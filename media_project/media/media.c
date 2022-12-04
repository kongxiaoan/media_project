//
//  media.c
//  media_project
//
//  Created by mtkj on 2022/12/3.
//

#include "media.h"

/**
 常用结构体 (单独学习)
 */
void common_stract(void) {
//    AVFormatContext 格式上下文环境 链接多个API之间的桥梁
//    AVStream 流/轨的概念，可以读取流
//    AVPacket 流中的每一块数据就是包 操作包可以操作流
}


/**
 操作流的基本步骤
 */
void use_stream(void) {
    // 解复用
    
    // 获取流
    
    // 读数据包
    
    // 释放相关资源
}


void media_info(void) {
    av_log_set_level(AV_LOG_DEBUG);
    int result;
    
    AVFormatContext *fmt_ctx = NULL;
    //第三个参数 不指定时 会自动解析文件格式
    //第四个是命令行的一些参数
    result = avformat_open_input(&fmt_ctx, MEDIA_BASE_PATH"/ffmpeg_1.mp4", NULL, NULL);
    
    if(result < 0) {
        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(result));
        goto _fail;
    }
  
    /**
     第二个参数 流的索引值
     */
    av_dump_format(fmt_ctx, 0, MEDIA_BASE_PATH"/ffmpeg_1.mp4", 0);// 输入0 输出1

_fail:
    av_log(NULL, AV_LOG_INFO, "释放操作\n");
    avformat_close_input(&fmt_ctx);
    
}

/**
 打印音/视频信息
 */
void log_media_info(void) {
    
    //打开多媒体文件
//    avformat_open_input(<#AVFormatContext **ps#>, <#const char *url#>, <#const AVInputFormat *fmt#>, <#AVDictionary **options#>)
//    avformat_close_input(<#AVFormatContext **s#>)
    //打印多媒体信息
//    av_dump_format(<#AVFormatContext *ic#>, <#int index#>, <#const char *url#>, <#int is_output#>)
    
    media_info();
    
}

void _get_audio(const char* src, const char* dst) {
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

/**
 获取音频数据
 */
void get_audio_data(const char* src, const char* dst){
    //初始化一个数据包结构体
//    av_init_packet(<#AVPacket *pkt#>)
    //在多媒体文件中找到想要的流
//    av_find_best_stream(<#AVFormatContext *ic#>, <#enum AVMediaType type#>, <#int wanted_stream_nb#>, <#int related_stream#>, <#const AVCodec **decoder_ret#>, <#int flags#>)
    //获取流中的数据包
//    av_read_frame(<#AVFormatContext *s#>, <#AVPacket *pkt#>)
    //释放引用计数 防止内存泄漏
//    av_packet_unref(<#AVPacket *pkt#>)
    _get_audio(src, dst);
}
