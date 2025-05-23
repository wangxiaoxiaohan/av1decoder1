/*
 * GStreamer - GStreamer SRTP decoder
 *
 * Copyright 2009 Collabora Ltd.
 *  @author: Gabriel Millaire <gabriel.millaire@collabora.co.uk>
 *  @author: Olivier Crete <olivier.crete@collabora.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
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
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_SRTPDEC_H__
#define __GST_SRTPDEC_H__

#include "gstsrtp.h"

G_BEGIN_DECLS

#define GST_TYPE_SRTP_DEC \
  (gst_srtp_dec_get_type())
#define GST_SRTP_DEC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_SRTP_DEC,GstSrtpDec))
#define GST_SRTP_DEC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_SRTP_DEC,GstSrtpDecClass))
#define GST_IS_SRTP_DEC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SRTP_DEC))
#define GST_IS_SRTP_DEC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SRTP_DEC))

typedef struct _GstSrtpDec      GstSrtpDec;
typedef struct _GstSrtpDecClass GstSrtpDecClass;
typedef struct _GstSrtpDecSsrcStream GstSrtpDecSsrcStream;

struct _GstSrtpDec
{
  GstElement element;

  guint replay_window_size;

  GstPad *rtp_sinkpad, *rtp_srcpad;
  GstPad *rtcp_sinkpad, *rtcp_srcpad;

  gboolean ask_update;
  srtp_t session;
  gboolean first_session;
  GHashTable *streams;

  gboolean rtp_has_segment;
  gboolean rtcp_has_segment;
  guint recv_count;
  guint recv_drop_count;
};

struct _GstSrtpDecClass
{
  GstElementClass parent_class;

  void (*clear_streams) (GstSrtpDec * filter);
  void (*remove_stream) (GstSrtpDec * filter, guint ssrc);
};

GType gst_srtp_dec_get_type (void);


G_END_DECLS

#endif /* __GST_SRTPDEC_H__ */
