# 应用层

一个mpp 例子程序

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "rk_mpi.h"
#include "mpp_log.h"
#include "mpp_buffer.h"

#define MAX_PACKET_SIZE    (512 * 1024)
#define FRAME_TIMEOUT_MS   1000

typedef struct {
    MppCtx          ctx;
    MppApi         *mpi;
    MppBufferGroup buf_grp;
    FILE           *input_fp;
    FILE           *output_fp;
    size_t          packet_size;
} DecodeContext;

/* H264解码线程 */
void* decode_thread(void *arg) {
    DecodeContext *ctx = (DecodeContext *)arg;
    MppPacket packet = NULL;
    MppFrame  frame  = NULL;
    MppBuffer str_buf = NULL;
    RK_U8 *buf = malloc(MAX_PACKET_SIZE);
    size_t read_size;

    while (1) {
        /* 读取H264码流 */
        read_size = fread(buf, 1, MAX_PACKET_SIZE, ctx->input_fp);
        if (!read_size) break;
    
        /* 创建MPP数据包 */
        mpp_packet_init(&packet, buf, read_size);
        mpp_packet_set_length(packet, read_size);
        mpp_packet_set_eos(packet, feof(ctx->input_fp));
    
        /* 发送到解码器 */
        RK_S32 ret = ctx->mpi->decode_put_packet(ctx->ctx, packet);
        if (MPP_OK != ret) {
            mpp_packet_deinit(&packet);
            usleep(5000);
            continue;
        }
    
        /* 获取解码帧 */
        do {
            ret = ctx->mpi->decode_get_frame(ctx->ctx, &frame);
            if (MPP_OK == ret && frame) {
                /* 处理YUV数据 */
                if (mpp_frame_get_errinfo(frame)) {
                    mpp_frame_deinit(&frame);
                    continue;
                }
    
                /* 写入YUV文件 */
                MppBuffer buffer = mpp_frame_get_buffer(frame);
                if (buffer) {
                    void *ptr = mpp_buffer_get_ptr(buffer);
                    size_t len = mpp_buffer_get_size(buffer);
                    fwrite(ptr, 1, len, ctx->output_fp);
                }
                mpp_frame_deinit(&frame);
            }
        } while (MPP_OK == ret);
    
        mpp_packet_deinit(&packet);
    }
    
    free(buf);
    return NULL;

}

int main(int argc, char **argv) {
    MPP_RET ret = MPP_OK;
    DecodeContext dec_ctx = {0};
    const char *input = "input.h264";
    const char *output = "output.yuv";

    /* 初始化MPP系统 */
    ret = RK_MPI_SYS_Init();
    if (ret) {
        mpp_err("MPP系统初始化失败: %d\n", ret);
        return -1;
    }
    
    /* 创建解码器上下文 */
    ret = mpp_create(&dec_ctx.ctx, &dec_ctx.mpi);
    if (ret) {
        mpp_err("创建解码器失败: %d\n", ret);
        return -1;
    }
    
    /* 配置H264解码参数 */
    ret = dec_ctx.mpi->control(dec_ctx.ctx, MPP_DEC_SET_FRAME_INFO, 
                             (MppParam)MPP_FRAME_FMT_YUV420SP);
    ret |= dec_ctx.mpi->control(dec_ctx.ctx, MPP_DEC_SET_OUT_BLOCK, 
                              (MppParam)MPP_TRUE);
    if (ret) {
        mpp_err("配置解码参数失败\n");
        goto DECODE_OUT;
    }
    
    /* 打开输入输出文件 */
    dec_ctx.input_fp = fopen(input, "rb");
    dec_ctx.output_fp = fopen(output, "wb");
    if (!dec_ctx.input_fp || !dec_ctx.output_fp) {
        mpp_err("打开文件失败\n");
        goto DECODE_OUT;
    }
    
    /* 创建解码线程 */
    pthread_t thd;
    pthread_create(&thd, NULL, decode_thread, &dec_ctx);
    pthread_join(thd, NULL);

DECODE_OUT:
    /* 释放资源 */
    if (dec_ctx.input_fp) fclose(dec_ctx.input_fp);
    if (dec_ctx.output_fp) fclose(dec_ctx.output_fp);
    if (dec_ctx.ctx) {
        dec_ctx.mpi->reset(dec_ctx.ctx);
        mpp_destroy(dec_ctx.ctx);
    }
    RK_MPI_SYS_Exit();
    return ret;
}





# 驱动层

mpp_dev_probe

VPU 的 驱动最主要的就是这个函数
