



以瑞芯微为例：

#define RKMPP_DEC(NAME, ID, BSFS) \

    RKMPP_DEC_CLASS(NAME) \

    const FFCodec ff_##NAME##_rkmpp_decoder = { \

        .p.name         = #NAME "_rkmpp", \

        CODEC_LONG_NAME(#NAME " (rkmpp)"), \

        .p.type         = AVMEDIA_TYPE_VIDEO, \

        .p.id           = ID, \

        .priv_data_size = sizeof(RKMPPDecodeContext), \

        .init           = rkmpp_init_decoder, \

        .close          = rkmpp_close_decoder, \

        FF_CODEC_RECEIVE_FRAME_CB(rkmpp_receive_frame), \

        .flush          = rkmpp_flush, \

        .p.priv_class   = &rkmpp_##NAME##_dec_class, \

        .p.capabilities = AV_CODEC_CAP_DELAY | AV_CODEC_CAP_AVOID_PROBING | AV_CODEC_CAP_HARDWARE, \

        .hw_configs     = rkmpp_hw_configs, \

        .bsfs           = BSFS, \

        .p.wrapper_name = "rkmpp", \

当前版本的主要就是要实现 receive_frame

配合`avcodec_send_packet`和`avcodec_receive_frame`完成异步解码

https://mp.weixin.qq.com/s?__biz=MzA4MjU1MDk3Ng==&mid=2451528347&idx=1&sn=79d74b8e7588fdaf2e511294a525c04b&chksm=898f653ead088b2af3e3de6bbd58aec49843472174d57490c4a3a88cf261b100adf90392286c#rd









一个编码器实现
#include "new_enc_h264.h"  
   
const enum AVPixelFormat ff_new_enc_pix_fmts[] = {  
    AV_PIX_FMT_NV12,  
    AV_PIX_FMT_NONE  
};  

static av_cold int ff_new_enc_init(AVCodecContext *avctx)  
{  
    av_log(avctx, AV_LOG_VERBOSE, "%s\n", __func__);  
   
    return 0;  
}  


该回调函数实现初始化工作，可能包括对编码器的硬件初始化、内存分配、私有数据的初始化等等



   
static av_cold int ff_new_enc_close(AVCodecContext *avctx)  
{  
    av_log(avctx, AV_LOG_VERBOSE, "NewEnc unloaded\n");  
   
    return 0;  
}  


释放init中的分配的资源。



   
static int ff_new_enc_receive_packet(AVCodecContext *avctx, AVPacket *pkt)  
{  
    av_log(avctx, AV_LOG_WARNING, "Not implement.\n");  
    return AVERROR(EAGAIN);  
}  
   


该回调函数负责将编码后的数据放入到AVPacket中。ffmpeg使用AVPacket存放编码后的数据，与AVFrame相对应。

通常的处理过程如下:

1. 调用GetFilledBuffer接口函数，获取编码内存

2. 调用ff_alloc_packet2，给@pkt分配足够的空间存放编码后的数据。

3. 从编码内存中拷贝数据到@pkt。这一步数据量通常较小，不需要特殊处理。

4. 调用FillThisBuffer将处理后的编码内存返回给编码器

5. 



static int ff_new_enc_send_frame(AVCodecContext *avctx, const AVFrame *frame)  
{  
    av_log(avctx, AV_LOG_WARNING, "Not implement.\n");  
    return AVERROR(EAGAIN);  
}  

该函数通过AVFrame，传递一帧视频原始数据(这里为NV12格式)给codec，在该函数内部实现对该帧的处理。通常的处理过程为:

1. 使用GetEmptyBuffer获取空闲内存

2. 将@frame中的数据放入到空闲内存中。因为frame数据量较大，且视频格式多样，这一步可能涉及到调用特定接口实现加速拷贝。

3. 使用EmptyThisBuffer将填充后的内存放入到编码器中进行编码。

====================================

上面提到的几个函数

- GetEmptyBuffer: 获取空闲内存，用于存放原始数据

- EmptyThisBuffer: 将原始数据提交给编码器

- GetFilledBuffer: 获取编码之后的内存

- FillThisBuffer: 返回编码内存

这些是假设底层接入的是openmax il层的接口，所使用的函数







AVCodec ff_h264_new_encoder = {  
    .name           = "new_enc",  
    .long_name      = NULL_IF_CONFIG_SMALL("New H264 Encoder"),  
    .type           = AVMEDIA_TYPE_VIDEO,  
    .id             = AV_CODEC_ID_H264,  
    .priv_data_size = sizeof(NewEncCtx),  
    .init           = ff_new_enc_init,  
    .close          = ff_new_enc_close,  
    .receive_packet = ff_new_enc_receive_packet,  
    .send_frame     = ff_new_enc_send_frame,  
    .pix_fmts       = ff_new_enc_pix_fmts,  
};
