/* GStreamer
 * Copyright (C) 2023 Seungha Yang <seungha@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

/**
 * SECTION:element-d3d12convert
 * @title: d3d12convert
 * @short_description: A Direct3D12 based color conversion and video resizing element
 *
 * This element resizes video frames and change color space.
 * By default the element will try to negotiate to the same size on the source
 * and sinkpad so that no scaling is needed.
 * It is therefore safe to insert this element in a pipeline to
 * get more robust behaviour without any cost if no scaling is needed.
 *
 * ## Example launch line
 * ```
 * gst-launch-1.0 videotestsrc ! video/x-raw,format=NV12 ! d3d12upload ! d3d12convert ! d3d12videosink
 * ```
 *  This will output a test video (generated in NV12 format) in a video
 * window. If the video sink selected does not support NV12
 * d3d12convert will automatically convert the video to a format understood
 * by the video sink.
 *
 * Since: 1.24
 */

/**
 * SECTION:element-d3d12colorconvert
 * @title: d3d12colorconvert
 *
 * A Direct3D12 based color conversion element
 *
 * ## Example launch line
 * ```
 * gst-launch-1.0 videotestsrc ! video/x-raw,format=NV12 ! d3d12upload ! d3d12colorconvert ! d3d12download ! video/x-raw,format=RGBA ! fakesink
 * ```
 *  This will upload a test video (generated in NV12 format) to Direct3D12
 * memory space and convert it to RGBA format. Then a converted Direct3D12
 * frame will be downloaded to system memory space.
 *
 * Since: 1.26
 */

/**
 * SECTION:element-d3d12scale
 * @title: d3d12scale
 *
 * A Direct3D12 based video resizing element
 *
 * ## Example launch line
 * ```
 * gst-launch-1.0 videotestsrc ! video/x-raw,width=640,height=480 ! d3d12upload ! d3d12scale ! d3d12download ! video/x-raw,width=1280,height=720 ! fakesink
 * ```
 *  This will upload a 640x480 resolution test video to Direct3D12
 * memory space and resize it to 1280x720 resolution. Then a resized Direct3D12
 * frame will be downloaded to system memory space.
 *
 * Since: 1.26
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstd3d12convert.h"
#include "gstd3d12pluginutils.h"
#include <directx/d3dx12.h>
#include <mutex>
#include <memory>
#include <queue>
#include <wrl.h>
#include <atomic>

/* *INDENT-OFF* */
using namespace Microsoft::WRL;
/* *INDENT-ON* */

GST_DEBUG_CATEGORY_STATIC (gst_d3d12_base_convert_debug);
#define GST_CAT_DEFAULT gst_d3d12_base_convert_debug

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY, GST_D3D12_ALL_FORMATS) "; "
        GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY ","
            GST_CAPS_FEATURE_META_GST_VIDEO_OVERLAY_COMPOSITION,
            GST_D3D12_ALL_FORMATS)));

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY, GST_D3D12_ALL_FORMATS) "; "
        GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY ","
            GST_CAPS_FEATURE_META_GST_VIDEO_OVERLAY_COMPOSITION,
            GST_D3D12_ALL_FORMATS)));

enum
{
  PROP_SAMPLING_METHOD = 1,
  PROP_ASYNC_DEPTH,
};

#define DEFAULT_ADD_BORDERS TRUE
#define DEFAULT_BORDER_COLOR G_GUINT64_CONSTANT(0xffff000000000000)
#define DEFAULT_GAMMA_MODE GST_VIDEO_GAMMA_MODE_NONE
#define DEFAULT_PRIMARIES_MODE GST_VIDEO_PRIMARIES_MODE_NONE
#define DEFAULT_SAMPLING_METHOD GST_D3D12_SAMPLING_METHOD_BILINEAR
#define DEFAULT_ASYNC_DEPTH 0
#define DEFAULT_HUE 0.0
#define DEFAULT_SATURATION 1.0
#define DEFAULT_BRIGHTNESS 0.0
#define DEFAULT_CONTRAST 1.0
#define DEFAULT_MAX_MIP_LEVELS 1

/* *INDENT-OFF* */
struct ConvertContext
{
  ConvertContext (GstD3D12Device * dev)
  {
    device = (GstD3D12Device *) gst_object_ref (dev);
    auto device_handle = gst_d3d12_device_get_device_handle (device);
    ca_pool = gst_d3d12_cmd_alloc_pool_new (device_handle,
        D3D12_COMMAND_LIST_TYPE_DIRECT);
  }

   ~ConvertContext ()
  {
    gst_d3d12_device_fence_wait (device, D3D12_COMMAND_LIST_TYPE_DIRECT,
        fence_val);

    gst_clear_object (&ca_pool);
    gst_clear_object (&conv);
    gst_clear_object (&device);
  }

  GstD3D12Device *device = nullptr;
  GstD3D12Converter *conv = nullptr;
  ComPtr<ID3D12GraphicsCommandList> cl;
  std::queue<guint64> scheduled;
  GstD3D12CmdAllocPool *ca_pool;
  guint64 fence_val = 0;
};

struct GstD3D12BaseConvertPrivate
{
  GstD3D12BaseConvertPrivate ()
  {
    fence_data_pool = gst_d3d12_fence_data_pool_new ();
    const gchar *channels[4] = { "HUE", "SATURATION",
      "BRIGHTNESS", "CONTRAST"
    };

    color_balance_channels = nullptr;
    for (guint i = 0; i < G_N_ELEMENTS (channels); i++) {
      auto ch = (GstColorBalanceChannel *)
          g_object_new (GST_TYPE_COLOR_BALANCE_CHANNEL, nullptr);
      ch->label = g_strdup (channels[i]);
      ch->min_value = -1000;
      ch->max_value = 1000;

      color_balance_channels = g_list_append (color_balance_channels, ch);
    }
  }

  ~GstD3D12BaseConvertPrivate ()
  {
    gst_clear_object (&fence_data_pool);

    auto iter = color_balance_channels;
    while (iter) {
      g_object_unref (iter->data);
      iter = iter->next;
    }

    g_list_free (color_balance_channels);
  }

  std::unique_ptr < ConvertContext > ctx;
  gboolean same_caps = FALSE;
  gboolean downstream_supports_crop_meta = FALSE;
  GstD3D12FenceDataPool *fence_data_pool;

  /* used for border rendering */
  D3D12_BOX in_rect = { };
  D3D12_BOX prev_in_rect = { };
  D3D12_BOX out_rect = { };

  gint borders_h = 0;
  gint borders_w = 0;

  gboolean add_borders = DEFAULT_ADD_BORDERS;
  gboolean active_add_borders = DEFAULT_ADD_BORDERS;

  guint64 border_color = DEFAULT_BORDER_COLOR;

  GstVideoGammaMode gamma_mode = DEFAULT_GAMMA_MODE;
  GstVideoGammaMode active_gamma_mode = DEFAULT_GAMMA_MODE;

  GstVideoPrimariesMode primaries_mode = DEFAULT_PRIMARIES_MODE;
  GstVideoPrimariesMode active_primaries_mode = DEFAULT_PRIMARIES_MODE;

  /* sampling method, configured via property */
  GstD3D12SamplingMethod sampling_method = DEFAULT_SAMPLING_METHOD;

  /* orientation */
  /* method configured via property */
  GstVideoOrientationMethod method = GST_VIDEO_ORIENTATION_IDENTITY;
  /* method parsed from tag */
  GstVideoOrientationMethod tag_method = GST_VIDEO_ORIENTATION_IDENTITY;
  /* method currently selected based on "method" and "tag_method" */
  GstVideoOrientationMethod selected_method = GST_VIDEO_ORIENTATION_IDENTITY;
  /* method previously selected and used for negotiation */
  GstVideoOrientationMethod active_method = GST_VIDEO_ORIENTATION_IDENTITY;

  GList *color_balance_channels = nullptr;
  gdouble hue = DEFAULT_HUE;
  gdouble saturation = DEFAULT_SATURATION;
  gdouble brightness = DEFAULT_BRIGHTNESS;
  gdouble contrast = DEFAULT_CONTRAST;
  gboolean color_balance_updated = FALSE;
  gboolean need_color_balance = FALSE;
  gboolean mip_levels_updated = FALSE;
  guint mip_levels = DEFAULT_MAX_MIP_LEVELS;

  std::atomic<guint> async_depth = { DEFAULT_ASYNC_DEPTH };

  std::mutex lock;
};
/* *INDENT-ON* */

struct _GstD3D12BaseConvert
{
  GstD3D12BaseFilter parent;

  GstD3D12BaseConvertPrivate *priv;
};

static void gst_d3d12_base_convert_finalize (GObject * object);
static void gst_d3d12_base_convert_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_d3d12_base_convert_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);
static gboolean gst_d3d12_base_convert_stop (GstBaseTransform * trans);
static GstCaps *gst_d3d12_base_convert_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter);
static GstCaps *gst_d3d12_base_convert_fixate_caps (GstBaseTransform *
    base, GstPadDirection direction, GstCaps * caps, GstCaps * othercaps);
static gboolean gst_d3d12_base_convert_propose_allocation (GstBaseTransform *
    trans, GstQuery * decide_query, GstQuery * query);
static gboolean gst_d3d12_base_convert_decide_allocation (GstBaseTransform *
    trans, GstQuery * query);
static GstFlowReturn gst_d3d12_base_convert_generate_output (GstBaseTransform *
    trans, GstBuffer ** buffer);
static gboolean gst_d3d12_base_convert_transform_meta (GstBaseTransform * trans,
    GstBuffer * outbuf, GstMeta * meta, GstBuffer * inbuf);
static void gst_d3d12_base_convert_before_transform (GstBaseTransform * trans,
    GstBuffer * buffer);
static GstFlowReturn gst_d3d12_base_convert_transform (GstBaseTransform * trans,
    GstBuffer * inbuf, GstBuffer * outbuf);
static gboolean gst_d3d12_base_convert_set_info (GstD3D12BaseFilter * filter,
    GstCaps * incaps, GstVideoInfo * in_info, GstCaps * outcaps,
    GstVideoInfo * out_info);

/**
 * GstD3D12BaseConvert:
 *
 * Since: 1.26
 */
#define gst_d3d12_base_convert_parent_class parent_class
G_DEFINE_ABSTRACT_TYPE_WITH_CODE (GstD3D12BaseConvert, gst_d3d12_base_convert,
    GST_TYPE_D3D12_BASE_FILTER,
    GST_DEBUG_CATEGORY_INIT (gst_d3d12_base_convert_debug, "d3d12convert", 0,
        "d3d12convert"));

static void
gst_d3d12_base_convert_class_init (GstD3D12BaseConvertClass * klass)
{
  auto object_class = G_OBJECT_CLASS (klass);
  auto element_class = GST_ELEMENT_CLASS (klass);
  auto trans_class = GST_BASE_TRANSFORM_CLASS (klass);
  auto filter_class = GST_D3D12_BASE_FILTER_CLASS (klass);

  object_class->set_property = gst_d3d12_base_convert_set_property;
  object_class->get_property = gst_d3d12_base_convert_get_property;
  object_class->finalize = gst_d3d12_base_convert_finalize;

  g_object_class_install_property (object_class, PROP_SAMPLING_METHOD,
      g_param_spec_enum ("method", "Method",
          "Method used for sampling",
          GST_TYPE_D3D12_SAMPLING_METHOD, DEFAULT_SAMPLING_METHOD,
          (GParamFlags) (GST_PARAM_MUTABLE_PLAYING | G_PARAM_READWRITE |
              G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12BaseConvert:async-depth:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_ASYNC_DEPTH,
      g_param_spec_uint ("async-depth", "Async Depth",
          "Number of in-flight GPU commands which can be scheduled without "
          "synchronization (0 = unlimited)", 0, G_MAXINT, DEFAULT_ASYNC_DEPTH,
          (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  gst_element_class_add_static_pad_template (element_class, &sink_template);
  gst_element_class_add_static_pad_template (element_class, &src_template);

  trans_class->passthrough_on_same_caps = FALSE;

  trans_class->stop = GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_stop);
  trans_class->transform_caps =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_transform_caps);
  trans_class->fixate_caps =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_fixate_caps);
  trans_class->propose_allocation =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_propose_allocation);
  trans_class->decide_allocation =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_decide_allocation);
  trans_class->generate_output =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_generate_output);
  trans_class->transform_meta =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_transform_meta);
  trans_class->before_transform =
      GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_before_transform);
  trans_class->transform = GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_transform);

  filter_class->set_info = GST_DEBUG_FUNCPTR (gst_d3d12_base_convert_set_info);

  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_BASE_CONVERT,
      (GstPluginAPIFlags) 0);
  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_SAMPLING_METHOD,
      (GstPluginAPIFlags) 0);
}

static void
gst_d3d12_base_convert_init (GstD3D12BaseConvert * self)
{
  self->priv = new GstD3D12BaseConvertPrivate ();
}

static void
gst_d3d12_base_convert_finalize (GObject * object)
{
  auto self = GST_D3D12_BASE_CONVERT (object);

  delete self->priv;

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gst_d3d12_base_convert_set_sampling_method (GstD3D12BaseConvert * self,
    GstD3D12SamplingMethod method)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  GST_DEBUG_OBJECT (self,
      "Sampling method %d -> %d", priv->sampling_method, method);

  priv->sampling_method = method;
  if (priv->ctx && priv->ctx->conv) {
    g_object_set (priv->ctx->conv, "sampler-filter",
        gst_d3d12_sampling_method_to_native (method), nullptr);
  }
}

static void
gst_d3d12_base_convert_set_add_border (GstD3D12BaseConvert * self,
    gboolean add_border)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  priv->add_borders = add_border;
  if (priv->add_borders != priv->active_add_borders)
    gst_base_transform_reconfigure_src (GST_BASE_TRANSFORM_CAST (self));
}

static void
gst_d3d12_base_convert_set_border_color (GstD3D12BaseConvert * self,
    guint64 border_color)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  priv->border_color = border_color;
  if (priv->ctx)
    g_object_set (priv->ctx->conv, "border-color", priv->border_color, nullptr);
}

static void
gst_d3d12_base_convert_set_orientation (GstD3D12BaseConvert * self,
    GstVideoOrientationMethod method, gboolean from_tag)
{
  if (method == GST_VIDEO_ORIENTATION_CUSTOM) {
    GST_WARNING_OBJECT (self, "Unsupported custom orientation");
    return;
  }

  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  if (from_tag)
    priv->tag_method = method;
  else
    priv->method = method;

  if (priv->method == GST_VIDEO_ORIENTATION_AUTO) {
    priv->selected_method = priv->tag_method;
  } else {
    priv->selected_method = priv->method;
  }

  if (priv->selected_method != priv->active_method) {
    GST_DEBUG_OBJECT (self, "Rotation orientation %d -> %d",
        priv->active_method, priv->selected_method);

    gst_base_transform_reconfigure_src (GST_BASE_TRANSFORM (self));
  }
}

static void
gst_d3d12_base_convert_set_gamma_mode (GstD3D12BaseConvert * self,
    GstVideoGammaMode mode)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  GstVideoGammaMode prev_mode = priv->gamma_mode;
  priv->gamma_mode = mode;

  if (priv->gamma_mode != priv->active_gamma_mode) {
    GST_DEBUG_OBJECT (self, "Gamma mode %d -> %d", prev_mode, priv->gamma_mode);
    gst_base_transform_reconfigure_src (GST_BASE_TRANSFORM (self));
  }
}

static void
gst_d3d12_base_convert_set_primaries_mode (GstD3D12BaseConvert * self,
    GstVideoPrimariesMode mode)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);

  GstVideoPrimariesMode prev_mode = priv->primaries_mode;
  priv->primaries_mode = mode;

  if (priv->primaries_mode != priv->active_primaries_mode) {
    gboolean prev_enabled = TRUE;
    gboolean new_enabled = TRUE;

    GST_DEBUG_OBJECT (self, "Primaries mode %d -> %d",
        prev_mode, priv->primaries_mode);

    if (prev_mode == GST_VIDEO_PRIMARIES_MODE_NONE)
      prev_enabled = FALSE;

    if (priv->primaries_mode == GST_VIDEO_PRIMARIES_MODE_NONE)
      new_enabled = FALSE;

    if (prev_enabled != new_enabled)
      gst_base_transform_reconfigure_src (GST_BASE_TRANSFORM (self));
    else
      priv->active_primaries_mode = priv->primaries_mode;
  }
}

static void
gst_d3d12_base_convert_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_BASE_CONVERT (object);
  auto priv = self->priv;

  switch (prop_id) {
    case PROP_SAMPLING_METHOD:
      gst_d3d12_base_convert_set_sampling_method (self,
          (GstD3D12SamplingMethod) g_value_get_enum (value));
      break;
    case PROP_ASYNC_DEPTH:
      priv->async_depth = g_value_get_uint (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_d3d12_base_convert_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_BASE_CONVERT (object);
  auto priv = self->priv;

  std::lock_guard < std::mutex > lk (priv->lock);
  switch (prop_id) {
    case PROP_SAMPLING_METHOD:
      g_value_set_enum (value, priv->sampling_method);
      break;
    case PROP_ASYNC_DEPTH:
      g_value_set_uint (value, priv->async_depth);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static gboolean
gst_d3d12_base_convert_stop (GstBaseTransform * trans)
{
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;

  priv->ctx = nullptr;

  return GST_BASE_TRANSFORM_CLASS (parent_class)->stop (trans);
}

static GstCaps *
gst_d3d12_base_convert_caps_remove_format_info (GstCaps * caps)
{
  GstStructure *st;
  GstCapsFeatures *f;
  gint i, n;
  GstCaps *res;
  GstCapsFeatures *feature =
      gst_caps_features_from_string (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY);

  res = gst_caps_new_empty ();

  n = gst_caps_get_size (caps);
  for (i = 0; i < n; i++) {
    st = gst_caps_get_structure (caps, i);
    f = gst_caps_get_features (caps, i);

    /* If this is already expressed by the existing caps
     * skip this structure */
    if (i > 0 && gst_caps_is_subset_structure_full (res, st, f))
      continue;

    st = gst_structure_copy (st);
    /* Only remove format info for the cases when we can actually convert */
    if (!gst_caps_features_is_any (f)
        && gst_caps_features_is_equal (f, feature)) {
      gst_structure_remove_fields (st, "format", "colorimetry", "chroma-site",
          NULL);
    }

    gst_caps_append_structure_full (res, st, gst_caps_features_copy (f));
  }
  gst_caps_features_free (feature);

  return res;
}

static GstCaps *
gst_d3d12_base_convert_caps_rangify_size_info (GstCaps * caps)
{
  GstStructure *st;
  GstCapsFeatures *f;
  gint i, n;
  GstCaps *res;
  GstCapsFeatures *feature =
      gst_caps_features_from_string (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY);

  res = gst_caps_new_empty ();

  n = gst_caps_get_size (caps);
  for (i = 0; i < n; i++) {
    st = gst_caps_get_structure (caps, i);
    f = gst_caps_get_features (caps, i);

    /* If this is already expressed by the existing caps
     * skip this structure */
    if (i > 0 && gst_caps_is_subset_structure_full (res, st, f))
      continue;

    st = gst_structure_copy (st);
    /* Only remove format info for the cases when we can actually convert */
    if (!gst_caps_features_is_any (f)
        && gst_caps_features_is_equal (f, feature)) {
      gst_structure_set (st, "width", GST_TYPE_INT_RANGE, 1, G_MAXINT,
          "height", GST_TYPE_INT_RANGE, 1, G_MAXINT, NULL);

      /* if pixel aspect ratio, make a range of it */
      if (gst_structure_has_field (st, "pixel-aspect-ratio")) {
        gst_structure_set (st, "pixel-aspect-ratio",
            GST_TYPE_FRACTION_RANGE, 1, G_MAXINT, G_MAXINT, 1, NULL);
      }
    }

    gst_caps_append_structure_full (res, st, gst_caps_features_copy (f));
  }
  gst_caps_features_free (feature);

  return res;
}

static GstCaps *
gst_d3d12_base_convert_caps_remove_format_and_rangify_size_info (GstCaps * caps)
{
  GstStructure *st;
  GstCapsFeatures *f;
  gint i, n;
  GstCaps *res;
  GstCapsFeatures *feature =
      gst_caps_features_new_single_static_str
      (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY);

  res = gst_caps_new_empty ();

  n = gst_caps_get_size (caps);
  for (i = 0; i < n; i++) {
    st = gst_caps_get_structure (caps, i);
    f = gst_caps_get_features (caps, i);

    /* If this is already expressed by the existing caps
     * skip this structure */
    if (i > 0 && gst_caps_is_subset_structure_full (res, st, f))
      continue;

    st = gst_structure_copy (st);
    /* Only remove format info for the cases when we can actually convert */
    if (!gst_caps_features_is_any (f)
        && gst_caps_features_is_equal (f, feature)) {
      gst_structure_set (st, "width", GST_TYPE_INT_RANGE, 1, G_MAXINT,
          "height", GST_TYPE_INT_RANGE, 1, G_MAXINT, nullptr);
      /* if pixel aspect ratio, make a range of it */
      if (gst_structure_has_field (st, "pixel-aspect-ratio")) {
        gst_structure_set (st, "pixel-aspect-ratio",
            GST_TYPE_FRACTION_RANGE, 1, G_MAXINT, G_MAXINT, 1, nullptr);
      }
      gst_structure_remove_fields (st, "format", "colorimetry", "chroma-site",
          nullptr);
    }

    gst_caps_append_structure_full (res, st, gst_caps_features_copy (f));
  }
  gst_caps_features_free (feature);

  return res;
}

static GstCaps *
gst_d3d12_base_convert_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter)
{
  auto ret =
      gst_d3d12_base_convert_caps_remove_format_and_rangify_size_info (caps);

  if (filter) {
    auto tmp = gst_caps_intersect_full (filter, ret, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref (ret);
    ret = tmp;
  }

  GST_DEBUG_OBJECT (trans, "transformed %" GST_PTR_FORMAT " into %"
      GST_PTR_FORMAT, caps, ret);

  return ret;
}

/*
 * This is an incomplete matrix of in formats and a score for the prefered output
 * format.
 *
 *         out: RGB24   RGB16  ARGB  AYUV  YUV444  YUV422 YUV420 YUV411 YUV410  PAL  GRAY
 *  in
 * RGB24          0      2       1     2     2       3      4      5      6      7    8
 * RGB16          1      0       1     2     2       3      4      5      6      7    8
 * ARGB           2      3       0     1     4       5      6      7      8      9    10
 * AYUV           3      4       1     0     2       5      6      7      8      9    10
 * YUV444         2      4       3     1     0       5      6      7      8      9    10
 * YUV422         3      5       4     2     1       0      6      7      8      9    10
 * YUV420         4      6       5     3     2       1      0      7      8      9    10
 * YUV411         4      6       5     3     2       1      7      0      8      9    10
 * YUV410         6      8       7     5     4       3      2      1      0      9    10
 * PAL            1      3       2     6     4       6      7      8      9      0    10
 * GRAY           1      4       3     2     1       5      6      7      8      9    0
 *
 * PAL or GRAY are never prefered, if we can we would convert to PAL instead
 * of GRAY, though
 * less subsampling is prefered and if any, preferably horizontal
 * We would like to keep the alpha, even if we would need to to colorspace conversion
 * or lose depth.
 */
#define SCORE_FORMAT_CHANGE       1
#define SCORE_DEPTH_CHANGE        1
#define SCORE_ALPHA_CHANGE        1
#define SCORE_CHROMA_W_CHANGE     1
#define SCORE_CHROMA_H_CHANGE     1
#define SCORE_PALETTE_CHANGE      1

#define SCORE_COLORSPACE_LOSS     2     /* RGB <-> YUV */
#define SCORE_DEPTH_LOSS          4     /* change bit depth */
#define SCORE_ALPHA_LOSS          8     /* lose the alpha channel */
#define SCORE_CHROMA_W_LOSS      16     /* vertical subsample */
#define SCORE_CHROMA_H_LOSS      32     /* horizontal subsample */
#define SCORE_PALETTE_LOSS       64     /* convert to palette format */
#define SCORE_COLOR_LOSS        128     /* convert to GRAY */

#define COLORSPACE_MASK (GST_VIDEO_FORMAT_FLAG_YUV | \
                         GST_VIDEO_FORMAT_FLAG_RGB | GST_VIDEO_FORMAT_FLAG_GRAY)
#define ALPHA_MASK      (GST_VIDEO_FORMAT_FLAG_ALPHA)
#define PALETTE_MASK    (GST_VIDEO_FORMAT_FLAG_PALETTE)

/* calculate how much loss a conversion would be */
static void
score_value (GstBaseTransform * base, const GstVideoFormatInfo * in_info,
    const GValue * val, gint * min_loss, const GstVideoFormatInfo ** out_info)
{
  const gchar *fname;
  const GstVideoFormatInfo *t_info;
  guint in_flags, t_flags;
  gint loss;

  fname = g_value_get_string (val);
  t_info = gst_video_format_get_info (gst_video_format_from_string (fname));
  if (!t_info || t_info->format == GST_VIDEO_FORMAT_UNKNOWN)
    return;

  /* accept input format immediately without loss */
  if (in_info == t_info) {
    *min_loss = 0;
    *out_info = t_info;
    return;
  }

  loss = SCORE_FORMAT_CHANGE;

  in_flags = GST_VIDEO_FORMAT_INFO_FLAGS (in_info);
  in_flags &= ~GST_VIDEO_FORMAT_FLAG_LE;
  in_flags &= ~GST_VIDEO_FORMAT_FLAG_COMPLEX;
  in_flags &= ~GST_VIDEO_FORMAT_FLAG_UNPACK;

  t_flags = GST_VIDEO_FORMAT_INFO_FLAGS (t_info);
  t_flags &= ~GST_VIDEO_FORMAT_FLAG_LE;
  t_flags &= ~GST_VIDEO_FORMAT_FLAG_COMPLEX;
  t_flags &= ~GST_VIDEO_FORMAT_FLAG_UNPACK;

  if ((t_flags & PALETTE_MASK) != (in_flags & PALETTE_MASK)) {
    loss += SCORE_PALETTE_CHANGE;
    if (t_flags & PALETTE_MASK)
      loss += SCORE_PALETTE_LOSS;
  }

  if ((t_flags & COLORSPACE_MASK) != (in_flags & COLORSPACE_MASK)) {
    loss += SCORE_COLORSPACE_LOSS;
    if (t_flags & GST_VIDEO_FORMAT_FLAG_GRAY)
      loss += SCORE_COLOR_LOSS;
  }

  if ((t_flags & ALPHA_MASK) != (in_flags & ALPHA_MASK)) {
    loss += SCORE_ALPHA_CHANGE;
    if (in_flags & ALPHA_MASK)
      loss += SCORE_ALPHA_LOSS;
  }

  if ((in_info->h_sub[1]) != (t_info->h_sub[1])) {
    loss += SCORE_CHROMA_H_CHANGE;
    if ((in_info->h_sub[1]) < (t_info->h_sub[1]))
      loss += SCORE_CHROMA_H_LOSS;
  }
  if ((in_info->w_sub[1]) != (t_info->w_sub[1])) {
    loss += SCORE_CHROMA_W_CHANGE;
    if ((in_info->w_sub[1]) < (t_info->w_sub[1]))
      loss += SCORE_CHROMA_W_LOSS;
  }

  if ((in_info->bits) != (t_info->bits)) {
    loss += SCORE_DEPTH_CHANGE;
    if ((in_info->bits) > (t_info->bits))
      loss += SCORE_DEPTH_LOSS + (in_info->bits - t_info->bits);
  }

  GST_DEBUG_OBJECT (base, "score %s -> %s = %d",
      GST_VIDEO_FORMAT_INFO_NAME (in_info),
      GST_VIDEO_FORMAT_INFO_NAME (t_info), loss);

  if (loss < *min_loss) {
    GST_DEBUG_OBJECT (base, "found new best %d", loss);
    *out_info = t_info;
    *min_loss = loss;
  }
}

static void
gst_d3d12_base_convert_fixate_format (GstBaseTransform * trans, GstCaps * caps,
    GstCaps * result)
{
  GstStructure *ins, *outs;
  const gchar *in_format;
  const GstVideoFormatInfo *in_info, *out_info = nullptr;
  gint min_loss = G_MAXINT;
  guint i, capslen;

  ins = gst_caps_get_structure (caps, 0);
  in_format = gst_structure_get_string (ins, "format");
  if (!in_format) {
    return;
  }

  GST_DEBUG_OBJECT (trans, "source format %s", in_format);

  in_info =
      gst_video_format_get_info (gst_video_format_from_string (in_format));
  if (!in_info)
    return;

  outs = gst_caps_get_structure (result, 0);

  capslen = gst_caps_get_size (result);
  GST_DEBUG ("iterate %d structures", capslen);
  for (i = 0; i < capslen; i++) {
    GstStructure *tests;
    const GValue *format;

    tests = gst_caps_get_structure (result, i);
    format = gst_structure_get_value (tests, "format");

    /* should not happen */
    if (format == nullptr)
      continue;

    if (GST_VALUE_HOLDS_LIST (format)) {
      gint j, len;

      len = gst_value_list_get_size (format);
      GST_DEBUG_OBJECT (trans, "have %d formats", len);
      for (j = 0; j < len; j++) {
        const GValue *val;

        val = gst_value_list_get_value (format, j);
        if (G_VALUE_HOLDS_STRING (val)) {
          score_value (trans, in_info, val, &min_loss, &out_info);
          if (min_loss == 0)
            break;
        }
      }
    } else if (G_VALUE_HOLDS_STRING (format)) {
      score_value (trans, in_info, format, &min_loss, &out_info);
    }
  }
  if (out_info)
    gst_structure_set (outs, "format", G_TYPE_STRING,
        GST_VIDEO_FORMAT_INFO_NAME (out_info), nullptr);
}

static gboolean
subsampling_unchanged (GstVideoInfo * in_info, GstVideoInfo * out_info)
{
  guint i;
  const GstVideoFormatInfo *in_format, *out_format;

  if (GST_VIDEO_INFO_N_COMPONENTS (in_info) !=
      GST_VIDEO_INFO_N_COMPONENTS (out_info))
    return FALSE;

  in_format = in_info->finfo;
  out_format = out_info->finfo;

  for (i = 0; i < GST_VIDEO_INFO_N_COMPONENTS (in_info); i++) {
    if (GST_VIDEO_FORMAT_INFO_W_SUB (in_format,
            i) != GST_VIDEO_FORMAT_INFO_W_SUB (out_format, i))
      return FALSE;
    if (GST_VIDEO_FORMAT_INFO_H_SUB (in_format,
            i) != GST_VIDEO_FORMAT_INFO_H_SUB (out_format, i))
      return FALSE;
  }

  return TRUE;
}

static void
transfer_colorimetry_from_input (GstBaseTransform * trans, GstCaps * in_caps,
    GstCaps * out_caps)
{
  GstStructure *out_caps_s = gst_caps_get_structure (out_caps, 0);
  GstStructure *in_caps_s = gst_caps_get_structure (in_caps, 0);
  gboolean have_colorimetry =
      gst_structure_has_field (out_caps_s, "colorimetry");
  gboolean have_chroma_site =
      gst_structure_has_field (out_caps_s, "chroma-site");

  /* If the output already has colorimetry and chroma-site, stop,
   * otherwise try and transfer what we can from the input caps */
  if (have_colorimetry && have_chroma_site)
    return;

  {
    GstVideoInfo in_info, out_info;
    const GValue *in_colorimetry =
        gst_structure_get_value (in_caps_s, "colorimetry");

    if (!gst_video_info_from_caps (&in_info, in_caps)) {
      GST_WARNING_OBJECT (trans,
          "Failed to convert sink pad caps to video info");
      return;
    }
    if (!gst_video_info_from_caps (&out_info, out_caps)) {
      GST_WARNING_OBJECT (trans,
          "Failed to convert src pad caps to video info");
      return;
    }

    if (!have_colorimetry && in_colorimetry != nullptr) {
      if ((GST_VIDEO_INFO_IS_YUV (&out_info)
              && GST_VIDEO_INFO_IS_YUV (&in_info))
          || (GST_VIDEO_INFO_IS_RGB (&out_info)
              && GST_VIDEO_INFO_IS_RGB (&in_info))
          || (GST_VIDEO_INFO_IS_GRAY (&out_info)
              && GST_VIDEO_INFO_IS_GRAY (&in_info))) {
        /* Can transfer the colorimetry intact from the input if it has it */
        gst_structure_set_value (out_caps_s, "colorimetry", in_colorimetry);
      } else {
        gchar *colorimetry_str;

        /* Changing between YUV/RGB - forward primaries and transfer function, but use
         * default range and matrix.
         * the primaries is used for conversion between RGB and XYZ (CIE 1931 coordinate).
         * the transfer function could be another reference (e.g., HDR)
         */
        out_info.colorimetry.primaries = in_info.colorimetry.primaries;
        out_info.colorimetry.transfer = in_info.colorimetry.transfer;

        colorimetry_str =
            gst_video_colorimetry_to_string (&out_info.colorimetry);
        gst_caps_set_simple (out_caps, "colorimetry", G_TYPE_STRING,
            colorimetry_str, nullptr);
        g_free (colorimetry_str);
      }
    }

    /* Only YUV output needs chroma-site. If the input was also YUV and had the same chroma
     * subsampling, transfer the siting. If the sub-sampling is changing, then the planes get
     * scaled anyway so there's no real reason to prefer the input siting. */
    if (!have_chroma_site && GST_VIDEO_INFO_IS_YUV (&out_info)) {
      if (GST_VIDEO_INFO_IS_YUV (&in_info)) {
        const GValue *in_chroma_site =
            gst_structure_get_value (in_caps_s, "chroma-site");
        if (in_chroma_site != nullptr
            && subsampling_unchanged (&in_info, &out_info))
          gst_structure_set_value (out_caps_s, "chroma-site", in_chroma_site);
      }
    }
  }
}

static GstCaps *
gst_d3d12_base_convert_get_fixed_format (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  GstCaps *result;

  result = gst_caps_intersect (othercaps, caps);
  if (gst_caps_is_empty (result)) {
    gst_caps_unref (result);
    result = gst_caps_copy (othercaps);
  }

  gst_d3d12_base_convert_fixate_format (trans, caps, result);

  /* fixate remaining fields */
  result = gst_caps_fixate (result);

  if (direction == GST_PAD_SINK) {
    if (gst_caps_is_subset (caps, result)) {
      gst_caps_replace (&result, caps);
    } else {
      /* Try and preserve input colorimetry / chroma information */
      transfer_colorimetry_from_input (trans, caps, result);
    }
  }

  return result;
}

static GstCaps *
gst_d3d12_base_convert_fixate_size (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  auto self = GST_D3D12_BASE_CONVERT (base);
  auto priv = self->priv;
  GstStructure *ins, *outs;
  const GValue *from_par, *to_par;
  GValue fpar = G_VALUE_INIT, tpar = G_VALUE_INIT;
  gboolean rotate = FALSE;

  othercaps = gst_caps_truncate (othercaps);
  othercaps = gst_caps_make_writable (othercaps);
  ins = gst_caps_get_structure (caps, 0);
  outs = gst_caps_get_structure (othercaps, 0);

  from_par = gst_structure_get_value (ins, "pixel-aspect-ratio");
  to_par = gst_structure_get_value (outs, "pixel-aspect-ratio");

  /* If we're fixating from the sinkpad we always set the PAR and
   * assume that missing PAR on the sinkpad means 1/1 and
   * missing PAR on the srcpad means undefined
   */
  std::lock_guard < std::mutex > lk (priv->lock);
  switch (priv->selected_method) {
    case GST_VIDEO_ORIENTATION_90R:
    case GST_VIDEO_ORIENTATION_90L:
    case GST_VIDEO_ORIENTATION_UL_LR:
    case GST_VIDEO_ORIENTATION_UR_LL:
      rotate = TRUE;
      break;
    default:
      rotate = FALSE;
      break;
  }

  if (direction == GST_PAD_SINK) {
    if (!from_par) {
      g_value_init (&fpar, GST_TYPE_FRACTION);
      gst_value_set_fraction (&fpar, 1, 1);
      from_par = &fpar;
    }
    if (!to_par) {
      g_value_init (&tpar, GST_TYPE_FRACTION_RANGE);
      gst_value_set_fraction_range_full (&tpar, 1, G_MAXINT, G_MAXINT, 1);
      to_par = &tpar;
    }
  } else {
    gint from_par_n, from_par_d;

    if (!from_par) {
      g_value_init (&fpar, GST_TYPE_FRACTION);
      gst_value_set_fraction (&fpar, 1, 1);
      from_par = &fpar;

      from_par_n = from_par_d = 1;
    } else {
      from_par_n = gst_value_get_fraction_numerator (from_par);
      from_par_d = gst_value_get_fraction_denominator (from_par);
    }

    if (!to_par) {
      gint to_par_n, to_par_d;

      if (rotate) {
        to_par_n = from_par_d;
        to_par_d = from_par_n;
      } else {
        to_par_n = from_par_n;
        to_par_d = from_par_d;
      }

      g_value_init (&tpar, GST_TYPE_FRACTION);
      gst_value_set_fraction (&tpar, to_par_n, to_par_d);
      to_par = &tpar;

      gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
          to_par_n, to_par_d, nullptr);
    }
  }

  /* we have both PAR but they might not be fixated */
  {
    gint from_w, from_h, from_par_n, from_par_d, to_par_n, to_par_d;
    gint w = 0, h = 0;
    gint from_dar_n, from_dar_d;
    gint num, den;

    /* from_par should be fixed */
    g_return_val_if_fail (gst_value_is_fixed (from_par), othercaps);

    from_par_n = gst_value_get_fraction_numerator (from_par);
    from_par_d = gst_value_get_fraction_denominator (from_par);

    gst_structure_get_int (ins, "width", &from_w);
    gst_structure_get_int (ins, "height", &from_h);

    gst_structure_get_int (outs, "width", &w);
    gst_structure_get_int (outs, "height", &h);

    /* swap dimensions when it's rotated */
    if (rotate) {
      gint _tmp = from_w;
      from_w = from_h;
      from_h = _tmp;

      _tmp = from_par_n;
      from_par_n = from_par_d;
      from_par_d = _tmp;
    }

    /* if both width and height are already fixed, we can't do anything
     * about it anymore */
    if (w && h) {
      guint n, d;

      GST_DEBUG_OBJECT (base, "dimensions already set to %dx%d, not fixating",
          w, h);
      if (!gst_value_is_fixed (to_par)) {
        if (gst_video_calculate_display_ratio (&n, &d, from_w, from_h,
                from_par_n, from_par_d, w, h)) {
          GST_DEBUG_OBJECT (base, "fixating to_par to %dx%d", n, d);
          if (gst_structure_has_field (outs, "pixel-aspect-ratio"))
            gst_structure_fixate_field_nearest_fraction (outs,
                "pixel-aspect-ratio", n, d);
          else if (n != d)
            gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
                n, d, nullptr);
        }
      }
      goto done;
    }

    /* Calculate input DAR */
    if (!gst_util_fraction_multiply (from_w, from_h, from_par_n, from_par_d,
            &from_dar_n, &from_dar_d)) {
      GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
          ("Error calculating the output scaled size - integer overflow"));
      goto done;
    }

    GST_DEBUG_OBJECT (base, "Input DAR is %d/%d", from_dar_n, from_dar_d);

    /* If either width or height are fixed there's not much we
     * can do either except choosing a height or width and PAR
     * that matches the DAR as good as possible
     */
    if (h) {
      GstStructure *tmp;
      gint set_w, set_par_n, set_par_d;

      GST_DEBUG_OBJECT (base, "height is fixed (%d)", h);

      /* If the PAR is fixed too, there's not much to do
       * except choosing the width that is nearest to the
       * width with the same DAR */
      if (gst_value_is_fixed (to_par)) {
        to_par_n = gst_value_get_fraction_numerator (to_par);
        to_par_d = gst_value_get_fraction_denominator (to_par);

        GST_DEBUG_OBJECT (base, "PAR is fixed %d/%d", to_par_n, to_par_d);

        if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, to_par_d,
                to_par_n, &num, &den)) {
          GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
              ("Error calculating the output scaled size - integer overflow"));
          goto done;
        }

        w = (guint) gst_util_uint64_scale_int_round (h, num, den);
        gst_structure_fixate_field_nearest_int (outs, "width", w);

        goto done;
      }

      /* The PAR is not fixed and it's quite likely that we can set
       * an arbitrary PAR. */

      /* Check if we can keep the input width */
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "width", from_w);
      gst_structure_get_int (tmp, "width", &set_w);

      /* Might have failed but try to keep the DAR nonetheless by
       * adjusting the PAR */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, h, set_w,
              &to_par_n, &to_par_d)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        gst_structure_free (tmp);
        goto done;
      }

      if (!gst_structure_has_field (tmp, "pixel-aspect-ratio"))
        gst_structure_set_value (tmp, "pixel-aspect-ratio", to_par);
      gst_structure_fixate_field_nearest_fraction (tmp, "pixel-aspect-ratio",
          to_par_n, to_par_d);
      gst_structure_get_fraction (tmp, "pixel-aspect-ratio", &set_par_n,
          &set_par_d);
      gst_structure_free (tmp);

      /* Check if the adjusted PAR is accepted */
      if (set_par_n == to_par_n && set_par_d == to_par_d) {
        if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
            set_par_n != set_par_d)
          gst_structure_set (outs, "width", G_TYPE_INT, set_w,
              "pixel-aspect-ratio", GST_TYPE_FRACTION, set_par_n, set_par_d,
              nullptr);
        goto done;
      }

      /* Otherwise scale the width to the new PAR and check if the
       * adjusted with is accepted. If all that fails we can't keep
       * the DAR */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, set_par_d,
              set_par_n, &num, &den)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        goto done;
      }

      w = (guint) gst_util_uint64_scale_int_round (h, num, den);
      gst_structure_fixate_field_nearest_int (outs, "width", w);
      if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
          set_par_n != set_par_d)
        gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
            set_par_n, set_par_d, nullptr);

      goto done;
    } else if (w) {
      GstStructure *tmp;
      gint set_h, set_par_n, set_par_d;

      GST_DEBUG_OBJECT (base, "width is fixed (%d)", w);

      /* If the PAR is fixed too, there's not much to do
       * except choosing the height that is nearest to the
       * height with the same DAR */
      if (gst_value_is_fixed (to_par)) {
        to_par_n = gst_value_get_fraction_numerator (to_par);
        to_par_d = gst_value_get_fraction_denominator (to_par);

        GST_DEBUG_OBJECT (base, "PAR is fixed %d/%d", to_par_n, to_par_d);

        if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, to_par_d,
                to_par_n, &num, &den)) {
          GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
              ("Error calculating the output scaled size - integer overflow"));
          goto done;
        }

        h = (guint) gst_util_uint64_scale_int_round (w, den, num);
        gst_structure_fixate_field_nearest_int (outs, "height", h);

        goto done;
      }

      /* The PAR is not fixed and it's quite likely that we can set
       * an arbitrary PAR. */

      /* Check if we can keep the input height */
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "height", from_h);
      gst_structure_get_int (tmp, "height", &set_h);

      /* Might have failed but try to keep the DAR nonetheless by
       * adjusting the PAR */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, set_h, w,
              &to_par_n, &to_par_d)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        gst_structure_free (tmp);
        goto done;
      }
      if (!gst_structure_has_field (tmp, "pixel-aspect-ratio"))
        gst_structure_set_value (tmp, "pixel-aspect-ratio", to_par);
      gst_structure_fixate_field_nearest_fraction (tmp, "pixel-aspect-ratio",
          to_par_n, to_par_d);
      gst_structure_get_fraction (tmp, "pixel-aspect-ratio", &set_par_n,
          &set_par_d);
      gst_structure_free (tmp);

      /* Check if the adjusted PAR is accepted */
      if (set_par_n == to_par_n && set_par_d == to_par_d) {
        if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
            set_par_n != set_par_d)
          gst_structure_set (outs, "height", G_TYPE_INT, set_h,
              "pixel-aspect-ratio", GST_TYPE_FRACTION, set_par_n, set_par_d,
              nullptr);
        goto done;
      }

      /* Otherwise scale the height to the new PAR and check if the
       * adjusted with is accepted. If all that fails we can't keep
       * the DAR */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, set_par_d,
              set_par_n, &num, &den)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scale sized - integer overflow"));
        goto done;
      }

      h = (guint) gst_util_uint64_scale_int_round (w, den, num);
      gst_structure_fixate_field_nearest_int (outs, "height", h);
      if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
          set_par_n != set_par_d)
        gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
            set_par_n, set_par_d, nullptr);

      goto done;
    } else if (gst_value_is_fixed (to_par)) {
      GstStructure *tmp;
      gint set_h, set_w, f_h, f_w;

      to_par_n = gst_value_get_fraction_numerator (to_par);
      to_par_d = gst_value_get_fraction_denominator (to_par);

      /* Calculate scale factor for the PAR change */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, to_par_n,
              to_par_d, &num, &den)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        goto done;
      }

      /* Try to keep the input height (because of interlacing) */
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "height", from_h);
      gst_structure_get_int (tmp, "height", &set_h);

      /* This might have failed but try to scale the width
       * to keep the DAR nonetheless */
      w = (guint) gst_util_uint64_scale_int_round (set_h, num, den);
      gst_structure_fixate_field_nearest_int (tmp, "width", w);
      gst_structure_get_int (tmp, "width", &set_w);
      gst_structure_free (tmp);

      /* We kept the DAR and the height is nearest to the original height */
      if (set_w == w) {
        gst_structure_set (outs, "width", G_TYPE_INT, set_w, "height",
            G_TYPE_INT, set_h, nullptr);
        goto done;
      }

      f_h = set_h;
      f_w = set_w;

      /* If the former failed, try to keep the input width at least */
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "width", from_w);
      gst_structure_get_int (tmp, "width", &set_w);

      /* This might have failed but try to scale the width
       * to keep the DAR nonetheless */
      h = (guint) gst_util_uint64_scale_int_round (set_w, den, num);
      gst_structure_fixate_field_nearest_int (tmp, "height", h);
      gst_structure_get_int (tmp, "height", &set_h);
      gst_structure_free (tmp);

      /* We kept the DAR and the width is nearest to the original width */
      if (set_h == h) {
        gst_structure_set (outs, "width", G_TYPE_INT, set_w, "height",
            G_TYPE_INT, set_h, nullptr);
        goto done;
      }

      /* If all this failed, keep the dimensions with the DAR that was closest
       * to the correct DAR. This changes the DAR but there's not much else to
       * do here.
       */
      if (set_w * ABS (set_h - h) < ABS (f_w - w) * f_h) {
        f_h = set_h;
        f_w = set_w;
      }
      gst_structure_set (outs, "width", G_TYPE_INT, f_w, "height", G_TYPE_INT,
          f_h, nullptr);
      goto done;
    } else {
      GstStructure *tmp;
      gint set_h, set_w, set_par_n, set_par_d, tmp2;

      /* width, height and PAR are not fixed but passthrough is not possible */

      /* First try to keep the height and width as good as possible
       * and scale PAR */
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "height", from_h);
      gst_structure_get_int (tmp, "height", &set_h);
      gst_structure_fixate_field_nearest_int (tmp, "width", from_w);
      gst_structure_get_int (tmp, "width", &set_w);

      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, set_h, set_w,
              &to_par_n, &to_par_d)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        gst_structure_free (tmp);
        goto done;
      }

      if (!gst_structure_has_field (tmp, "pixel-aspect-ratio"))
        gst_structure_set_value (tmp, "pixel-aspect-ratio", to_par);
      gst_structure_fixate_field_nearest_fraction (tmp, "pixel-aspect-ratio",
          to_par_n, to_par_d);
      gst_structure_get_fraction (tmp, "pixel-aspect-ratio", &set_par_n,
          &set_par_d);
      gst_structure_free (tmp);

      if (set_par_n == to_par_n && set_par_d == to_par_d) {
        gst_structure_set (outs, "width", G_TYPE_INT, set_w, "height",
            G_TYPE_INT, set_h, nullptr);

        if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
            set_par_n != set_par_d)
          gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
              set_par_n, set_par_d, nullptr);
        goto done;
      }

      /* Otherwise try to scale width to keep the DAR with the set
       * PAR and height */
      if (!gst_util_fraction_multiply (from_dar_n, from_dar_d, set_par_d,
              set_par_n, &num, &den)) {
        GST_ELEMENT_ERROR (base, CORE, NEGOTIATION, (nullptr),
            ("Error calculating the output scaled size - integer overflow"));
        goto done;
      }

      w = (guint) gst_util_uint64_scale_int_round (set_h, num, den);
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "width", w);
      gst_structure_get_int (tmp, "width", &tmp2);
      gst_structure_free (tmp);

      if (tmp2 == w) {
        gst_structure_set (outs, "width", G_TYPE_INT, tmp2, "height",
            G_TYPE_INT, set_h, nullptr);
        if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
            set_par_n != set_par_d)
          gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
              set_par_n, set_par_d, nullptr);
        goto done;
      }

      /* ... or try the same with the height */
      h = (guint) gst_util_uint64_scale_int_round (set_w, den, num);
      tmp = gst_structure_copy (outs);
      gst_structure_fixate_field_nearest_int (tmp, "height", h);
      gst_structure_get_int (tmp, "height", &tmp2);
      gst_structure_free (tmp);

      if (tmp2 == h) {
        gst_structure_set (outs, "width", G_TYPE_INT, set_w, "height",
            G_TYPE_INT, tmp2, nullptr);
        if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
            set_par_n != set_par_d)
          gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
              set_par_n, set_par_d, nullptr);
        goto done;
      }

      /* If all fails we can't keep the DAR and take the nearest values
       * for everything from the first try */
      gst_structure_set (outs, "width", G_TYPE_INT, set_w, "height",
          G_TYPE_INT, set_h, nullptr);
      if (gst_structure_has_field (outs, "pixel-aspect-ratio") ||
          set_par_n != set_par_d)
        gst_structure_set (outs, "pixel-aspect-ratio", GST_TYPE_FRACTION,
            set_par_n, set_par_d, nullptr);
    }
  }

done:
  if (from_par == &fpar)
    g_value_unset (&fpar);
  if (to_par == &tpar)
    g_value_unset (&tpar);

  return othercaps;
}

static GstCaps *
gst_d3d12_base_convert_fixate_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  GST_DEBUG_OBJECT (trans,
      "trying to fixate othercaps %" GST_PTR_FORMAT " based on caps %"
      GST_PTR_FORMAT, othercaps, caps);

  auto format = gst_d3d12_base_convert_get_fixed_format (trans, direction, caps,
      othercaps);

  if (gst_caps_is_empty (format)) {
    GST_ERROR_OBJECT (trans, "Could not convert formats");
    return format;
  }

  /* convert mode is "all" or "size" here */
  othercaps =
      gst_d3d12_base_convert_fixate_size (trans, direction, caps, othercaps);

  if (gst_caps_get_size (othercaps) == 1) {
    guint i;
    const gchar *format_fields[] = { "format", "colorimetry", "chroma-site" };
    GstStructure *format_struct = gst_caps_get_structure (format, 0);
    GstStructure *fixated_struct;

    othercaps = gst_caps_make_writable (othercaps);
    fixated_struct = gst_caps_get_structure (othercaps, 0);

    for (i = 0; i < G_N_ELEMENTS (format_fields); i++) {
      if (gst_structure_has_field (format_struct, format_fields[i])) {
        gst_structure_set (fixated_struct, format_fields[i], G_TYPE_STRING,
            gst_structure_get_string (format_struct, format_fields[i]),
            nullptr);
      } else {
        gst_structure_remove_field (fixated_struct, format_fields[i]);
      }
    }
  }
  gst_caps_unref (format);

  GST_DEBUG_OBJECT (trans, "fixated othercaps to %" GST_PTR_FORMAT, othercaps);

  return othercaps;
}

static gboolean
gst_d3d12_base_convert_propose_allocation (GstBaseTransform * trans,
    GstQuery * decide_query, GstQuery * query)
{
  auto filter = GST_D3D12_BASE_FILTER (trans);
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;
  GstVideoInfo info;
  GstBufferPool *pool = nullptr;
  GstCaps *caps;
  guint n_pools, i;
  guint size;

  if (!GST_BASE_TRANSFORM_CLASS (parent_class)->propose_allocation (trans,
          decide_query, query)) {
    return FALSE;
  }

  if (priv->same_caps) {
    if (!gst_pad_peer_query (trans->srcpad, query))
      return FALSE;

    gst_query_add_allocation_meta (query, GST_VIDEO_META_API_TYPE, nullptr);
    gst_query_add_allocation_meta (query,
        GST_VIDEO_CROP_META_API_TYPE, nullptr);
    return TRUE;
  }

  gst_query_parse_allocation (query, &caps, nullptr);

  if (!caps)
    return FALSE;

  if (!gst_video_info_from_caps (&info, caps)) {
    GST_ERROR_OBJECT (filter, "Invalid caps %" GST_PTR_FORMAT, caps);
    return FALSE;
  }

  n_pools = gst_query_get_n_allocation_pools (query);
  for (i = 0; i < n_pools; i++) {
    gst_query_parse_nth_allocation_pool (query, i, &pool, nullptr, nullptr,
        nullptr);
    if (pool) {
      if (!GST_IS_D3D12_BUFFER_POOL (pool)) {
        gst_clear_object (&pool);
      } else {
        auto dpool = GST_D3D12_BUFFER_POOL (pool);
        if (!gst_d3d12_device_is_equal (dpool->device, filter->device))
          gst_clear_object (&pool);
      }
    }
  }

  if (!pool)
    pool = gst_d3d12_buffer_pool_new (filter->device);

  auto config = gst_buffer_pool_get_config (pool);
  gst_buffer_pool_config_add_option (config, GST_BUFFER_POOL_OPTION_VIDEO_META);

  auto d3d12_params =
      gst_buffer_pool_config_get_d3d12_allocation_params (config);
  if (!d3d12_params) {
    d3d12_params = gst_d3d12_allocation_params_new (filter->device, &info,
        GST_D3D12_ALLOCATION_FLAG_DEFAULT,
        D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS, D3D12_HEAP_FLAG_NONE);
  } else {
    gst_d3d12_allocation_params_set_resource_flags (d3d12_params,
        D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS);
    gst_d3d12_allocation_params_unset_resource_flags (d3d12_params,
        D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);
  }

  gst_buffer_pool_config_set_d3d12_allocation_params (config, d3d12_params);
  gst_d3d12_allocation_params_free (d3d12_params);

  /* size will be updated by d3d12 buffer pool */
  gst_buffer_pool_config_set_params (config, caps, 0, 0, 0);

  if (!gst_buffer_pool_set_config (pool, config)) {
    GST_ERROR_OBJECT (filter, "failed to set config");
    gst_object_unref (pool);
    return FALSE;
  }

  gst_query_add_allocation_meta (query, GST_VIDEO_META_API_TYPE, nullptr);
  gst_query_add_allocation_meta (query,
      GST_VIDEO_OVERLAY_COMPOSITION_META_API_TYPE, nullptr);
  gst_query_add_allocation_meta (query, GST_VIDEO_CROP_META_API_TYPE, nullptr);

  /* d3d12 buffer pool will update buffer size based on allocated texture,
   * get size from config again */
  config = gst_buffer_pool_get_config (pool);
  gst_buffer_pool_config_get_params (config, nullptr, &size, nullptr, nullptr);
  gst_structure_free (config);

  gst_query_add_allocation_pool (query, pool, size, 0, 0);

  gst_object_unref (pool);

  return TRUE;
}

static gboolean
gst_d3d12_base_convert_decide_allocation (GstBaseTransform * trans,
    GstQuery * query)
{
  auto filter = GST_D3D12_BASE_FILTER (trans);
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;
  GstCaps *outcaps = nullptr;
  GstBufferPool *pool = nullptr;
  guint size, min = 0, max = 0;
  GstStructure *config;
  gboolean update_pool = FALSE;
  GstVideoInfo info;

  gst_query_parse_allocation (query, &outcaps, nullptr);

  if (!outcaps)
    return FALSE;

  if (!gst_video_info_from_caps (&info, outcaps)) {
    GST_ERROR_OBJECT (filter, "Invalid caps %" GST_PTR_FORMAT, outcaps);
    return FALSE;
  }

  GstD3D12Format device_format;
  if (!gst_d3d12_device_get_format (filter->device,
          GST_VIDEO_INFO_FORMAT (&info), &device_format)) {
    GST_ERROR_OBJECT (self, "Couldn't get device foramt");
    return FALSE;
  }

  priv->downstream_supports_crop_meta = gst_query_find_allocation_meta (query,
      GST_VIDEO_CROP_META_API_TYPE, nullptr);
  GST_DEBUG_OBJECT (self, "Downstream crop meta support: %d",
      priv->downstream_supports_crop_meta);

  size = GST_VIDEO_INFO_SIZE (&info);
  if (gst_query_get_n_allocation_pools (query) > 0) {
    gst_query_parse_nth_allocation_pool (query, 0, &pool, &size, &min, &max);
    if (pool) {
      if (!GST_IS_D3D12_BUFFER_POOL (pool)) {
        gst_clear_object (&pool);
      } else {
        auto dpool = GST_D3D12_BUFFER_POOL (pool);
        if (!gst_d3d12_device_is_equal (dpool->device, filter->device))
          gst_clear_object (&pool);
      }
    }

    update_pool = TRUE;
  }

  if (!pool)
    pool = gst_d3d12_buffer_pool_new (filter->device);

  config = gst_buffer_pool_get_config (pool);
  gst_buffer_pool_config_add_option (config, GST_BUFFER_POOL_OPTION_VIDEO_META);

  D3D12_RESOURCE_FLAGS resource_flags =
      D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
  if ((device_format.format_flags & GST_D3D12_FORMAT_FLAG_OUTPUT_UAV)
      == GST_D3D12_FORMAT_FLAG_OUTPUT_UAV) {
    resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
  }

  if ((device_format.support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET) ==
      D3D12_FORMAT_SUPPORT1_RENDER_TARGET) {
    resource_flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
  }

  auto d3d12_params =
      gst_buffer_pool_config_get_d3d12_allocation_params (config);
  if (!d3d12_params) {
    d3d12_params = gst_d3d12_allocation_params_new (filter->device, &info,
        GST_D3D12_ALLOCATION_FLAG_DEFAULT, resource_flags,
        D3D12_HEAP_FLAG_SHARED);
  } else {
    gst_d3d12_allocation_params_set_resource_flags (d3d12_params,
        resource_flags);
  }

  gst_buffer_pool_config_set_d3d12_allocation_params (config, d3d12_params);
  gst_d3d12_allocation_params_free (d3d12_params);

  gst_buffer_pool_config_set_params (config, outcaps, size, min, max);
  gst_buffer_pool_set_config (pool, config);

  /* d3d12 buffer pool will update buffer size based on allocated texture,
   * get size from config again */
  config = gst_buffer_pool_get_config (pool);
  gst_buffer_pool_config_get_params (config, nullptr, &size, nullptr, nullptr);
  gst_structure_free (config);

  if (update_pool)
    gst_query_set_nth_allocation_pool (query, 0, pool, size, min, max);
  else
    gst_query_add_allocation_pool (query, pool, size, min, max);

  gst_object_unref (pool);

  return GST_BASE_TRANSFORM_CLASS (parent_class)->decide_allocation (trans,
      query);
}

static gboolean
gst_d3d12_base_convert_needs_color_convert (GstD3D12BaseConvert * self,
    const GstVideoInfo * in_info, const GstVideoInfo * out_info)
{
  auto priv = self->priv;
  const GstVideoColorimetry *in_cinfo = &in_info->colorimetry;
  const GstVideoColorimetry *out_cinfo = &out_info->colorimetry;

  if (in_cinfo->range != out_cinfo->range ||
      in_cinfo->matrix != out_cinfo->matrix) {
    return TRUE;
  }

  if (priv->primaries_mode != GST_VIDEO_PRIMARIES_MODE_NONE &&
      !gst_video_color_primaries_is_equivalent (in_cinfo->primaries,
          out_cinfo->primaries)) {
    return TRUE;
  }

  if (priv->gamma_mode != GST_VIDEO_GAMMA_MODE_NONE &&
      !gst_video_transfer_function_is_equivalent (in_cinfo->transfer,
          GST_VIDEO_INFO_COMP_DEPTH (in_info, 0), out_cinfo->transfer,
          GST_VIDEO_INFO_COMP_DEPTH (out_info, 0))) {
    return TRUE;
  }

  return FALSE;
}

static gboolean
gst_d3d12_base_convert_set_info (GstD3D12BaseFilter * filter,
    GstCaps * incaps, GstVideoInfo * in_info, GstCaps * outcaps,
    GstVideoInfo * out_info)
{
  auto self = GST_D3D12_BASE_CONVERT (filter);
  auto klass = GST_D3D12_BASE_CONVERT_GET_CLASS (self);
  auto priv = self->priv;
  gint from_dar_n, from_dar_d, to_dar_n, to_dar_d;
  gint border_offset_x = 0;
  gint border_offset_y = 0;
  gboolean need_flip = FALSE;
  gint in_width, in_height, in_par_n, in_par_d;
  gint out_width, out_height;
  GstStructure *config;

  std::lock_guard < std::mutex > lk (priv->lock);
  priv->active_method = priv->selected_method;
  priv->active_add_borders = priv->add_borders;
  priv->active_gamma_mode = priv->gamma_mode;
  priv->active_primaries_mode = priv->primaries_mode;

  GST_DEBUG_OBJECT (self, "method %d, add-borders %d, gamma-mode %d, "
      "primaries-mode %d, sampling %d", priv->active_method,
      priv->active_add_borders, priv->active_gamma_mode,
      priv->active_primaries_mode, priv->sampling_method);

  if (priv->active_method != GST_VIDEO_ORIENTATION_IDENTITY)
    need_flip = TRUE;

  if (!need_flip && gst_caps_is_equal (incaps, outcaps)) {
    priv->same_caps = TRUE;
  } else {
    priv->same_caps = FALSE;
  }

  switch (priv->selected_method) {
    case GST_VIDEO_ORIENTATION_90R:
    case GST_VIDEO_ORIENTATION_90L:
    case GST_VIDEO_ORIENTATION_UL_LR:
    case GST_VIDEO_ORIENTATION_UR_LL:
      in_width = in_info->height;
      in_height = in_info->width;
      in_par_n = in_info->par_d;
      in_par_d = in_info->par_n;
      break;
    default:
      in_width = in_info->width;
      in_height = in_info->height;
      in_par_n = in_info->par_n;
      in_par_d = in_info->par_d;
      break;
  }

  if (!gst_util_fraction_multiply (in_width,
          in_height, in_par_n, in_par_d, &from_dar_n, &from_dar_d)) {
    from_dar_n = from_dar_d = -1;
  }

  if (!gst_util_fraction_multiply (out_info->width,
          out_info->height, out_info->par_n, out_info->par_d, &to_dar_n,
          &to_dar_d)) {
    to_dar_n = to_dar_d = -1;
  }

  priv->borders_w = priv->borders_h = 0;
  if (to_dar_n != from_dar_n || to_dar_d != from_dar_d) {
    if (priv->active_add_borders) {
      gint n, d, to_h, to_w;

      if (from_dar_n != -1 && from_dar_d != -1
          && gst_util_fraction_multiply (from_dar_n, from_dar_d,
              out_info->par_d, out_info->par_n, &n, &d)) {
        to_h = gst_util_uint64_scale_int (out_info->width, d, n);
        if (to_h <= out_info->height) {
          priv->borders_h = out_info->height - to_h;
          priv->borders_w = 0;
        } else {
          to_w = gst_util_uint64_scale_int (out_info->height, n, d);
          g_assert (to_w <= out_info->width);
          priv->borders_h = 0;
          priv->borders_w = out_info->width - to_w;
        }
      } else {
        GST_WARNING_OBJECT (self, "Can't calculate borders");
      }
    } else {
      GST_INFO_OBJECT (self, "Display aspect ratio update %d/%d -> %d/%d",
          from_dar_n, from_dar_d, to_dar_n, to_dar_d);
    }
  }

  priv->ctx = nullptr;

  GST_DEBUG_OBJECT (self, "Setup convert with format %s -> %s",
      gst_video_format_to_string (GST_VIDEO_INFO_FORMAT (in_info)),
      gst_video_format_to_string (GST_VIDEO_INFO_FORMAT (out_info)));

  /* if present, these must match */
  if (in_info->interlace_mode != out_info->interlace_mode) {
    GST_ERROR_OBJECT (self, "input and output formats do not match");
    return FALSE;
  }

  if (in_width == out_info->width && in_height == out_info->height
      && in_info->finfo == out_info->finfo && priv->borders_w == 0 &&
      priv->borders_h == 0 && !need_flip &&
      !gst_d3d12_base_convert_needs_color_convert (self, in_info, out_info)) {
    priv->same_caps = TRUE;
  }

  config = gst_structure_new ("convert-config",
      GST_D3D12_CONVERTER_OPT_GAMMA_MODE,
      GST_TYPE_VIDEO_GAMMA_MODE, priv->active_gamma_mode,
      GST_D3D12_CONVERTER_OPT_PRIMARIES_MODE,
      GST_TYPE_VIDEO_PRIMARIES_MODE, priv->active_primaries_mode,
      GST_D3D12_CONVERTER_OPT_SAMPLER_FILTER,
      GST_TYPE_D3D12_CONVERTER_SAMPLER_FILTER,
      gst_d3d12_sampling_method_to_native (priv->sampling_method),
      GST_D3D12_CONVERTER_OPT_COLOR_BALANCE,
      GST_TYPE_D3D12_CONVERTER_COLOR_BALANCE, klass->enable_color_balance ?
      GST_D3D12_CONVERTER_COLOR_BALANCE_ENABLED :
      GST_D3D12_CONVERTER_COLOR_BALANCE_DISABLED,
      GST_D3D12_CONVERTER_OPT_MIP_GEN, GST_TYPE_D3D12_CONVERTER_MIP_GEN,
      klass->enable_mip_levels ? GST_D3D12_CONVERTER_MIP_GEN_ENABLED :
      GST_D3D12_CONVERTER_MIP_GEN_DISABLED, nullptr);

  auto ctx = std::make_unique < ConvertContext > (filter->device);

  ctx->conv = gst_d3d12_converter_new (filter->device, nullptr, in_info,
      out_info, nullptr, nullptr, config);
  if (!ctx->conv) {
    GST_ERROR_OBJECT (self, "Couldn't create converter");
    return FALSE;
  }

  GST_DEBUG_OBJECT (self, "from=%dx%d (par=%d/%d dar=%d/%d), size %"
      G_GSIZE_FORMAT " -> to=%dx%d (par=%d/%d dar=%d/%d borders=%d:%d), "
      "size %" G_GSIZE_FORMAT ", orientation: %d",
      in_info->width, in_info->height, in_info->par_n, in_info->par_d,
      from_dar_n, from_dar_d, in_info->size, out_info->width,
      out_info->height, out_info->par_n, out_info->par_d, to_dar_n, to_dar_d,
      priv->borders_w, priv->borders_h, out_info->size, priv->active_method);

  priv->in_rect = CD3DX12_BOX (0, 0,
      GST_VIDEO_INFO_WIDTH (in_info), GST_VIDEO_INFO_HEIGHT (in_info));
  priv->prev_in_rect = priv->in_rect;

  if (priv->borders_w) {
    border_offset_x = priv->borders_w / 2;
    priv->out_rect.left = border_offset_x;
    priv->out_rect.right = GST_VIDEO_INFO_WIDTH (out_info) - border_offset_x;
  } else {
    priv->out_rect.left = 0;
    priv->out_rect.right = GST_VIDEO_INFO_WIDTH (out_info);
  }

  if (priv->borders_h) {
    border_offset_y = priv->borders_h / 2;
    priv->out_rect.top = border_offset_y;
    priv->out_rect.bottom = GST_VIDEO_INFO_HEIGHT (out_info) - border_offset_y;
  } else {
    priv->out_rect.top = 0;
    priv->out_rect.bottom = GST_VIDEO_INFO_HEIGHT (out_info);
  }

  out_width = priv->out_rect.right - priv->out_rect.left;
  out_height = priv->out_rect.bottom - priv->out_rect.top;

  g_object_set (ctx->conv, "dest-x", (gint) priv->out_rect.left,
      "dest-y", (gint) priv->out_rect.top,
      "dest-width", out_width, "dest-height", out_height,
      "video-direction", priv->active_method, nullptr);

  if (priv->borders_w > 0 || priv->borders_h > 0) {
    g_object_set (ctx->conv, "fill-border", TRUE, "border-color",
        priv->border_color, nullptr);
  }

  if (klass->enable_color_balance) {
    priv->color_balance_updated = FALSE;
    g_object_set (ctx->conv, "hue", priv->hue,
        "saturation", priv->saturation, "brightness", priv->brightness,
        "contrast", priv->contrast, nullptr);
  }

  if (klass->enable_mip_levels) {
    priv->mip_levels_updated = FALSE;
    g_object_set (ctx->conv, "max-mip-levels", priv->mip_levels, nullptr);
  }

  priv->ctx = std::move (ctx);

  return TRUE;
}

static GstFlowReturn
gst_d3d12_base_convert_generate_output (GstBaseTransform * trans,
    GstBuffer ** buffer)
{
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;
  gboolean passthrough = priv->same_caps;

  if (!trans->queued_buf)
    return GST_FLOW_OK;

  {
    std::lock_guard < std::mutex > lk (priv->lock);
    if (priv->need_color_balance)
      passthrough = FALSE;
  }

  if (passthrough && !priv->downstream_supports_crop_meta) {
    if (gst_buffer_get_video_crop_meta (trans->queued_buf)) {
      GST_LOG_OBJECT (self,
          "Buffer has crop meta but downstream does not support crop");
      passthrough = FALSE;
    }
  }

  if (!passthrough) {
    return GST_BASE_TRANSFORM_CLASS (parent_class)->generate_output (trans,
        buffer);
  }

  *buffer = trans->queued_buf;
  trans->queued_buf = nullptr;

  return GST_FLOW_OK;
}

static gboolean
gst_d3d12_base_convert_transform_meta (GstBaseTransform * trans,
    GstBuffer * outbuf, GstMeta * meta, GstBuffer * inbuf)
{
  /* Do not copy crop meta in any case.
   *
   * 1) When input and output caps are identical,
   * - If downstream supports crop meta or crop meta is not attached on input
   *   buffer, then we do passthrough input buffers.
   *   In that case, this method must not be called already
   * - Otherwise (downstream does not support crop meta), we do crop input
   *   and copy cropped area to output buffer
   * 2) in case of input-caps != output-caps, we specify source rectangle to
   *   shader or video processor object. Then the conversion object will
   *   consider source cropping area automatically
   */
  if (meta->info->api == GST_VIDEO_CROP_META_API_TYPE)
    return FALSE;

  return GST_BASE_TRANSFORM_CLASS (parent_class)->transform_meta (trans,
      outbuf, meta, inbuf);
}

static void
gst_d3d12_base_convert_before_transform (GstBaseTransform * trans,
    GstBuffer * buffer)
{
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;
  GstCaps *in_caps;
  GstCaps *out_caps;
  GstBaseTransformClass *klass;
  gboolean update = FALSE;
  auto pts = GST_BUFFER_PTS (buffer);
  if (GST_CLOCK_TIME_IS_VALID (pts)) {
    auto stream_time = gst_segment_to_stream_time (&trans->segment,
        GST_FORMAT_TIME, pts);
    if (GST_CLOCK_TIME_IS_VALID (stream_time))
      gst_object_sync_values (GST_OBJECT (trans), stream_time);
  }

  GST_BASE_TRANSFORM_CLASS (parent_class)->before_transform (trans, buffer);

  priv->lock.lock ();
  if (priv->selected_method != priv->active_method ||
      priv->add_borders != priv->active_add_borders ||
      priv->gamma_mode != priv->active_gamma_mode ||
      priv->primaries_mode != priv->active_primaries_mode) {
    update = TRUE;
  }
  priv->lock.unlock ();

  if (!update)
    return;

  GST_DEBUG_OBJECT (self, "Updating caps for property change");

  in_caps = gst_pad_get_current_caps (GST_BASE_TRANSFORM_SINK_PAD (trans));
  if (!in_caps) {
    GST_WARNING_OBJECT (trans, "sinkpad has no current caps");
    return;
  }

  out_caps = gst_pad_get_current_caps (GST_BASE_TRANSFORM_SRC_PAD (trans));
  if (!out_caps) {
    GST_WARNING_OBJECT (trans, "srcpad has no current caps");
    gst_caps_unref (in_caps);
    return;
  }

  klass = GST_BASE_TRANSFORM_GET_CLASS (trans);
  klass->set_caps (trans, in_caps, out_caps);
  gst_caps_unref (in_caps);
  gst_caps_unref (out_caps);

  gst_base_transform_reconfigure_src (trans);
}

static GstFlowReturn
gst_d3d12_base_convert_transform (GstBaseTransform * trans, GstBuffer * inbuf,
    GstBuffer * outbuf)
{
  auto self = GST_D3D12_BASE_CONVERT (trans);
  auto priv = self->priv;
  D3D12_BOX in_rect;

  auto crop_meta = gst_buffer_get_video_crop_meta (inbuf);
  if (crop_meta) {
    GST_LOG_OBJECT (self, "Have crop rect, x:y:w:h = %d:%d:%d:%d",
        crop_meta->x, crop_meta->y, crop_meta->width, crop_meta->height);

    in_rect = CD3DX12_BOX (crop_meta->x, crop_meta->y,
        crop_meta->x + crop_meta->width, crop_meta->y + crop_meta->height);
  } else {
    in_rect = priv->in_rect;
  }

  if (in_rect != priv->in_rect) {
    priv->prev_in_rect = in_rect;
    g_object_set (priv->ctx->conv, "src-x", (gint) in_rect.left,
        "src-y", (gint) in_rect.top,
        "src-width", (gint) in_rect.right - in_rect.left,
        "src-height", (gint) in_rect.bottom - in_rect.top, nullptr);
  }

  {
    std::lock_guard < std::mutex > lk (priv->lock);
    if (priv->color_balance_updated) {
      priv->color_balance_updated = FALSE;
      g_object_set (priv->ctx->conv, "hue", priv->hue,
          "saturation", priv->saturation, "brightness", priv->brightness,
          "contrast", priv->contrast, nullptr);
    }

    if (priv->mip_levels_updated) {
      priv->mip_levels_updated = FALSE;
      g_object_set (priv->ctx->conv,
          "max-mip-levels", priv->mip_levels, nullptr);
    }
  }

  GstD3D12CmdAlloc *gst_ca;
  if (!gst_d3d12_cmd_alloc_pool_acquire (priv->ctx->ca_pool, &gst_ca)) {
    GST_ERROR_OBJECT (self, "Couldn't acquire command allocator");
    return GST_FLOW_ERROR;
  }

  auto ca = gst_d3d12_cmd_alloc_get_handle (gst_ca);

  auto hr = ca->Reset ();
  if (!gst_d3d12_result (hr, priv->ctx->device)) {
    GST_ERROR_OBJECT (self, "Couldn't reset command allocator");
    gst_d3d12_cmd_alloc_unref (gst_ca);
    return GST_FLOW_ERROR;
  }

  if (!priv->ctx->cl) {
    auto device = gst_d3d12_device_get_device_handle (priv->ctx->device);
    hr = device->CreateCommandList (0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        ca, nullptr, IID_PPV_ARGS (&priv->ctx->cl));
    if (!gst_d3d12_result (hr, priv->ctx->device)) {
      GST_ERROR_OBJECT (self, "Couldn't create command list");
      gst_d3d12_cmd_alloc_unref (gst_ca);
      return GST_FLOW_ERROR;
    }
  } else {
    hr = priv->ctx->cl->Reset (ca, nullptr);
    if (!gst_d3d12_result (hr, priv->ctx->device)) {
      GST_ERROR_OBJECT (self, "Couldn't reset command list");
      gst_d3d12_cmd_alloc_unref (gst_ca);
      return GST_FLOW_ERROR;
    }
  }

  GstD3D12FenceData *fence_data;
  gst_d3d12_fence_data_pool_acquire (priv->fence_data_pool, &fence_data);
  gst_d3d12_fence_data_push (fence_data, FENCE_NOTIFY_MINI_OBJECT (gst_ca));

  auto cq = gst_d3d12_device_get_cmd_queue (priv->ctx->device,
      D3D12_COMMAND_LIST_TYPE_DIRECT);
  auto fence = gst_d3d12_cmd_queue_get_fence_handle (cq);
  if (!gst_d3d12_converter_convert_buffer (priv->ctx->conv,
          inbuf, outbuf, fence_data, priv->ctx->cl.Get (), TRUE)) {
    GST_ERROR_OBJECT (self, "Couldn't build command list");
    gst_d3d12_fence_data_unref (fence_data);
    return GST_FLOW_ERROR;
  }

  hr = priv->ctx->cl->Close ();
  if (!gst_d3d12_result (hr, priv->ctx->device)) {
    GST_ERROR_OBJECT (self, "Couldn't close command list");
    gst_d3d12_fence_data_unref (fence_data);
    return GST_FLOW_ERROR;
  }

  ID3D12CommandList *cmd_list[] = { priv->ctx->cl.Get () };

  hr = gst_d3d12_cmd_queue_execute_command_lists (cq,
      1, cmd_list, &priv->ctx->fence_val);
  if (!gst_d3d12_result (hr, priv->ctx->device)) {
    GST_ERROR_OBJECT (self, "Couldn't execute command list");
    gst_d3d12_fence_data_unref (fence_data);
    return GST_FLOW_ERROR;
  }

  gst_d3d12_buffer_set_fence (outbuf, fence, priv->ctx->fence_val, FALSE);
  gst_d3d12_cmd_queue_set_notify (cq, priv->ctx->fence_val,
      FENCE_NOTIFY_MINI_OBJECT (fence_data));

  priv->ctx->scheduled.push (priv->ctx->fence_val);

  auto completed = gst_d3d12_device_get_completed_value (priv->ctx->device,
      D3D12_COMMAND_LIST_TYPE_DIRECT);
  while (!priv->ctx->scheduled.empty ()) {
    if (priv->ctx->scheduled.front () > completed)
      break;

    priv->ctx->scheduled.pop ();
  }

  auto async_depth = priv->async_depth.load ();
  if (async_depth > 0 && priv->ctx->scheduled.size () > async_depth) {
    auto fence_to_wait = priv->ctx->scheduled.front ();
    priv->ctx->scheduled.pop ();
    gst_d3d12_device_fence_wait (priv->ctx->device,
        D3D12_COMMAND_LIST_TYPE_DIRECT, fence_to_wait);
  }

  return GST_FLOW_OK;
}

enum
{
  PROP_CONVERT_ADD_BORDERS = 1,
  PROP_CONVERT_BORDER_COLOR,
  PROP_CONVERT_VIDEO_DIRECTION,
  PROP_CONVERT_GAMMA_MODE,
  PROP_CONVERT_PRIMARIES_MODE,
  PROP_CONVERT_HUE,
  PROP_CONVERT_SATURATION,
  PROP_CONVERT_BRIGHTNESS,
  PROP_CONVERT_CONTRAST,
  PROP_CONVERT_MAX_MIP_LEVELS,
};

struct _GstD3D12Convert
{
  GstD3D12BaseConvert parent;
};

static void
gst_d3d12_convert_video_direction_interface_init (GstVideoDirectionInterface *
    iface)
{
}

static const GList *
gst_d3d12_base_convert_color_balance_list_channels (GstColorBalance * iface)
{
  auto self = GST_D3D12_BASE_CONVERT (iface);
  auto priv = self->priv;

  return priv->color_balance_channels;
}

static void
gst_d3d12_base_convert_color_balance_set_value (GstColorBalance * iface,
    GstColorBalanceChannel * channel, gint value)
{
  auto self = GST_D3D12_BASE_CONVERT (iface);
  auto priv = self->priv;

  gdouble new_val;
  gboolean changed = FALSE;

  g_return_if_fail (channel->label);

  {
    std::lock_guard < std::mutex > lk (priv->lock);
    if (!g_ascii_strcasecmp (channel->label, "HUE")) {
      new_val = (value + 1000.0) * 2.0 / 2000.0 - 1.0;
      changed = priv->hue != new_val;
    } else if (!g_ascii_strcasecmp (channel->label, "SATURATION")) {
      new_val = (value + 1000.0) * 2.0 / 2000.0;
      changed = priv->saturation != new_val;
    } else if (!g_ascii_strcasecmp (channel->label, "BRIGHTNESS")) {
      new_val = (value + 1000.0) * 2.0 / 2000.0 - 1.0;
      changed = priv->brightness != new_val;
    } else if (!g_ascii_strcasecmp (channel->label, "CONTRAST")) {
      new_val = (value + 1000.0) * 2.0 / 2000.0;
      changed = priv->contrast != new_val;
    }
  }

  if (changed) {
    gst_color_balance_value_changed (iface, channel,
        gst_color_balance_get_value (iface, channel));
  }
}

static gint
gst_d3d12_base_convert_color_balance_get_value (GstColorBalance * iface,
    GstColorBalanceChannel * channel)
{
  auto self = GST_D3D12_BASE_CONVERT (iface);
  auto priv = self->priv;
  gint value = 0;

  g_return_val_if_fail (channel->label, 0);

  {
    std::lock_guard < std::mutex > lock (priv->lock);
    if (!g_ascii_strcasecmp (channel->label, "HUE")) {
      auto hue = priv->hue;
      value = static_cast < gint > ((hue + 1) * 2000.0 / 2.0 - 1000.0);
    } else if (!g_ascii_strcasecmp (channel->label, "SATURATION")) {
      auto saturation = priv->saturation;
      value = static_cast < gint > (saturation * 2000.0 / 2.0 - 1000.0);
    } else if (!g_ascii_strcasecmp (channel->label, "BRIGHTNESS")) {
      auto brightness = priv->brightness;
      value = static_cast < gint > ((brightness + 1) * 2000.0 / 2.0 - 1000.0);
    } else if (!g_ascii_strcasecmp (channel->label, "CONTRAST")) {
      auto contrast = priv->contrast;
      value = static_cast < gint > (contrast * 2000.0 / 2.0 - 1000.0);
    }
  }

  return value;
}

static GstColorBalanceType
gst_d3d12_base_convert_color_balance_get_balance_type (GstColorBalance * iface)
{
  return GST_COLOR_BALANCE_HARDWARE;
}

static void
gst_d3d12_base_convert_color_balance_init (GstColorBalanceInterface * iface)
{
  iface->list_channels = gst_d3d12_base_convert_color_balance_list_channels;
  iface->set_value = gst_d3d12_base_convert_color_balance_set_value;
  iface->get_value = gst_d3d12_base_convert_color_balance_get_value;
  iface->get_balance_type =
      gst_d3d12_base_convert_color_balance_get_balance_type;
}

static void
gst_d3d12_base_convert_update_color_balance (GstD3D12BaseConvert * self,
    const gchar * name, gdouble * prev, gdouble value)
{
  auto priv = self->priv;
  gboolean updated = FALSE;

  {
    std::lock_guard < std::mutex > lk (priv->lock);
    if (*prev != value) {
      *prev = value;
      priv->color_balance_updated = TRUE;
      priv->need_color_balance =
          gst_d3d12_converter_is_color_balance_needed (priv->hue,
          priv->saturation, priv->brightness, priv->contrast);
      updated = TRUE;
    }
  }

  if (updated) {
    GList *iter = priv->color_balance_channels;
    while (iter) {
      auto ch = (GstColorBalanceChannel *) iter->data;
      if (g_ascii_strcasecmp (ch->label, name) == 0) {
        auto iface = GST_COLOR_BALANCE (self);
        gst_color_balance_value_changed (iface, ch,
            gst_color_balance_get_value (iface, ch));
        break;
      }

      iter = g_list_next (iter);
    }
  }
}

static void
gst_d3d12_base_convert_set_hue (GstD3D12BaseConvert * self, gdouble value)
{
  auto priv = self->priv;
  gst_d3d12_base_convert_update_color_balance (self, "HUE", &priv->hue, value);
}

static void
gst_d3d12_base_convert_set_saturation (GstD3D12BaseConvert * self,
    gdouble value)
{
  auto priv = self->priv;
  gst_d3d12_base_convert_update_color_balance (self,
      "SATURATION", &priv->saturation, value);
}

static void
gst_d3d12_base_convert_set_brightness (GstD3D12BaseConvert * self,
    gdouble value)
{
  auto priv = self->priv;
  gst_d3d12_base_convert_update_color_balance (self,
      "BRIGHTNESS", &priv->brightness, value);
}

static void
gst_d3d12_base_convert_set_contrast (GstD3D12BaseConvert * self, gdouble value)
{
  auto priv = self->priv;
  gst_d3d12_base_convert_update_color_balance (self,
      "CONTRAST", &priv->contrast, value);
}

static void
gst_d3d12_base_convert_set_mip_levels (GstD3D12BaseConvert * self, guint value)
{
  auto priv = self->priv;
  std::lock_guard < std::mutex > lk (priv->lock);
  if (priv->mip_levels != value) {
    priv->mip_levels_updated = TRUE;
    priv->mip_levels = value;
  }
}

G_DEFINE_TYPE_WITH_CODE (GstD3D12Convert, gst_d3d12_convert,
    GST_TYPE_D3D12_BASE_CONVERT,
    G_IMPLEMENT_INTERFACE (GST_TYPE_VIDEO_DIRECTION,
        gst_d3d12_convert_video_direction_interface_init);
    G_IMPLEMENT_INTERFACE (GST_TYPE_COLOR_BALANCE,
        gst_d3d12_base_convert_color_balance_init));

static void gst_d3d12_convert_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_d3d12_convert_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static gboolean gst_d3d12_convert_sink_event (GstBaseTransform * trans,
    GstEvent * event);

static void
gst_d3d12_convert_class_init (GstD3D12ConvertClass * klass)
{
  auto object_class = G_OBJECT_CLASS (klass);
  auto element_class = GST_ELEMENT_CLASS (klass);
  auto trans_class = GST_BASE_TRANSFORM_CLASS (klass);
  auto conv_class = GST_D3D12_BASE_CONVERT_CLASS (klass);

  object_class->set_property = gst_d3d12_convert_set_property;
  object_class->get_property = gst_d3d12_convert_get_property;

  g_object_class_install_property (object_class, PROP_CONVERT_ADD_BORDERS,
      g_param_spec_boolean ("add-borders", "Add Borders",
          "Add black borders if necessary to keep the display aspect ratio",
          DEFAULT_ADD_BORDERS, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_CONVERT_BORDER_COLOR,
      g_param_spec_uint64 ("border-color", "Border color",
          "Border color to use in ARGB64 format", 0, G_MAXUINT64,
          DEFAULT_BORDER_COLOR, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_override_property (object_class, PROP_CONVERT_VIDEO_DIRECTION,
      "video-direction");

  g_object_class_install_property (object_class, PROP_CONVERT_GAMMA_MODE,
      g_param_spec_enum ("gamma-mode", "Gamma mode",
          "Gamma conversion mode", GST_TYPE_VIDEO_GAMMA_MODE,
          DEFAULT_GAMMA_MODE, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_CONVERT_PRIMARIES_MODE,
      g_param_spec_enum ("primaries-mode", "Primaries Mode",
          "Primaries conversion mode", GST_TYPE_VIDEO_PRIMARIES_MODE,
          DEFAULT_PRIMARIES_MODE, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Convert:hue:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONVERT_HUE,
      g_param_spec_double ("hue", "Hue", "hue", -1.0, 1.0, DEFAULT_HUE,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Convert:saturation:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONVERT_SATURATION,
      g_param_spec_double ("saturation", "Saturation", "saturation", 0.0, 2.0,
          DEFAULT_SATURATION,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Convert:brightness:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONVERT_BRIGHTNESS,
      g_param_spec_double ("brightness", "Brightness", "brightness", -1.0, 1.0,
          DEFAULT_BRIGHTNESS,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Convert:contrast:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONVERT_CONTRAST,
      g_param_spec_double ("contrast", "Contrast", "contrast", 0.0, 2.0,
          DEFAULT_CONTRAST,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Convert:max-mip-levels:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONVERT_MAX_MIP_LEVELS,
      g_param_spec_uint ("max-mip-levels", "Max Mip Levels",
          "Maximum mip levels of shader resource to create "
          "if viewport size is smaller than shader resource "
          "(0 = maximum level)", 0, G_MAXUINT16, DEFAULT_MAX_MIP_LEVELS,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  gst_element_class_set_static_metadata (element_class,
      "Direct3D12 Converter",
      "Filter/Converter/Scaler/Effect/Video/Hardware",
      "Performs resizing, colorspace conversion, cropping, flipping/rotating "
      "and adjusts hue/saturation/brightness/contrast using Direct3D12",
      "Seungha Yang <seungha@centricular.com>");

  trans_class->sink_event = GST_DEBUG_FUNCPTR (gst_d3d12_convert_sink_event);

  conv_class->enable_color_balance = TRUE;
  conv_class->enable_mip_levels = TRUE;
}

static void
gst_d3d12_convert_init (GstD3D12Convert * self)
{
}

static void
gst_d3d12_convert_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_BASE_CONVERT (object);

  switch (prop_id) {
    case PROP_CONVERT_ADD_BORDERS:
      gst_d3d12_base_convert_set_add_border (self, g_value_get_boolean (value));
      break;
    case PROP_CONVERT_BORDER_COLOR:
      gst_d3d12_base_convert_set_border_color (self,
          g_value_get_uint64 (value));
      break;
    case PROP_CONVERT_VIDEO_DIRECTION:
      gst_d3d12_base_convert_set_orientation (self,
          (GstVideoOrientationMethod) g_value_get_enum (value), FALSE);
      break;
    case PROP_CONVERT_GAMMA_MODE:
      gst_d3d12_base_convert_set_gamma_mode (self,
          (GstVideoGammaMode) g_value_get_enum (value));
      break;
    case PROP_CONVERT_PRIMARIES_MODE:
      gst_d3d12_base_convert_set_primaries_mode (self,
          (GstVideoPrimariesMode) g_value_get_enum (value));
      break;
    case PROP_CONVERT_HUE:
      gst_d3d12_base_convert_set_hue (self, g_value_get_double (value));
      break;
    case PROP_CONVERT_SATURATION:
      gst_d3d12_base_convert_set_saturation (self, g_value_get_double (value));
      break;
    case PROP_CONVERT_BRIGHTNESS:
      gst_d3d12_base_convert_set_brightness (self, g_value_get_double (value));
      break;
    case PROP_CONVERT_CONTRAST:
      gst_d3d12_base_convert_set_contrast (self, g_value_get_double (value));
      break;
    case PROP_CONVERT_MAX_MIP_LEVELS:
      gst_d3d12_base_convert_set_mip_levels (self, g_value_get_uint (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_d3d12_convert_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_BASE_CONVERT (object);
  auto priv = self->priv;

  std::lock_guard < std::mutex > lk (priv->lock);
  switch (prop_id) {
    case PROP_CONVERT_ADD_BORDERS:
      g_value_set_boolean (value, priv->add_borders);
      break;
    case PROP_CONVERT_BORDER_COLOR:
      g_value_set_uint64 (value, priv->border_color);
      break;
    case PROP_CONVERT_VIDEO_DIRECTION:
      g_value_set_enum (value, priv->method);
      break;
    case PROP_CONVERT_GAMMA_MODE:
      g_value_set_enum (value, priv->gamma_mode);
      break;
    case PROP_CONVERT_PRIMARIES_MODE:
      g_value_set_enum (value, priv->primaries_mode);
      break;
    case PROP_CONVERT_HUE:
      g_value_set_double (value, priv->hue);
      break;
    case PROP_CONVERT_SATURATION:
      g_value_set_double (value, priv->saturation);
      break;
    case PROP_CONVERT_BRIGHTNESS:
      g_value_set_double (value, priv->brightness);
      break;
    case PROP_CONVERT_CONTRAST:
      g_value_set_double (value, priv->contrast);
      break;
    case PROP_CONVERT_MAX_MIP_LEVELS:
      g_value_set_uint (value, priv->mip_levels);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static gboolean
gst_d3d12_convert_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  auto base = GST_D3D12_BASE_CONVERT (trans);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_TAG:{
      GstTagList *taglist;
      GstVideoOrientationMethod method = GST_VIDEO_ORIENTATION_IDENTITY;

      gst_event_parse_tag (event, &taglist);
      if (gst_video_orientation_from_tag (taglist, &method))
        gst_d3d12_base_convert_set_orientation (base, method, TRUE);
      break;
    }
    default:
      break;
  }

  return
      GST_BASE_TRANSFORM_CLASS (gst_d3d12_base_convert_parent_class)->sink_event
      (trans, event);
}

enum
{
  PROP_COLOR_CONVERT_GAMMA_MODE = 1,
  PROP_COLOR_CONVERT_PRIMARIES_MODE,
  PROP_COLOR_CONVERT_HUE,
  PROP_COLOR_CONVERT_SATURATION,
  PROP_COLOR_CONVERT_BRIGHTNESS,
  PROP_COLOR_CONVERT_CONTRAST,
};

struct _GstD3D12ColorConvert
{
  GstD3D12BaseConvert parent;
};

static void gst_d3d12_color_convert_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_d3d12_color_convert_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);
static GstCaps *gst_d3d12_color_convert_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter);
static GstCaps *gst_d3d12_color_convert_fixate_caps (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps);

G_DEFINE_TYPE_WITH_CODE (GstD3D12ColorConvert, gst_d3d12_color_convert,
    GST_TYPE_D3D12_BASE_CONVERT,
    G_IMPLEMENT_INTERFACE (GST_TYPE_COLOR_BALANCE,
        gst_d3d12_base_convert_color_balance_init));

static void
gst_d3d12_color_convert_class_init (GstD3D12ColorConvertClass * klass)
{
  auto object_class = G_OBJECT_CLASS (klass);
  auto element_class = GST_ELEMENT_CLASS (klass);
  auto trans_class = GST_BASE_TRANSFORM_CLASS (klass);
  auto conv_class = GST_D3D12_BASE_CONVERT_CLASS (klass);

  object_class->set_property = gst_d3d12_color_convert_set_property;
  object_class->get_property = gst_d3d12_color_convert_get_property;

  g_object_class_install_property (object_class, PROP_COLOR_CONVERT_GAMMA_MODE,
      g_param_spec_enum ("gamma-mode", "Gamma mode",
          "Gamma conversion mode", GST_TYPE_VIDEO_GAMMA_MODE,
          DEFAULT_GAMMA_MODE, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class,
      PROP_COLOR_CONVERT_PRIMARIES_MODE,
      g_param_spec_enum ("primaries-mode", "Primaries Mode",
          "Primaries conversion mode", GST_TYPE_VIDEO_PRIMARIES_MODE,
          DEFAULT_PRIMARIES_MODE, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12ColorConvert:hue:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_COLOR_CONVERT_HUE,
      g_param_spec_double ("hue", "Hue", "hue", -1.0, 1.0, DEFAULT_HUE,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12ColorConvert:saturation:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_COLOR_CONVERT_SATURATION,
      g_param_spec_double ("saturation", "Saturation", "saturation", 0.0, 2.0,
          DEFAULT_SATURATION,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12ColorConvert:brightness:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_COLOR_CONVERT_BRIGHTNESS,
      g_param_spec_double ("brightness", "Brightness", "brightness", -1.0, 1.0,
          DEFAULT_BRIGHTNESS,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12ColorConvert:contrast:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_COLOR_CONVERT_CONTRAST,
      g_param_spec_double ("contrast", "Contrast", "contrast", 0.0, 2.0,
          DEFAULT_CONTRAST,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  gst_element_class_set_static_metadata (element_class,
      "Direct3D12 Colorspace Converter",
      "Filter/Converter/Video/Hardware",
      "Converts colorspace and adjusts hue/saturation/brightness/contrast "
      "using Direct3D12", "Seungha Yang <seungha@centricular.com>");

  trans_class->transform_caps =
      GST_DEBUG_FUNCPTR (gst_d3d12_color_convert_transform_caps);
  trans_class->fixate_caps =
      GST_DEBUG_FUNCPTR (gst_d3d12_color_convert_fixate_caps);

  conv_class->enable_color_balance = TRUE;
}

static void
gst_d3d12_color_convert_init (GstD3D12ColorConvert * self)
{
}

static void
gst_d3d12_color_convert_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_BASE_CONVERT (object);

  switch (prop_id) {
    case PROP_COLOR_CONVERT_GAMMA_MODE:
      gst_d3d12_base_convert_set_gamma_mode (self,
          (GstVideoGammaMode) g_value_get_enum (value));
      break;
    case PROP_COLOR_CONVERT_PRIMARIES_MODE:
      gst_d3d12_base_convert_set_primaries_mode (self,
          (GstVideoPrimariesMode) g_value_get_enum (value));
      break;
    case PROP_COLOR_CONVERT_HUE:
      gst_d3d12_base_convert_set_hue (self, g_value_get_double (value));
      break;
    case PROP_COLOR_CONVERT_SATURATION:
      gst_d3d12_base_convert_set_saturation (self, g_value_get_double (value));
      break;
    case PROP_COLOR_CONVERT_BRIGHTNESS:
      gst_d3d12_base_convert_set_brightness (self, g_value_get_double (value));
      break;
    case PROP_COLOR_CONVERT_CONTRAST:
      gst_d3d12_base_convert_set_contrast (self, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_d3d12_color_convert_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  auto base = GST_D3D12_BASE_CONVERT (object);
  auto priv = base->priv;

  std::lock_guard < std::mutex > lk (priv->lock);
  switch (prop_id) {
    case PROP_COLOR_CONVERT_GAMMA_MODE:
      g_value_set_enum (value, priv->gamma_mode);
      break;
    case PROP_COLOR_CONVERT_PRIMARIES_MODE:
      g_value_set_enum (value, priv->primaries_mode);
      break;
    case PROP_COLOR_CONVERT_HUE:
      g_value_set_double (value, priv->hue);
      break;
    case PROP_COLOR_CONVERT_SATURATION:
      g_value_set_double (value, priv->saturation);
      break;
    case PROP_COLOR_CONVERT_BRIGHTNESS:
      g_value_set_double (value, priv->brightness);
      break;
    case PROP_COLOR_CONVERT_CONTRAST:
      g_value_set_double (value, priv->contrast);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstCaps *
gst_d3d12_color_convert_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter)
{
  auto ret = gst_d3d12_base_convert_caps_remove_format_info (caps);

  if (filter) {
    auto tmp = gst_caps_intersect_full (filter, ret, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref (ret);
    ret = tmp;
  }

  GST_DEBUG_OBJECT (trans, "transformed %" GST_PTR_FORMAT " into %"
      GST_PTR_FORMAT, caps, ret);

  return ret;
}

static GstCaps *
gst_d3d12_color_convert_fixate_caps (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  GST_DEBUG_OBJECT (base,
      "trying to fixate othercaps %" GST_PTR_FORMAT " based on caps %"
      GST_PTR_FORMAT, othercaps, caps);

  auto format = gst_d3d12_base_convert_get_fixed_format (base, direction, caps,
      othercaps);
  gst_caps_unref (othercaps);

  if (gst_caps_is_empty (format)) {
    GST_ERROR_OBJECT (base, "Could not convert formats");
  } else {
    GST_DEBUG_OBJECT (base, "fixated othercaps to %" GST_PTR_FORMAT, format);
  }

  return format;
}

enum
{
  PROP_SCALE_ADD_BORDERS = 1,
  PROP_SCALE_BORDER_COLOR,
  PROP_SCALE_MAX_MIP_LEVELS,
};

struct _GstD3D12Scale
{
  GstD3D12BaseConvert parent;
};

static void gst_d3d12_scale_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_d3d12_scale_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static GstCaps *gst_d3d12_scale_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter);
static GstCaps *gst_d3d12_scale_fixate_caps (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps);

G_DEFINE_TYPE (GstD3D12Scale, gst_d3d12_scale, GST_TYPE_D3D12_BASE_CONVERT);

static void
gst_d3d12_scale_class_init (GstD3D12ScaleClass * klass)
{
  auto object_class = G_OBJECT_CLASS (klass);
  auto element_class = GST_ELEMENT_CLASS (klass);
  auto trans_class = GST_BASE_TRANSFORM_CLASS (klass);
  auto conv_class = GST_D3D12_BASE_CONVERT_CLASS (klass);

  object_class->set_property = gst_d3d12_scale_set_property;
  object_class->get_property = gst_d3d12_scale_get_property;

  g_object_class_install_property (object_class, PROP_SCALE_ADD_BORDERS,
      g_param_spec_boolean ("add-borders", "Add Borders",
          "Add black borders if necessary to keep the display aspect ratio",
          DEFAULT_ADD_BORDERS, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_SCALE_BORDER_COLOR,
      g_param_spec_uint64 ("border-color", "Border color",
          "Border color to use in ARGB64 format", 0, G_MAXUINT64,
          DEFAULT_BORDER_COLOR, (GParamFlags) (GST_PARAM_MUTABLE_PLAYING |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12Scale:max-mip-levels:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_SCALE_MAX_MIP_LEVELS,
      g_param_spec_uint ("max-mip-levels", "Max Mip Levels",
          "Maximum mip levels of shader resource to create "
          "if viewport size is smaller than shader resource "
          "(0 = maximum level)", 0, G_MAXUINT16, DEFAULT_MAX_MIP_LEVELS,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  gst_element_class_set_static_metadata (element_class,
      "Direct3D12 Scaler",
      "Filter/Converter/Video/Scaler/Hardware",
      "Resizes video using Direct3D12",
      "Seungha Yang <seungha@centricular.com>");

  trans_class->transform_caps =
      GST_DEBUG_FUNCPTR (gst_d3d12_scale_transform_caps);
  trans_class->fixate_caps = GST_DEBUG_FUNCPTR (gst_d3d12_scale_fixate_caps);

  conv_class->enable_mip_levels = TRUE;
}

static void
gst_d3d12_scale_init (GstD3D12Scale * self)
{
}

static void
gst_d3d12_scale_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  auto base = GST_D3D12_BASE_CONVERT (object);

  switch (prop_id) {
    case PROP_SCALE_ADD_BORDERS:
      gst_d3d12_base_convert_set_add_border (base, g_value_get_boolean (value));
      break;
    case PROP_SCALE_BORDER_COLOR:
      gst_d3d12_base_convert_set_border_color (base,
          g_value_get_uint64 (value));
      break;
    case PROP_SCALE_MAX_MIP_LEVELS:
      gst_d3d12_base_convert_set_mip_levels (base, g_value_get_uint (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_d3d12_scale_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  auto base = GST_D3D12_BASE_CONVERT (object);
  auto priv = base->priv;

  std::lock_guard < std::mutex > lk (priv->lock);
  switch (prop_id) {
    case PROP_SCALE_ADD_BORDERS:
      g_value_set_boolean (value, priv->add_borders);
      break;
    case PROP_SCALE_BORDER_COLOR:
      g_value_set_uint64 (value, priv->border_color);
      break;
    case PROP_SCALE_MAX_MIP_LEVELS:
      g_value_set_uint (value, priv->mip_levels);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstCaps *
gst_d3d12_scale_transform_caps (GstBaseTransform *
    trans, GstPadDirection direction, GstCaps * caps, GstCaps * filter)
{
  auto ret = gst_d3d12_base_convert_caps_rangify_size_info (caps);

  if (filter) {
    auto tmp = gst_caps_intersect_full (filter, ret, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref (ret);
    ret = tmp;
  }

  GST_DEBUG_OBJECT (trans, "transformed %" GST_PTR_FORMAT " into %"
      GST_PTR_FORMAT, caps, ret);

  return ret;
}

static GstCaps *
gst_d3d12_scale_fixate_caps (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  GST_DEBUG_OBJECT (base,
      "trying to fixate othercaps %" GST_PTR_FORMAT " based on caps %"
      GST_PTR_FORMAT, othercaps, caps);

  othercaps =
      gst_d3d12_base_convert_fixate_size (base, direction, caps, othercaps);

  GST_DEBUG_OBJECT (base, "fixated othercaps to %" GST_PTR_FORMAT, othercaps);

  return othercaps;
}
