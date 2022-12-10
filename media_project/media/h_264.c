//
//  h_264.c
//  media_project
//
//  Created by mtkj on 2022/12/10.
//

#include "h_264.h"

void _get_video(const char* src, const char* dst) {
    av_log_set_level(AV_LOG_DEBUG);
    int result;
    int len;
    // 1. 两个参数
    
    AVPacket pkt;
    AVFormatContext *fmt_ctx = NULL;
    int audio_index;
    result = avformat_open_input(&fmt_ctx, src, NULL, NULL);
    
    if(result < 0) {
        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(result));
        avformat_close_input(&fmt_ctx);
        return;
    }
    
    FILE* dst_fd = fopen(dst, "wb");
    if(!dst_fd) {
        av_log(NULL,AV_LOG_ERROR, "%s", "文件打开失败");
        avformat_close_input(&fmt_ctx);
        return;
    }

    av_dump_format(fmt_ctx, 0, src, 0);// 输入0 输出1
    // 2. get stream
    result = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1,-1, NULL, 0);
    if(result < 0) {
        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(result));
        fclose(dst_fd);
        avformat_close_input(&fmt_ctx);
        return;
    }
    audio_index = result;
    
    av_init_packet(&pkt);
    
    while (av_read_frame(fmt_ctx,&pkt) >= 0) {
        if(pkt.stream_index == audio_index) {
            //3. audio 输出到aac 新文件
            len = fwrite(pkt.data, 1, pkt.size, dst_fd);
            if(len != pkt.size) {
                av_log(NULL,AV_LOG_WARNING, "%s", "文件大小有问题\n");
        
            }
        }
        av_packet_unref(&pkt);
    }
    av_log(NULL, AV_LOG_INFO, "释放操作\n");
    avformat_close_input(&fmt_ctx);
    if(dst_fd) {
        fclose(dst_fd);
    }
}


void get_h264_info(void){
//    _get_audio("", "");
}
