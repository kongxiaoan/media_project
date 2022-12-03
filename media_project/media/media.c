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
