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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstd3d12videosink.h"
#include "gstd3d12pluginutils.h"
#include "gstd3d12window.h"
#include <mutex>
#include <atomic>
#include <string>

/**
 * GstD3D12VideoSinkDisplayFormat:
 *
 * Swapchain display format
 *
 * Since: 1.26
 */
#define GST_TYPE_D3D12_VIDEO_SINK_DISPLAY_FORMAT (gst_d3d12_video_sink_display_format_type())
static GType
gst_d3d12_video_sink_display_format_type (void)
{
  static GType format_type = 0;

  GST_D3D12_CALL_ONCE_BEGIN {
    static const GEnumValue format_types[] = {
      /**
       * GstD3D12VideoSinkDisplayFormat::unknown:
       *
       * Since: 1.26
       */
      {DXGI_FORMAT_UNKNOWN, "DXGI_FORMAT_UNKNOWN", "unknown"},

      /**
       * GstD3D12VideoSinkDisplayFormat::r10g10b10a2-unorm:
       *
       * Since: 1.26
       */
      {DXGI_FORMAT_R10G10B10A2_UNORM,
          "DXGI_FORMAT_R10G10B10A2_UNORM", "r10g10b10a2-unorm"},

      /**
       * GstD3D12VideoSinkDisplayFormat::r8g8b8a8-unorm:
       *
       * Since: 1.26
       */
      {DXGI_FORMAT_R8G8B8A8_UNORM,
          "DXGI_FORMAT_R8G8B8A8_UNORM", "r8g8b8a8-unorm"},

      /**
       * GstD3D12VideoSinkDisplayFormat::b8g8r8a8-unorm:
       *
       * Since: 1.26
       */
      {DXGI_FORMAT_B8G8R8A8_UNORM,
          "DXGI_FORMAT_B8G8R8A8_UNORM", "b8g8r8a8-unorm"},
      {0, nullptr, nullptr},
    };

    format_type = g_enum_register_static ("GstD3D12VideoSinkDisplayFormat",
        format_types);
  } GST_D3D12_CALL_ONCE_END;

  return format_type;
}

enum
{
  PROP_0,
  PROP_ADAPTER,
  PROP_FORCE_ASPECT_RATIO,
  PROP_ENABLE_NAVIGATION_EVENTS,
  PROP_ROTATE_METHOD,
  PROP_FULLSCREEN_ON_ALT_ENTER,
  PROP_FULLSCREEN,
  PROP_MSAA,
  PROP_REDRAW_ON_UPDATE,
  PROP_FOV,
  PROP_ORTHO,
  PROP_ROTATION_X,
  PROP_ROTATION_Y,
  PROP_ROTATION_Z,
  PROP_SCALE_X,
  PROP_SCALE_Y,
  PROP_SAMPLING_METHOD,
  PROP_GAMMA_MODE,
  PROP_PRIMARIES_MODE,
  PROP_OVERLAY_MODE,
  PROP_DISPLAY_FORMAT,
  PROP_ERROR_ON_CLOSED,
  PROP_EXTERNAL_WINDOW_ONLY,
  PROP_DIRECT_SWAPCHAIN,
  PROP_HUE,
  PROP_SATURATION,
  PROP_BRIGHTNESS,
  PROP_CONTRAST,
  PROP_MAX_MIP_LEVELS,
};

#define DEFAULT_ADAPTER -1
#define DEFAULT_FORCE_ASPECT_RATIO TRUE
#define DEFAULT_ENABLE_NAVIGATION_EVENTS TRUE
#define DEFAULT_ROTATE_METHOD GST_VIDEO_ORIENTATION_IDENTITY
#define DEFAULT_FULLSCREEN_ON_ALT_ENTER FALSE
#define DEFAULT_FULLSCREEN FALSE
#define DEFAULT_MSAA GST_D3D12_MSAA_DISABLED
#define DEFAULT_REDROW_ON_UPDATE TRUE
#define DEFAULT_ROTATION 0.0f
#define DEFAULT_SCALE 1.0f
#define DEFAULT_FOV 90.0f
#define DEFAULT_ORTHO FALSE
#define DEFAULT_SAMPLING_METHOD GST_D3D12_SAMPLING_METHOD_BILINEAR
#define DEFAULT_GAMMA_MODE GST_VIDEO_GAMMA_MODE_NONE
#define DEFAULT_PRIMARIES_MODE GST_VIDEO_PRIMARIES_MODE_NONE
#define DEFAULT_OVERLAY_MODE GST_D3D12_WINDOW_OVERLAY_NONE
#define DEFAULT_DISPLAY_FORMAT DXGI_FORMAT_UNKNOWN
#define DEFAULT_ERROR_ON_CLOSED TRUE
#define DEFAULT_EXTERNAL_WINDOW_ONLY FALSE
#define DEFAULT_DIRECT_SWAPCHAIN FALSE
#define DEFAULT_HUE 0.0
#define DEFAULT_SATURATION 1.0
#define DEFAULT_BRIGHTNESS 0.0
#define DEFAULT_CONTRAST 1.0
#define DEFAULT_MAX_MIP_LEVELS 1

enum
{
  SIGNAL_OVERLAY,
  SIGNAL_LAST
};

static guint d3d12_video_sink_signals[SIGNAL_LAST] = { 0, };

static GstStaticPadTemplate sink_template =
    GST_STATIC_PAD_TEMPLATE ("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
    GST_STATIC_CAPS (GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY, GST_D3D12_ALL_FORMATS) "; "
        GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY ","
            GST_CAPS_FEATURE_META_GST_VIDEO_OVERLAY_COMPOSITION,
            GST_D3D12_ALL_FORMATS) ";"
        GST_VIDEO_CAPS_MAKE (GST_D3D12_ALL_FORMATS) "; "
        GST_VIDEO_CAPS_MAKE_WITH_FEATURES
        (GST_CAPS_FEATURE_MEMORY_SYSTEM_MEMORY ","
            GST_CAPS_FEATURE_META_GST_VIDEO_OVERLAY_COMPOSITION,
            GST_D3D12_ALL_FORMATS)));

GST_DEBUG_CATEGORY_STATIC (gst_d3d12_video_sink_debug);
#define GST_CAT_DEFAULT gst_d3d12_video_sink_debug

/* *INDENT-OFF* */
struct GstD3D12VideoSinkPrivate
{
  GstD3D12VideoSinkPrivate ()
  {
    const gchar *channels[4] = { "HUE", "SATURATION",
      "BRIGHTNESS", "CONTRAST"
    };
    window = gst_d3d12_window_new ();
    convert_config = gst_structure_new_empty ("convert-config");
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

  ~GstD3D12VideoSinkPrivate ()
  {
    gst_structure_free (convert_config);
    gst_clear_caps (&caps);
    gst_clear_object (&window);
    if (pool) {
      gst_buffer_pool_set_active (pool, FALSE);
      gst_object_unref (pool);
    }

    auto iter = color_balance_channels;
    while (iter) {
      g_object_unref (iter->data);
      iter = iter->next;
    }

    g_list_free (color_balance_channels);
  }

  GstD3D12Window *window;
  guintptr window_handle = 0;
  gboolean window_handle_updated = FALSE;

  std::recursive_mutex context_lock;

  GstVideoInfo info;
  GstCaps *caps = nullptr;
  gboolean update_window = FALSE;
  GstBufferPool *pool = nullptr;
  GstStructure *convert_config;

  gboolean warn_closed_window = FALSE;
  gboolean window_open_called = FALSE;

  GList *color_balance_channels = nullptr;
  std::atomic<bool> sync_in_progress = { false };

  std::recursive_mutex lock;
  /* properties */
  std::atomic<gint> adapter = { DEFAULT_ADAPTER };
  gboolean force_aspect_ratio = DEFAULT_FORCE_ASPECT_RATIO;
  gboolean enable_navigation = DEFAULT_ENABLE_NAVIGATION_EVENTS;
  GstVideoOrientationMethod orientation = DEFAULT_ROTATE_METHOD;
  GstVideoOrientationMethod orientation_from_tag = DEFAULT_ROTATE_METHOD;
  GstVideoOrientationMethod orientation_selected = DEFAULT_ROTATE_METHOD;
  gboolean fullscreen_on_alt_enter = DEFAULT_FULLSCREEN_ON_ALT_ENTER;
  gboolean fullscreen = DEFAULT_FULLSCREEN;
  GstD3D12MSAAMode msaa = DEFAULT_MSAA;
  gboolean redraw_on_update = DEFAULT_REDROW_ON_UPDATE;
  gfloat fov = DEFAULT_FOV;
  gboolean ortho = DEFAULT_ORTHO;
  gfloat rotation_x = DEFAULT_ROTATION;
  gfloat rotation_y = DEFAULT_ROTATION;
  gfloat rotation_z = DEFAULT_ROTATION;
  gfloat scale_x = DEFAULT_SCALE;
  gfloat scale_y = DEFAULT_SCALE;
  GstVideoGammaMode gamma_mode = DEFAULT_GAMMA_MODE;
  GstVideoPrimariesMode primaries_mode = DEFAULT_PRIMARIES_MODE;
  GstD3D12SamplingMethod sampling_method = DEFAULT_SAMPLING_METHOD;
  GstD3D12WindowOverlayMode overlay_mode = DEFAULT_OVERLAY_MODE;
  DXGI_FORMAT display_format = DEFAULT_DISPLAY_FORMAT;
  std::atomic<gboolean> error_on_closed = { DEFAULT_ERROR_ON_CLOSED };
  gboolean external_only = DEFAULT_EXTERNAL_WINDOW_ONLY;
  std::atomic<gboolean> direct_swapchain = { DEFAULT_DIRECT_SWAPCHAIN };
  gdouble hue = DEFAULT_HUE;
  gdouble saturation = DEFAULT_SATURATION;
  gdouble brightness = DEFAULT_BRIGHTNESS;
  gdouble contrast = DEFAULT_CONTRAST;
};
/* *INDENT-ON* */

struct _GstD3D12VideoSink
{
  GstVideoSink parent;

  GstD3D12Device *device;

  GstD3D12VideoSinkPrivate *priv;
};

static void gst_d3d12_video_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_d3d12_video_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static void gst_d3d12_video_sink_dispose (GObject * object);
static void gst_d3d12_video_sink_finalize (GObject * object);
static void gst_d3d12_video_sink_set_context (GstElement * element,
    GstContext * context);
static gboolean gst_d3d12_video_sink_start (GstBaseSink * sink);
static gboolean gst_d3d12_video_sink_stop (GstBaseSink * sink);
static gboolean gst_d3d12_video_sink_unlock (GstBaseSink * sink);
static gboolean gst_d3d12_video_sink_unlock_stop (GstBaseSink * sink);
static gboolean gst_d3d12_video_sink_propose_allocation (GstBaseSink * sink,
    GstQuery * query);
static gboolean gst_d3d12_video_sink_query (GstBaseSink * sink,
    GstQuery * query);
static GstFlowReturn gst_d3d12_video_sink_prepare (GstBaseSink * sink,
    GstBuffer * buf);
static gboolean gst_d3d12_video_sink_event (GstBaseSink * sink,
    GstEvent * event);
static gboolean gst_d3d12_video_sink_set_info (GstVideoSink * sink,
    GstCaps * caps, const GstVideoInfo * info);
static GstFlowReturn gst_d3d12_video_sink_show_frame (GstVideoSink * sink,
    GstBuffer * buf);
static void gst_d3d12_video_sink_set_orientation (GstD3D12VideoSink * self,
    GstVideoOrientationMethod method, gboolean from_tag);
static void gst_d3d12_video_sink_key_event (GstD3D12Window * window,
    const gchar * event, const gchar * key, GstD3D12VideoSink * self);
static void gst_d3d12_video_sink_mouse_event (GstD3D12Window * window,
    const gchar * event, gint button, gdouble x, gdouble y, guint modifier,
    GstD3D12VideoSink * self);
static void gst_d3d12_video_sink_scroll_event (GstD3D12Window * window,
    gint delta_x, gint delta_y, gdouble x, gdouble y, guint modifier,
    GstD3D12VideoSink * self);
static void gst_d3d12_video_sink_on_fullscreen (GstD3D12Window * window,
    gboolean is_fullscreen, GstD3D12VideoSink * self);
static void gst_d3d12_video_sink_on_overlay (GstD3D12Window * window,
    gpointer command_queue, gpointer resource12, gpointer device11on12,
    gpointer resource11, gpointer context2d, gpointer viewport,
    GstD3D12VideoSink * self);

static void
gst_d3d12_video_sink_video_overlay_init (GstVideoOverlayInterface * iface);
static void
gst_d3d12_video_sink_navigation_init (GstNavigationInterface * iface);
static void
gst_d3d12_video_sink_color_balance_init (GstColorBalanceInterface * iface);

#define gst_d3d12_video_sink_parent_class parent_class
G_DEFINE_TYPE_WITH_CODE (GstD3D12VideoSink, gst_d3d12_video_sink,
    GST_TYPE_VIDEO_SINK,
    G_IMPLEMENT_INTERFACE (GST_TYPE_VIDEO_OVERLAY,
        gst_d3d12_video_sink_video_overlay_init);
    G_IMPLEMENT_INTERFACE (GST_TYPE_NAVIGATION,
        gst_d3d12_video_sink_navigation_init);
    G_IMPLEMENT_INTERFACE (GST_TYPE_COLOR_BALANCE,
        gst_d3d12_video_sink_color_balance_init);
    GST_DEBUG_CATEGORY_INIT (gst_d3d12_video_sink_debug,
        "d3d12videosink", 0, "d3d12videosink"));

static void
gst_d3d12_video_sink_class_init (GstD3D12VideoSinkClass * klass)
{
  auto object_class = G_OBJECT_CLASS (klass);
  auto element_class = GST_ELEMENT_CLASS (klass);
  auto basesink_class = GST_BASE_SINK_CLASS (klass);
  auto videosink_class = GST_VIDEO_SINK_CLASS (klass);

  object_class->set_property = gst_d3d12_video_sink_set_property;
  object_class->get_property = gst_d3d12_video_sink_get_property;
  object_class->dispose = gst_d3d12_video_sink_dispose;
  object_class->finalize = gst_d3d12_video_sink_finalize;

  g_object_class_install_property (object_class, PROP_ADAPTER,
      g_param_spec_int ("adapter", "Adapter",
          "Adapter index for creating device (-1 for default)",
          -1, G_MAXINT32, DEFAULT_ADAPTER,
          (GParamFlags) (G_PARAM_READWRITE | GST_PARAM_MUTABLE_READY |
              G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_FORCE_ASPECT_RATIO,
      g_param_spec_boolean ("force-aspect-ratio",
          "Force aspect ratio",
          "When enabled, scaling will respect original aspect ratio",
          DEFAULT_FORCE_ASPECT_RATIO,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ENABLE_NAVIGATION_EVENTS,
      g_param_spec_boolean ("enable-navigation-events",
          "Enable navigation events",
          "When enabled, navigation events are sent upstream",
          DEFAULT_ENABLE_NAVIGATION_EVENTS,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ROTATE_METHOD,
      g_param_spec_enum ("rotate-method", "Rotate Method",
          "Rotate method to use",
          GST_TYPE_VIDEO_ORIENTATION_METHOD, GST_VIDEO_ORIENTATION_IDENTITY,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class,
      PROP_FULLSCREEN_ON_ALT_ENTER,
      g_param_spec_boolean ("fullscreen-on-alt-enter",
          "Fullscreen on Alt Enter",
          "Enable fullscreen toggle on alt+enter key input",
          DEFAULT_FULLSCREEN_ON_ALT_ENTER,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_FULLSCREEN,
      g_param_spec_boolean ("fullscreen", "Fullscreen",
          "Fullscreen mode", DEFAULT_FULLSCREEN,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_MSAA,
      g_param_spec_enum ("msaa", "MSAA",
          "MSAA (Multi-Sampling Anti-Aliasing) level",
          GST_TYPE_D3D12_MSAA_MODE, DEFAULT_MSAA,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_REDRAW_ON_UPDATE,
      g_param_spec_boolean ("redraw-on-update",
          "redraw-on-update",
          "Immediately apply updated geometry related properties and redraw. "
          "If disabled, properties will be applied on the next frame or "
          "window resize", DEFAULT_REDROW_ON_UPDATE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_FOV,
      g_param_spec_float ("fov", "Fov",
          "Field of view angle in degrees",
          0, G_MAXFLOAT, DEFAULT_FOV,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ORTHO,
      g_param_spec_boolean ("ortho", "Orthographic",
          "Use orthographic projection", DEFAULT_ORTHO,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ROTATION_X,
      g_param_spec_float ("rotation-x", "Rotation X",
          "x-axis rotation angle in degrees",
          -G_MAXFLOAT, G_MAXFLOAT, DEFAULT_ROTATION,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ROTATION_Y,
      g_param_spec_float ("rotation-y", "Rotation Y",
          "y-axis rotation angle in degrees",
          -G_MAXFLOAT, G_MAXFLOAT, DEFAULT_ROTATION,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_ROTATION_Z,
      g_param_spec_float ("rotation-z", "Rotation Z",
          "z-axis rotation angle in degrees",
          -G_MAXFLOAT, G_MAXFLOAT, DEFAULT_ROTATION,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_SCALE_X,
      g_param_spec_float ("scale-x", "Scale X",
          "Scale multiplier for x-axis",
          -G_MAXFLOAT, G_MAXFLOAT, DEFAULT_SCALE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_SCALE_Y,
      g_param_spec_float ("scale-y", "Scale Y",
          "Scale multiplier for y-axis",
          -G_MAXFLOAT, G_MAXFLOAT, DEFAULT_SCALE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_GAMMA_MODE,
      g_param_spec_enum ("gamma-mode", "Gamma mode",
          "Gamma conversion mode", GST_TYPE_VIDEO_GAMMA_MODE,
          DEFAULT_GAMMA_MODE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_PRIMARIES_MODE,
      g_param_spec_enum ("primaries-mode", "Primaries Mode",
          "Primaries conversion mode", GST_TYPE_VIDEO_PRIMARIES_MODE,
          DEFAULT_PRIMARIES_MODE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property (object_class, PROP_SAMPLING_METHOD,
      g_param_spec_enum ("sampling-method", "Sampling method",
          "Sampler filter type to use", GST_TYPE_D3D12_SAMPLING_METHOD,
          DEFAULT_SAMPLING_METHOD,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:overlay-mode:
   *
   * Overly signal type
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_OVERLAY_MODE,
      g_param_spec_flags ("overlay-mode", "Overlay Mode",
          "Overlay signal type to use", GST_TYPE_D3D12_WINDOW_OVERLAY_MODE,
          DEFAULT_OVERLAY_MODE,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:display-format:
   *
   * Swapchain display format
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_DISPLAY_FORMAT,
      g_param_spec_enum ("display-format", "Display Format",
          "Swapchain display format", GST_TYPE_D3D12_VIDEO_SINK_DISPLAY_FORMAT,
          DEFAULT_DISPLAY_FORMAT, (GParamFlags) (G_PARAM_READWRITE |
              GST_PARAM_MUTABLE_READY | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:error-on-closed:
   *
   * Posts error message if window got closed in playing or paused state
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_ERROR_ON_CLOSED,
      g_param_spec_boolean ("error-on-closed", "Error On Closed",
          "Posts error message and return flow error if window is closed "
          "in playing or paused state", DEFAULT_ERROR_ON_CLOSED,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:external-window-only:
   *
   * If enabled and window handle is not set by user, videosink will report
   * error instead of creating videosink's own window.
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_EXTERNAL_WINDOW_ONLY,
      g_param_spec_boolean ("external-window-only", "External Window Only",
          "Disallow creating videosink's own window when overlay handle is not set",
          DEFAULT_EXTERNAL_WINDOW_ONLY,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:direct-swapchain:
   *
   * Attach DXGI swapchain to external window handle directly, instead of
   * creating child window. Note that once direct swapchain is configured,
   * GDI will no longer work with the given window handle.
   *
   * If enabled, GstVideoOverlay::set_render_rectangle will be ignored,
   * and application should handle window positioning.
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_DIRECT_SWAPCHAIN,
      g_param_spec_boolean ("direct-swapchain", "Direct Swapchain",
          "Attach DXGI swapchain to external window handle directly",
          DEFAULT_DIRECT_SWAPCHAIN,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:hue:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_HUE,
      g_param_spec_double ("hue", "Hue", "hue", -1.0, 1.0, DEFAULT_HUE,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:saturation:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_SATURATION,
      g_param_spec_double ("saturation", "Saturation", "saturation", 0.0, 2.0,
          DEFAULT_SATURATION,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:brightness:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_BRIGHTNESS,
      g_param_spec_double ("brightness", "Brightness", "brightness", -1.0, 1.0,
          DEFAULT_BRIGHTNESS,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:contrast:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_CONTRAST,
      g_param_spec_double ("contrast", "Contrast", "contrast", 0.0, 2.0,
          DEFAULT_CONTRAST,
          (GParamFlags) (GST_PARAM_CONTROLLABLE |
              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink:max-mip-levels:
   *
   * Since: 1.26
   */
  g_object_class_install_property (object_class, PROP_MAX_MIP_LEVELS,
      g_param_spec_uint ("max-mip-levels", "Max Mip Levels",
          "Maximum mip levels of shader resource to create "
          "if viewport size is smaller than shader resource "
          "(0 = maximum level)", 0, G_MAXUINT16, DEFAULT_MAX_MIP_LEVELS,
          (GParamFlags) (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  /**
   * GstD3D12VideoSink::overlay:
   * @d3d12videosink: the d3d12videosink element that emitted the signal
   * @command_queue: ID3D12CommandQueue
   * @resource12: ID3D12Resource
   * @device11on12: (nullable): ID3D11On12Device
   * @resource11: (nullable): ID3D11Texture2D
   * @context2d: (nullable): ID2D1DeviceContext2
   * @viewport: (nullable): D3D12_RECT, d3d12videosink's current viewport
   *
   * Signal emitted with Direct3D12, Direct3D11 and Direct2D resources
   * associated with swapchain backbuffer.
   *
   * This signal is emitted from the streaming thread if "overlay-mode" property
   * includes GST_D3D12_WINDOW_OVERLAY_D3D12. The @resource12 is a render target
   * backbuffer of the swapchain. The Resource state of @resource12 when this
   * signal is emitted will be always D3D12_RESOURCE_STATE_RENDER_TARGET and
   * signal handler should make sure the state is
   * D3D12_RESOURCE_STATE_RENDER_TARGET when signal handler is returned,
   * so that state change to final D3D12_RESOURCE_STATE_PRESENT can be
   * processed by videosink.
   *
   * In addition to the d2d12 resources, if "overlay-mode" includes
   * GST_D3D12_WINDOW_OVERLAY_D3D11 flag and d3d11on12 API is supported by
   * system, @device11on12 and @resource11 will be valid handles.
   * Singla handler should not assume the @device11on12 and @resource11
   * are always valid handle since d3d11on12 API may not be supported.
   * The @resource11 is wrapped resource created via
   * [ID3D11On12Device::CreateWrappedResource](https://learn.microsoft.com/en-us/windows/win32/api/d3d11on12/nf-d3d11on12-id3d11on12device-createwrappedresource).
   * Thus, signal handler must follow required steps for d3d11on12 device, for example,
   * [ID3D11On12Device::AcquireWrappedResources](https://learn.microsoft.com/en-us/windows/win32/api/d3d11on12/nf-d3d11on12-id3d11on12device-acquirewrappedresources)
   * must be called before recoding GPU commands.
   * Once GPU commands are recoded via d3d11 or d2d APIs,
   * the resource should be released via
   * [ID3D11On12Device::ReleaseWrappedResources](https://learn.microsoft.com/en-us/windows/win32/api/d3d11on12/nf-d3d11on12-id3d11on12device-releasewrappedresources),
   * and then [ID3D11DeviceContext::Flush](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-flush)
   * must be called in the signal handler.
   *
   * If "overlay-mode" is GST_D3D12_WINDOW_OVERLAY_D2D and d2d device is
   * available, @context2d will be valid handle. When this signal is emitted,
   * @context2d has configured render target already. The D2D render target
   * is also a resource derived from @resource11 and it's swapchain's backbuffer.
   * The same step for d3d11 resource (i.e., acquire, release, and flush)
   * is required for d2d as well.
   *
   * Since the resource is swapchain's backbuffer, signal handler must not hold
   * any derived resources such as ID3D11RenderTargetView, so that videosink
   * can clear swapchain resources and resize anytime it's needed.
   *
   * Since: 1.26
   */
  d3d12_video_sink_signals[SIGNAL_OVERLAY] =
      g_signal_new_class_handler ("overlay", G_TYPE_FROM_CLASS (klass),
      G_SIGNAL_RUN_LAST, nullptr, nullptr, nullptr, nullptr,
      G_TYPE_NONE, 6, G_TYPE_POINTER, G_TYPE_POINTER, G_TYPE_POINTER,
      G_TYPE_POINTER, G_TYPE_POINTER, G_TYPE_POINTER);

  element_class->set_context =
      GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_set_context);

  gst_element_class_set_static_metadata (element_class,
      "Direct3D12 Video Sink", "Sink/Video", "A Direct3D12 Video Sink",
      "Seungha Yang <seungha@centricular.com>");

  gst_element_class_add_static_pad_template (element_class, &sink_template);

  basesink_class->start = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_start);
  basesink_class->stop = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_stop);
  basesink_class->unlock = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_unlock);
  basesink_class->unlock_stop =
      GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_unlock_stop);
  basesink_class->propose_allocation =
      GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_propose_allocation);
  basesink_class->query = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_query);
  basesink_class->prepare = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_prepare);
  basesink_class->event = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_event);

  videosink_class->set_info = GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_set_info);
  videosink_class->show_frame =
      GST_DEBUG_FUNCPTR (gst_d3d12_video_sink_show_frame);

  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_MSAA_MODE, (GstPluginAPIFlags) 0);
  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_SAMPLING_METHOD,
      (GstPluginAPIFlags) 0);
  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_WINDOW_OVERLAY_MODE,
      (GstPluginAPIFlags) 0);
  gst_type_mark_as_plugin_api (GST_TYPE_D3D12_VIDEO_SINK_DISPLAY_FORMAT,
      (GstPluginAPIFlags) 0);
}

static void
gst_d3d12_video_sink_init (GstD3D12VideoSink * self)
{
  self->priv = new GstD3D12VideoSinkPrivate ();

  auto priv = self->priv;
  g_signal_connect (priv->window, "key-event",
      G_CALLBACK (gst_d3d12_video_sink_key_event), self);
  g_signal_connect (priv->window, "mouse-event",
      G_CALLBACK (gst_d3d12_video_sink_mouse_event), self);
  g_signal_connect (priv->window, "scroll-event",
      G_CALLBACK (gst_d3d12_video_sink_scroll_event), self);
  g_signal_connect (priv->window, "fullscreen",
      G_CALLBACK (gst_d3d12_video_sink_on_fullscreen), self);
  g_signal_connect (priv->window, "overlay",
      G_CALLBACK (gst_d3d12_video_sink_on_overlay), self);
}

static void
gst_d3d12_video_sink_dispose (GObject * object)
{
  auto self = GST_D3D12_VIDEO_SINK (object);
  auto priv = self->priv;

  gst_d3d12_window_invalidate (priv->window);
  g_signal_handlers_disconnect_by_data (priv->window, self);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

static void
gst_d3d12_video_sink_finalize (GObject * object)
{
  auto self = GST_D3D12_VIDEO_SINK (object);

  delete self->priv;
  gst_clear_object (&self->device);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gst_d3d12_video_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_VIDEO_SINK (object);
  auto priv = self->priv;
  const gchar *color_balance_label = nullptr;

  {
    std::lock_guard < std::recursive_mutex > lk (priv->lock);
    switch (prop_id) {
      case PROP_ADAPTER:
        priv->adapter = g_value_get_int (value);
        break;
      case PROP_FORCE_ASPECT_RATIO:
        priv->force_aspect_ratio = g_value_get_boolean (value);
        gst_d3d12_window_set_force_aspect_ratio (priv->window,
            priv->force_aspect_ratio);
        break;
      case PROP_ENABLE_NAVIGATION_EVENTS:
        priv->enable_navigation = g_value_get_boolean (value);
        gst_d3d12_window_set_enable_navigation_events (priv->window,
            priv->enable_navigation);
        break;
      case PROP_ROTATE_METHOD:
        gst_d3d12_video_sink_set_orientation (self,
            (GstVideoOrientationMethod) g_value_get_enum (value), FALSE);
        break;
      case PROP_FULLSCREEN_ON_ALT_ENTER:
        priv->fullscreen_on_alt_enter = g_value_get_boolean (value);
        gst_d3d12_window_enable_fullscreen_on_alt_enter (priv->window,
            priv->fullscreen_on_alt_enter);
        break;
      case PROP_FULLSCREEN:
        priv->fullscreen = g_value_get_boolean (value);
        gst_d3d12_window_set_fullscreen (priv->window, priv->fullscreen);
        break;
      case PROP_MSAA:
        priv->msaa = (GstD3D12MSAAMode) g_value_get_enum (value);
        gst_d3d12_window_set_msaa (priv->window, priv->msaa);
        break;
      case PROP_REDRAW_ON_UPDATE:
        priv->redraw_on_update = g_value_get_boolean (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_FOV:
        priv->fov = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_ORTHO:
        priv->ortho = g_value_get_boolean (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_ROTATION_X:
        priv->rotation_x = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_ROTATION_Y:
        priv->rotation_y = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_ROTATION_Z:
        priv->rotation_z = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_SCALE_X:
        priv->scale_x = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_SCALE_Y:
        priv->scale_y = g_value_get_float (value);
        gst_d3d12_video_sink_set_orientation (self, priv->orientation, FALSE);
        break;
      case PROP_GAMMA_MODE:
      {
        auto gamma_mode = (GstVideoGammaMode) g_value_get_enum (value);
        if (priv->gamma_mode != gamma_mode) {
          priv->gamma_mode = gamma_mode;
          priv->update_window = TRUE;
        }
        break;
      }
      case PROP_PRIMARIES_MODE:
      {
        auto primaries_mode = (GstVideoPrimariesMode) g_value_get_enum (value);
        if (priv->primaries_mode != primaries_mode) {
          priv->primaries_mode = primaries_mode;
          priv->update_window = TRUE;
        }
        break;
      }
      case PROP_SAMPLING_METHOD:
      {
        auto sampling_method =
            (GstD3D12SamplingMethod) g_value_get_enum (value);
        if (priv->sampling_method != sampling_method) {
          priv->sampling_method = sampling_method;
          priv->update_window = TRUE;
        }
        break;
      }
      case PROP_OVERLAY_MODE:
        priv->overlay_mode =
            (GstD3D12WindowOverlayMode) g_value_get_flags (value);
        gst_d3d12_window_set_overlay_mode (priv->window, priv->overlay_mode);
        break;
      case PROP_DISPLAY_FORMAT:
        priv->display_format = (DXGI_FORMAT) g_value_get_enum (value);
        break;
      case PROP_ERROR_ON_CLOSED:
        priv->error_on_closed = g_value_get_boolean (value);
        break;
      case PROP_EXTERNAL_WINDOW_ONLY:
        priv->external_only = g_value_get_boolean (value);
        break;
      case PROP_DIRECT_SWAPCHAIN:
        priv->direct_swapchain = g_value_get_boolean (value);
        break;
      case PROP_HUE:
        if (gst_d3d12_window_set_hue (priv->window,
                priv->sync_in_progress ? FALSE : priv->redraw_on_update,
                g_value_get_double (value))) {
          color_balance_label = "HUE";
        }
        break;
      case PROP_SATURATION:
        if (gst_d3d12_window_set_saturation (priv->window,
                priv->sync_in_progress ? FALSE : priv->redraw_on_update,
                g_value_get_double (value))) {
          color_balance_label = "SATURATION";
        }
        break;
      case PROP_BRIGHTNESS:
        if (gst_d3d12_window_set_brightness (priv->window,
                priv->sync_in_progress ? FALSE : priv->redraw_on_update,
                g_value_get_double (value))) {
          color_balance_label = "BRIGHTNESS";
        }
        break;
      case PROP_CONTRAST:
        if (gst_d3d12_window_set_contrast (priv->window,
                priv->sync_in_progress ? FALSE : priv->redraw_on_update,
                g_value_get_double (value))) {
          color_balance_label = "CONTRAST";
        }
        break;
      case PROP_MAX_MIP_LEVELS:
        gst_d3d12_window_set_mip_levels (priv->window, priv->redraw_on_update,
            g_value_get_uint (value));
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
  }

  if (color_balance_label) {
    GList *iter = priv->color_balance_channels;
    while (iter) {
      auto ch = (GstColorBalanceChannel *) iter->data;
      if (g_ascii_strcasecmp (ch->label, color_balance_label) == 0) {
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
gst_d3d12_video_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  auto self = GST_D3D12_VIDEO_SINK (object);
  auto priv = self->priv;

  std::lock_guard < std::recursive_mutex > lk (priv->lock);
  switch (prop_id) {
    case PROP_ADAPTER:
      g_value_set_int (value, priv->adapter);
      break;
    case PROP_FORCE_ASPECT_RATIO:
      g_value_set_boolean (value, priv->force_aspect_ratio);
      break;
    case PROP_ENABLE_NAVIGATION_EVENTS:
      g_value_set_boolean (value, priv->enable_navigation);
      break;
    case PROP_ROTATE_METHOD:
      g_value_set_enum (value, priv->orientation);
      break;
    case PROP_FULLSCREEN_ON_ALT_ENTER:
      g_value_set_boolean (value, priv->fullscreen_on_alt_enter);
      break;
    case PROP_FULLSCREEN:
      g_value_set_boolean (value, priv->fullscreen);
      break;
    case PROP_MSAA:
      g_value_set_enum (value, priv->msaa);
      break;
    case PROP_REDRAW_ON_UPDATE:
      g_value_set_boolean (value, priv->redraw_on_update);
      break;
    case PROP_FOV:
      g_value_set_float (value, priv->fov);
      break;
    case PROP_ORTHO:
      g_value_set_boolean (value, priv->ortho);
      break;
    case PROP_ROTATION_X:
      g_value_set_float (value, priv->rotation_x);
      break;
    case PROP_ROTATION_Y:
      g_value_set_float (value, priv->rotation_x);
      break;
    case PROP_ROTATION_Z:
      g_value_set_float (value, priv->rotation_z);
      break;
    case PROP_SCALE_X:
      g_value_set_float (value, priv->scale_x);
      break;
    case PROP_SCALE_Y:
      g_value_set_float (value, priv->scale_y);
      break;
    case PROP_GAMMA_MODE:
      g_value_set_enum (value, priv->gamma_mode);
      break;
    case PROP_PRIMARIES_MODE:
      g_value_set_enum (value, priv->primaries_mode);
      break;
    case PROP_SAMPLING_METHOD:
      g_value_set_enum (value, priv->sampling_method);
      break;
    case PROP_OVERLAY_MODE:
      g_value_set_flags (value, priv->overlay_mode);
      break;
    case PROP_DISPLAY_FORMAT:
      g_value_set_enum (value, priv->display_format);
      break;
    case PROP_ERROR_ON_CLOSED:
      g_value_set_boolean (value, priv->error_on_closed);
      break;
    case PROP_EXTERNAL_WINDOW_ONLY:
      g_value_set_boolean (value, priv->external_only);
      break;
    case PROP_DIRECT_SWAPCHAIN:
      g_value_set_boolean (value, priv->direct_swapchain);
      break;
    case PROP_HUE:
      g_value_set_double (value, gst_d3d12_window_get_hue (priv->window));
      break;
    case PROP_SATURATION:
      g_value_set_double (value,
          gst_d3d12_window_get_saturation (priv->window));
      break;
    case PROP_BRIGHTNESS:
      g_value_set_double (value,
          gst_d3d12_window_get_brightness (priv->window));
      break;
    case PROP_CONTRAST:
      g_value_set_double (value, gst_d3d12_window_get_contrast (priv->window));
      break;
    case PROP_MAX_MIP_LEVELS:
      g_value_set_uint (value, gst_d3d12_window_get_mip_levels (priv->window));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_d3d12_video_sink_set_orientation (GstD3D12VideoSink * self,
    GstVideoOrientationMethod orientation, gboolean from_tag)
{
  auto priv = self->priv;

  if (orientation == GST_VIDEO_ORIENTATION_CUSTOM) {
    GST_WARNING_OBJECT (self, "Unsupported custom orientation");
    return;
  }

  if (from_tag)
    priv->orientation_from_tag = orientation;
  else
    priv->orientation = orientation;

  if (priv->orientation == GST_VIDEO_ORIENTATION_AUTO)
    priv->orientation_selected = priv->orientation_from_tag;
  else
    priv->orientation_selected = priv->orientation;

  gst_d3d12_window_set_orientation (priv->window,
      priv->redraw_on_update, priv->orientation_selected, priv->fov,
      priv->ortho, priv->rotation_x, priv->rotation_y, priv->rotation_z,
      priv->scale_x, priv->scale_y);
}

static void
gst_d3d12_video_sink_set_context (GstElement * element, GstContext * context)
{
  auto self = GST_D3D12_VIDEO_SINK (element);
  auto priv = self->priv;

  {
    std::lock_guard < std::recursive_mutex > lk (priv->context_lock);
    gst_d3d12_handle_set_context (element,
        context, priv->adapter, &self->device);
  }

  GST_ELEMENT_CLASS (parent_class)->set_context (element, context);
}

static gboolean
gst_d3d12_video_sink_event (GstBaseSink * sink, GstEvent * event)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_TAG:{
      GstTagList *taglist;
      gchar *title = nullptr;

      gst_event_parse_tag (event, &taglist);
      gst_tag_list_get_string (taglist, GST_TAG_TITLE, &title);

      std::lock_guard < std::recursive_mutex > lk (priv->lock);

      if (title) {
        const gchar *app_name = g_get_application_name ();
        std::string title_string;

        if (app_name) {
          title_string = std::string (title) + " : " + std::string (app_name);
        } else {
          title_string = std::string (title);
        }

        gst_d3d12_window_set_title (priv->window, title_string.c_str ());
        g_free (title);
      }

      GstVideoOrientationMethod orientation = GST_VIDEO_ORIENTATION_IDENTITY;
      if (gst_video_orientation_from_tag (taglist, &orientation))
        gst_d3d12_video_sink_set_orientation (self, orientation, TRUE);
      break;
    }
    default:
      break;
  }

  return GST_BASE_SINK_CLASS (parent_class)->event (sink, event);
}

static gboolean
gst_d3d12_video_sink_set_info (GstVideoSink * sink, GstCaps * caps,
    const GstVideoInfo * info)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self, "set caps %" GST_PTR_FORMAT, caps);

  std::lock_guard < std::recursive_mutex > lk (priv->lock);
  gst_caps_replace (&priv->caps, caps);
  priv->info = *info;
  priv->update_window = TRUE;

  auto video_width = GST_VIDEO_INFO_WIDTH (&priv->info);
  auto video_height = GST_VIDEO_INFO_HEIGHT (&priv->info);
  auto video_par_n = GST_VIDEO_INFO_PAR_N (&priv->info);
  auto video_par_d = GST_VIDEO_INFO_PAR_D (&priv->info);
  gint display_par_n = 1;
  gint display_par_d = 1;
  guint num, den;

  if (!gst_video_calculate_display_ratio (&num, &den, video_width,
          video_height, video_par_n, video_par_d, display_par_n,
          display_par_d)) {
    GST_ELEMENT_WARNING (self, CORE, NEGOTIATION, (nullptr),
        ("Error calculating the output display ratio of the video."));
    GST_VIDEO_SINK_WIDTH (self) = video_width;
    GST_VIDEO_SINK_HEIGHT (self) = video_height;
  } else {
    GST_DEBUG_OBJECT (self,
        "video width/height: %dx%d, calculated display ratio: %d/%d format: %s",
        video_width, video_height, num, den,
        gst_video_format_to_string (GST_VIDEO_INFO_FORMAT (&priv->info)));

    if (video_height % den == 0) {
      GST_DEBUG_OBJECT (self, "keeping video height");
      GST_VIDEO_SINK_WIDTH (self) = (guint)
          gst_util_uint64_scale_int (video_height, num, den);
      GST_VIDEO_SINK_HEIGHT (self) = video_height;
    } else if (video_width % num == 0) {
      GST_DEBUG_OBJECT (self, "keeping video width");
      GST_VIDEO_SINK_WIDTH (self) = video_width;
      GST_VIDEO_SINK_HEIGHT (self) = (guint)
          gst_util_uint64_scale_int (video_width, den, num);
    } else {
      GST_DEBUG_OBJECT (self, "approximating while keeping video height");
      GST_VIDEO_SINK_WIDTH (self) = (guint)
          gst_util_uint64_scale_int (video_height, num, den);
      GST_VIDEO_SINK_HEIGHT (self) = video_height;
    }
  }

  if (GST_VIDEO_SINK_WIDTH (self) <= 0) {
    GST_WARNING_OBJECT (self, "Invalid display width %d",
        GST_VIDEO_SINK_WIDTH (self));
    GST_VIDEO_SINK_WIDTH (self) = 8;
  }

  if (GST_VIDEO_SINK_HEIGHT (self) <= 0) {
    GST_WARNING_OBJECT (self, "Invalid display height %d",
        GST_VIDEO_SINK_HEIGHT (self));
    GST_VIDEO_SINK_HEIGHT (self) = 8;
  }

  GST_DEBUG_OBJECT (self, "scaling to %dx%d",
      GST_VIDEO_SINK_WIDTH (self), GST_VIDEO_SINK_HEIGHT (self));

  if (priv->pool) {
    gst_buffer_pool_set_active (priv->pool, FALSE);
    gst_clear_object (&priv->pool);
  }

  priv->pool = gst_d3d12_buffer_pool_new (self->device);
  auto config = gst_buffer_pool_get_config (priv->pool);

  gst_buffer_pool_config_set_params (config, priv->caps, priv->info.size, 0, 0);
  if (!gst_buffer_pool_set_config (priv->pool, config) ||
      !gst_buffer_pool_set_active (priv->pool, TRUE)) {
    GST_ELEMENT_ERROR (self, RESOURCE, FAILED, (nullptr),
        ("Couldn't setup buffer pool"));
    gst_clear_object (&priv->pool);
    return FALSE;
  }

  return TRUE;
}

static void
gst_d3d12_video_sink_key_event (GstD3D12Window * window, const gchar * event,
    const gchar * key, GstD3D12VideoSink * self)
{
  GstEvent *key_event;

  GST_LOG_OBJECT (self, "send key event %s, key %s", event, key);
  if (g_strcmp0 ("key-press", event) == 0) {
    key_event = gst_navigation_event_new_key_press (key,
        GST_NAVIGATION_MODIFIER_NONE);
  } else if (g_strcmp0 ("key-release", event) == 0) {
    key_event = gst_navigation_event_new_key_release (key,
        GST_NAVIGATION_MODIFIER_NONE);
  } else {
    return;
  }

  gst_navigation_send_event_simple (GST_NAVIGATION (self), key_event);
}

static void
gst_d3d12_video_sink_mouse_event (GstD3D12Window * window, const gchar * event,
    gint button, gdouble x, gdouble y, guint modifier, GstD3D12VideoSink * self)
{
  GstEvent *mouse_event;

  GST_LOG_OBJECT (self,
      "send mouse event %s, button %d (%.1f, %.1f)", event, button, x, y);
  if (g_strcmp0 ("mouse-button-press", event) == 0) {
    mouse_event = gst_navigation_event_new_mouse_button_press (button, x, y,
        (GstNavigationModifierType) modifier);
  } else if (g_strcmp0 ("mouse-button-release", event) == 0) {
    mouse_event = gst_navigation_event_new_mouse_button_release (button, x, y,
        (GstNavigationModifierType) modifier);
  } else if (g_strcmp0 ("mouse-move", event) == 0) {
    mouse_event = gst_navigation_event_new_mouse_move (x, y,
        (GstNavigationModifierType) modifier);
  } else if (g_strcmp0 ("mouse-double-click", event) == 0) {
    mouse_event = gst_navigation_event_new_mouse_double_click (button, x, y,
        (GstNavigationModifierType) modifier);
  } else {
    return;
  }

  gst_navigation_send_event_simple (GST_NAVIGATION (self), mouse_event);
}

static void
gst_d3d12_video_sink_scroll_event (GstD3D12Window * window,
    gint delta_x, gint delta_y, gdouble x, gdouble y, guint modifier,
    GstD3D12VideoSink * self)
{
  gst_navigation_send_event_simple (GST_NAVIGATION (self),
      gst_navigation_event_new_mouse_scroll (x, y, delta_x, delta_y,
          (GstNavigationModifierType) modifier));
}

static void
gst_d3d12_video_sink_on_fullscreen (GstD3D12Window * window,
    gboolean is_fullscreen, GstD3D12VideoSink * self)
{
  auto priv = self->priv;
  gboolean notify = FALSE;

  {
    std::lock_guard < std::recursive_mutex > lk (priv->lock);
    if (priv->fullscreen != is_fullscreen) {
      priv->fullscreen = is_fullscreen;
      notify = TRUE;
    }
  }

  if (notify)
    g_object_notify (G_OBJECT (self), "fullscreen");
}

static gboolean
gst_d3d12_video_sink_foreach_meta (GstBuffer * buffer, GstMeta ** meta,
    GstBuffer * uploaded)
{
  if ((*meta)->info->api != GST_VIDEO_OVERLAY_COMPOSITION_META_API_TYPE)
    return TRUE;

  auto cmeta = (GstVideoOverlayCompositionMeta *) (*meta);
  if (!cmeta->overlay)
    return TRUE;

  if (gst_video_overlay_composition_n_rectangles (cmeta->overlay) == 0)
    return TRUE;

  gst_buffer_add_video_overlay_composition_meta (uploaded, cmeta->overlay);

  return TRUE;
}

static GstFlowReturn
gst_d3d12_video_sink_set_buffer (GstD3D12VideoSink * self,
    GstBuffer * buffer, gboolean is_prepare)
{
  auto priv = self->priv;
  GstFlowReturn ret = GST_FLOW_OK;
  gboolean set_buffer = FALSE;
  gboolean update_window = FALSE;

  {
    std::lock_guard < std::recursive_mutex > lk (priv->lock);
    if (is_prepare) {
      if (priv->update_window) {
        set_buffer = FALSE;
        update_window = FALSE;
      } else {
        set_buffer = TRUE;
        update_window = FALSE;
      }
    } else {
      if (priv->update_window) {
        set_buffer = TRUE;
        update_window = TRUE;
        priv->update_window = FALSE;
      } else {
        set_buffer = FALSE;
        update_window = FALSE;
      }
    }
  }

  if (update_window) {
    gst_structure_set (priv->convert_config,
        GST_D3D12_CONVERTER_OPT_GAMMA_MODE,
        GST_TYPE_VIDEO_GAMMA_MODE, priv->gamma_mode,
        GST_D3D12_CONVERTER_OPT_PRIMARIES_MODE,
        GST_TYPE_VIDEO_PRIMARIES_MODE, priv->primaries_mode,
        GST_D3D12_CONVERTER_OPT_SAMPLER_FILTER,
        GST_TYPE_D3D12_CONVERTER_SAMPLER_FILTER,
        gst_d3d12_sampling_method_to_native (priv->sampling_method),
        GST_D3D12_CONVERTER_OPT_DEST_ALPHA_MODE,
        GST_TYPE_D3D12_CONVERTER_ALPHA_MODE,
        GST_VIDEO_INFO_HAS_ALPHA (&priv->info) ?
        GST_D3D12_CONVERTER_ALPHA_MODE_PREMULTIPLIED :
        GST_D3D12_CONVERTER_ALPHA_MODE_UNSPECIFIED,
        GST_D3D12_CONVERTER_OPT_COLOR_BALANCE,
        GST_TYPE_D3D12_CONVERTER_COLOR_BALANCE,
        GST_D3D12_CONVERTER_COLOR_BALANCE_ENABLED,
        GST_D3D12_CONVERTER_OPT_MIP_GEN, GST_TYPE_D3D12_CONVERTER_MIP_GEN,
        GST_D3D12_CONVERTER_MIP_GEN_ENABLED, nullptr);

    ret = gst_d3d12_window_prepare (priv->window, self->device,
        GST_VIDEO_SINK_WIDTH (self), GST_VIDEO_SINK_HEIGHT (self), priv->caps,
        priv->convert_config, priv->display_format);

    if (ret != GST_FLOW_OK)
      return ret;
  }

  if (!set_buffer)
    return GST_FLOW_OK;

  GstBuffer *upload = nullptr;
  auto mem = gst_buffer_peek_memory (buffer, 0);
  if (!gst_is_d3d12_memory (mem)) {
    gst_buffer_pool_acquire_buffer (priv->pool, &upload, nullptr);
    if (!upload) {
      GST_ERROR_OBJECT (self, "Couldn't allocate upload buffer");
      return GST_FLOW_ERROR;
    }

    GstVideoFrame in_frame, out_frame;
    if (!gst_video_frame_map (&in_frame, &priv->info, buffer, GST_MAP_READ)) {
      GST_ERROR_OBJECT (self, "Couldn't map input frame");
      gst_buffer_unref (upload);
      return GST_FLOW_ERROR;
    }

    if (!gst_video_frame_map (&out_frame, &priv->info, upload, GST_MAP_WRITE)) {
      GST_ERROR_OBJECT (self, "Couldn't map upload frame");
      gst_video_frame_unmap (&in_frame);
      gst_buffer_unref (upload);
      return GST_FLOW_ERROR;
    }

    auto copy_ret = gst_video_frame_copy (&out_frame, &in_frame);
    gst_video_frame_unmap (&out_frame);
    gst_video_frame_unmap (&in_frame);
    if (!copy_ret) {
      GST_ERROR_OBJECT (self, "Couldn't copy frame");
      gst_buffer_unref (upload);
      return GST_FLOW_ERROR;
    }

    gst_buffer_foreach_meta (buffer,
        (GstBufferForeachMetaFunc) gst_d3d12_video_sink_foreach_meta, upload);

    buffer = upload;
  }

  ret = gst_d3d12_window_set_buffer (priv->window, buffer);

  if (upload)
    gst_buffer_unref (upload);

  return ret;
}

static gboolean
gst_d3d12_video_sink_start (GstBaseSink * sink)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self, "Start");

  if (!gst_d3d12_ensure_element_data (GST_ELEMENT_CAST (self), priv->adapter,
          &self->device)) {
    GST_ERROR_OBJECT (sink, "Cannot create device");
    return FALSE;
  }

  priv->warn_closed_window = TRUE;
  priv->window_open_called = FALSE;

  return TRUE;
}

static gboolean
gst_d3d12_video_sink_stop (GstBaseSink * sink)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self, "Stop");

  priv->orientation_from_tag = GST_VIDEO_ORIENTATION_IDENTITY;

  if (priv->pool) {
    gst_buffer_pool_set_active (priv->pool, FALSE);
    gst_clear_object (&priv->pool);
  }

  gst_d3d12_window_unprepare (priv->window);
  gst_clear_object (&self->device);

  return TRUE;
}

static gboolean
gst_d3d12_video_sink_unlock (GstBaseSink * sink)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self, "Unlock");

  gst_d3d12_window_unlock (priv->window);

  return TRUE;
}

static gboolean
gst_d3d12_video_sink_unlock_stop (GstBaseSink * sink)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self, "Unlock stop");

  gst_d3d12_window_unlock_stop (priv->window);

  return TRUE;
}

static gboolean
gst_d3d12_video_sink_propose_allocation (GstBaseSink * sink, GstQuery * query)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  GstCaps *caps;
  GstBufferPool *pool = nullptr;
  GstVideoInfo info;
  guint size;
  gboolean need_pool;

  if (!self->device) {
    GST_WARNING_OBJECT (self, "No configured device");
    return FALSE;
  }

  gst_query_parse_allocation (query, &caps, &need_pool);
  if (!caps) {
    GST_WARNING_OBJECT (self, "no caps specified");
    return FALSE;
  }

  if (!gst_video_info_from_caps (&info, caps)) {
    GST_ERROR_OBJECT (self, "Invalid caps %" GST_PTR_FORMAT, caps);
    return FALSE;
  }

  size = info.size;

  bool is_d3d12 = false;
  auto features = gst_caps_get_features (caps, 0);
  if (gst_caps_features_contains (features,
          GST_CAPS_FEATURE_MEMORY_D3D12_MEMORY)) {
    is_d3d12 = true;
    GST_DEBUG_OBJECT (self, "upstream support d3d12 memory");
  }

  if (need_pool) {
    if (is_d3d12)
      pool = gst_d3d12_buffer_pool_new (self->device);
    else
      pool = gst_video_buffer_pool_new ();

    auto config = gst_buffer_pool_get_config (pool);
    gst_buffer_pool_config_add_option (config,
        GST_BUFFER_POOL_OPTION_VIDEO_META);
    if (!is_d3d12) {
      gst_buffer_pool_config_add_option (config,
          GST_BUFFER_POOL_OPTION_VIDEO_ALIGNMENT);
    }

    gst_buffer_pool_config_set_params (config, caps, size, 2, 0);

    if (!gst_buffer_pool_set_config (pool, config)) {
      GST_ERROR_OBJECT (pool, "Couldn't set config");
      gst_object_unref (pool);

      return FALSE;
    }

    if (is_d3d12) {
      config = gst_buffer_pool_get_config (pool);
      gst_buffer_pool_config_get_params (config, nullptr, &size, nullptr,
          nullptr);
      gst_structure_free (config);
    }
  }

  gst_query_add_allocation_pool (query, pool, size, 2, 0);
  gst_clear_object (&pool);

  gst_query_add_allocation_meta (query, GST_VIDEO_META_API_TYPE, nullptr);
  gst_query_add_allocation_meta (query,
      GST_VIDEO_OVERLAY_COMPOSITION_META_API_TYPE, nullptr);
  if (is_d3d12) {
    gst_query_add_allocation_meta (query,
        GST_VIDEO_CROP_META_API_TYPE, nullptr);
  }

  return TRUE;
}

static gboolean
gst_d3d12_video_sink_query (GstBaseSink * sink, GstQuery * query)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_CONTEXT:
    {
      std::lock_guard < std::recursive_mutex > lk (priv->context_lock);
      if (gst_d3d12_handle_context_query (GST_ELEMENT (self), query,
              self->device)) {
        return TRUE;
      }
      break;
    }
    default:
      break;
  }

  return GST_BASE_SINK_CLASS (parent_class)->query (sink, query);
}

static GstFlowReturn
gst_d3d12_video_sink_check_device_update (GstD3D12VideoSink * self,
    GstBuffer * buf)
{
  auto priv = self->priv;

  auto mem = gst_buffer_peek_memory (buf, 0);
  if (!gst_is_d3d12_memory (mem))
    return GST_FLOW_OK;

  auto dmem = GST_D3D12_MEMORY_CAST (mem);
  if (gst_d3d12_device_is_equal (dmem->device, self->device))
    return GST_FLOW_OK;

  GST_INFO_OBJECT (self, "Updating device %" GST_PTR_FORMAT " -> %"
      GST_PTR_FORMAT, self->device, dmem->device);

  {
    std::lock_guard < std::recursive_mutex > lk (priv->lock);
    priv->update_window = TRUE;
  }

  std::lock_guard < std::recursive_mutex > lk (priv->context_lock);
  gst_clear_object (&self->device);
  self->device = (GstD3D12Device *) gst_object_ref (dmem->device);

  if (priv->pool) {
    gst_buffer_pool_set_active (priv->pool, FALSE);
    gst_clear_object (&priv->pool);
  }

  priv->pool = gst_d3d12_buffer_pool_new (self->device);
  auto config = gst_buffer_pool_get_config (priv->pool);

  gst_buffer_pool_config_set_params (config, priv->caps, priv->info.size, 0, 0);
  if (!gst_buffer_pool_set_config (priv->pool, config) ||
      !gst_buffer_pool_set_active (priv->pool, TRUE)) {
    GST_ELEMENT_ERROR (self, RESOURCE, FAILED, (nullptr),
        ("Couldn't setup buffer pool"));
    gst_clear_object (&priv->pool);
    return GST_FLOW_ERROR;
  }

  return GST_FLOW_OK;
}

static GstFlowReturn
gst_d3d12_video_sink_open_window (GstD3D12VideoSink * self)
{
  auto overlay = GST_VIDEO_OVERLAY (self);
  auto priv = self->priv;
  guintptr window_handle = 0;
  auto is_closed = gst_d3d12_window_is_closed (priv->window);
  gboolean need_open = FALSE;

  {
    std::lock_guard < std::recursive_mutex > lk (priv->lock);
    if (!priv->window_open_called) {
      GST_DEBUG_OBJECT (self, "Open was not called, try open");
      gst_video_overlay_prepare_window_handle (overlay);
      need_open = TRUE;
    } else if (priv->window_handle_updated) {
      GST_DEBUG_OBJECT (self, "Set window handle was called, try open again");
      need_open = TRUE;
    } else if (is_closed) {
      /* Request new window handle */
      GST_LOG_OBJECT (self, "Window was closed, requesting new window handle");
      gst_video_overlay_prepare_window_handle (overlay);
      if (priv->window_handle_updated) {
        GST_DEBUG_OBJECT (self, "Set window handle was called");
        need_open = TRUE;
      }
    }

    priv->window_handle_updated = FALSE;

    if (!need_open) {
      if (!is_closed)
        return GST_FLOW_OK;

      GST_WARNING_OBJECT (self, "Window was closed");
      return GST_D3D12_WINDOW_FLOW_CLOSED;
    }

    window_handle = priv->window_handle;
    if (!window_handle && priv->external_only) {
      GST_WARNING_OBJECT (self,
          "external-window-only mode but window handle is unavailable");
      return GST_D3D12_WINDOW_FLOW_CLOSED;
    }
  }

  priv->window_open_called = TRUE;
  priv->warn_closed_window = TRUE;
  auto ret = gst_d3d12_window_open (priv->window, self->device,
      GST_VIDEO_SINK_WIDTH (self), GST_VIDEO_SINK_HEIGHT (self),
      (HWND) window_handle, priv->direct_swapchain);

  std::lock_guard < std::recursive_mutex > lk (priv->lock);
  if (ret == GST_FLOW_OK) {
    if (window_handle) {
      GST_DEBUG_OBJECT (self, "Window created with HWND %p",
          (void *) window_handle);
      gst_video_overlay_got_window_handle (overlay, window_handle);
    } else {
      auto internal_hwnd = gst_d3d12_window_get_window_handle (priv->window);
      GST_DEBUG_OBJECT (self, "Window created with internal HWND %p",
          (void *) internal_hwnd);
      gst_video_overlay_got_window_handle (overlay, internal_hwnd);
    }

    priv->update_window = TRUE;
  }

  return ret;
}

static GstFlowReturn
gst_d3d12_video_sink_prepare (GstBaseSink * sink, GstBuffer * buffer)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;
  auto pts = GST_BUFFER_PTS (buffer);

  auto ret = gst_d3d12_video_sink_check_device_update (self, buffer);
  if (ret != GST_FLOW_OK)
    goto out;

  ret = gst_d3d12_video_sink_open_window (self);
  if (ret != GST_FLOW_OK)
    goto out;

  if (GST_CLOCK_TIME_IS_VALID (pts)) {
    auto stream_time = gst_segment_to_stream_time (&sink->segment,
        GST_FORMAT_TIME, pts);
    if (GST_CLOCK_TIME_IS_VALID (stream_time)) {
      priv->sync_in_progress = true;
      gst_object_sync_values (GST_OBJECT (self), stream_time);
      priv->sync_in_progress = false;
    }
  }

  ret = gst_d3d12_video_sink_set_buffer (self, buffer, TRUE);

out:
  if (ret == GST_D3D12_WINDOW_FLOW_CLOSED) {
    if (priv->error_on_closed) {
      GST_ELEMENT_ERROR (self, RESOURCE, NOT_FOUND,
          ("Output window was closed"), (nullptr));
      return GST_FLOW_ERROR;
    } else {
      if (priv->warn_closed_window) {
        GST_ELEMENT_WARNING (self, RESOURCE, NOT_FOUND,
            ("Output window was closed"), (nullptr));
        priv->warn_closed_window = FALSE;
      } else {
        GST_WARNING_OBJECT (self, "Output window was closed");
      }
      ret = GST_FLOW_OK;
    }
  }

  return ret;
}

static GstFlowReturn
gst_d3d12_video_sink_show_frame (GstVideoSink * sink, GstBuffer * buf)
{
  auto self = GST_D3D12_VIDEO_SINK (sink);
  auto priv = self->priv;
  auto ret = gst_d3d12_video_sink_set_buffer (self, buf, FALSE);
  if (ret != GST_FLOW_OK)
    goto out;

  ret = gst_d3d12_window_present (priv->window);

out:
  if (ret == GST_D3D12_WINDOW_FLOW_CLOSED) {
    if (priv->error_on_closed) {
      GST_ELEMENT_ERROR (self, RESOURCE, NOT_FOUND,
          ("Output window was closed"), (nullptr));
      ret = GST_FLOW_ERROR;
    } else {
      if (priv->warn_closed_window) {
        GST_ELEMENT_WARNING (self, RESOURCE, NOT_FOUND,
            ("Output window was closed"), (nullptr));
        priv->warn_closed_window = FALSE;
      } else {
        GST_WARNING_OBJECT (self, "Output window was closed");
      }
      ret = GST_FLOW_OK;
    }
  }

  return ret;
}

static void
gst_d3d12_video_sink_overlay_expose (GstVideoOverlay * overlay)
{
  auto self = GST_D3D12_VIDEO_SINK (overlay);
  auto priv = self->priv;

  gst_d3d12_window_expose (priv->window);
}

static void
gst_d3d12_video_sink_overlay_handle_events (GstVideoOverlay * overlay,
    gboolean handle_events)
{
  auto self = GST_D3D12_VIDEO_SINK (overlay);
  auto priv = self->priv;

  std::lock_guard < std::recursive_mutex > lk (priv->lock);
  priv->enable_navigation = handle_events;
  gst_d3d12_window_set_enable_navigation_events (priv->window, handle_events);
}

static void
gst_d3d12_video_sink_overlay_set_window_handle (GstVideoOverlay * overlay,
    guintptr window_handle)
{
  auto self = GST_D3D12_VIDEO_SINK (overlay);
  auto priv = self->priv;

  GST_DEBUG ("set window handle %" G_GUINTPTR_FORMAT, window_handle);

  std::lock_guard < std::recursive_mutex > lk (priv->lock);
  if (priv->window_handle != window_handle) {
    priv->window_handle = window_handle;
    priv->window_handle_updated = TRUE;
  }
}

static void
gst_d3d12_video_sink_overlay_set_render_rectangle (GstVideoOverlay * overlay,
    gint x, gint y, gint width, gint height)
{
  auto self = GST_D3D12_VIDEO_SINK (overlay);
  auto priv = self->priv;

  GST_DEBUG_OBJECT (self,
      "render rect x: %d, y: %d, width: %d, height %d", x, y, width, height);

  GstVideoRectangle rect;
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;

  gst_d3d12_window_set_render_rect (priv->window, &rect);
}

static void
gst_d3d12_video_sink_video_overlay_init (GstVideoOverlayInterface * iface)
{
  iface->expose = gst_d3d12_video_sink_overlay_expose;
  iface->handle_events = gst_d3d12_video_sink_overlay_handle_events;
  iface->set_window_handle = gst_d3d12_video_sink_overlay_set_window_handle;
  iface->set_render_rectangle =
      gst_d3d12_video_sink_overlay_set_render_rectangle;
}

static void
gst_d3d12_video_sink_navigation_send_event (GstNavigation * navigation,
    GstEvent * event)
{
  auto self = GST_D3D12_VIDEO_SINK (navigation);

  if (event) {
    gboolean handled;

    gst_event_ref (event);
    handled = gst_pad_push_event (GST_VIDEO_SINK_PAD (self), event);

    if (!handled)
      gst_element_post_message (GST_ELEMENT_CAST (self),
          gst_navigation_message_new_event (GST_OBJECT_CAST (self), event));

    gst_event_unref (event);
  }
}

static void
gst_d3d12_video_sink_navigation_init (GstNavigationInterface * iface)
{
  iface->send_event_simple = gst_d3d12_video_sink_navigation_send_event;
}

static const GList *
gst_d3d12_video_sink_color_balance_list_channels (GstColorBalance * iface)
{
  auto self = GST_D3D12_VIDEO_SINK (iface);
  auto priv = self->priv;

  return priv->color_balance_channels;
}

static void
gst_d3d12_video_sink_color_balance_set_value (GstColorBalance * iface,
    GstColorBalanceChannel * channel, gint value)
{
  auto self = GST_D3D12_VIDEO_SINK (iface);
  auto priv = self->priv;

  gdouble new_val;
  gboolean changed = FALSE;

  g_return_if_fail (channel->label);

  if (!g_ascii_strcasecmp (channel->label, "HUE")) {
    new_val = (value + 1000.0) * 2.0 / 2000.0 - 1.0;
    changed = gst_d3d12_window_set_hue (priv->window, priv->redraw_on_update,
        new_val);
  } else if (!g_ascii_strcasecmp (channel->label, "SATURATION")) {
    new_val = (value + 1000.0) * 2.0 / 2000.0;
    changed = gst_d3d12_window_set_saturation (priv->window,
        priv->redraw_on_update, new_val);
  } else if (!g_ascii_strcasecmp (channel->label, "BRIGHTNESS")) {
    new_val = (value + 1000.0) * 2.0 / 2000.0 - 1.0;
    changed = gst_d3d12_window_set_brightness (priv->window,
        priv->redraw_on_update, new_val);
  } else if (!g_ascii_strcasecmp (channel->label, "CONTRAST")) {
    new_val = (value + 1000.0) * 2.0 / 2000.0;
    changed = gst_d3d12_window_set_contrast (priv->window,
        priv->redraw_on_update, new_val);
  }

  if (changed) {
    gst_color_balance_value_changed (iface, channel,
        gst_color_balance_get_value (iface, channel));
  }
}

static gint
gst_d3d12_video_sink_color_balance_get_value (GstColorBalance * iface,
    GstColorBalanceChannel * channel)
{
  auto self = GST_D3D12_VIDEO_SINK (iface);
  auto priv = self->priv;
  gint value = 0;

  g_return_val_if_fail (channel->label, 0);

  if (!g_ascii_strcasecmp (channel->label, "HUE")) {
    auto hue = gst_d3d12_window_get_hue (priv->window);
    value = static_cast < gint > ((hue + 1) * 2000.0 / 2.0 - 1000.0);
  } else if (!g_ascii_strcasecmp (channel->label, "SATURATION")) {
    auto saturation = gst_d3d12_window_get_saturation (priv->window);
    value = static_cast < gint > (saturation * 2000.0 / 2.0 - 1000.0);
  } else if (!g_ascii_strcasecmp (channel->label, "BRIGHTNESS")) {
    auto brightness = gst_d3d12_window_get_saturation (priv->window);
    value = static_cast < gint > ((brightness + 1) * 2000.0 / 2.0 - 1000.0);
  } else if (!g_ascii_strcasecmp (channel->label, "CONTRAST")) {
    auto contrast = gst_d3d12_window_get_contrast (priv->window);
    value = static_cast < gint > (contrast * 2000.0 / 2.0 - 1000.0);
  }

  return value;
}

static GstColorBalanceType
gst_d3d12_video_sink_color_balance_get_balance_type (GstColorBalance * iface)
{
  return GST_COLOR_BALANCE_HARDWARE;
}

static void
gst_d3d12_video_sink_color_balance_init (GstColorBalanceInterface * iface)
{
  iface->list_channels = gst_d3d12_video_sink_color_balance_list_channels;
  iface->set_value = gst_d3d12_video_sink_color_balance_set_value;
  iface->get_value = gst_d3d12_video_sink_color_balance_get_value;
  iface->get_balance_type = gst_d3d12_video_sink_color_balance_get_balance_type;
}

static void
gst_d3d12_video_sink_on_overlay (GstD3D12Window * window,
    gpointer command_queue, gpointer resource12, gpointer device11on12,
    gpointer resource11, gpointer context2d, gpointer viewport,
    GstD3D12VideoSink * self)
{
  g_signal_emit (self, d3d12_video_sink_signals[SIGNAL_OVERLAY], 0,
      command_queue, resource12, device11on12, resource11, context2d, viewport);
}
