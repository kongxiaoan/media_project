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
    av_log(NULL,AV_LOG_INFO, "输入文件 %s \n, 输出文件 %s \n ", src, dst);
    int result;
    char errors[1024];

    // 1. 两个参数
    //存储压缩数据
    AVPacket pkt;
    //上下文
    AVFormatContext *fmt_ctx = NULL;
    AVFormatContext *fmt_out = NULL;
    //要拷贝的数据流索引
    int audio_index,video_index;
    
    //输入流
    AVStream *in_stream = NULL;
    
    //输出流
    AVStream *out_stream = NULL;
    
    //支持各种各样的输出文件格式，MP4，FLV，3GP等等
    AVOutputFormat *output_fmt = NULL;
    
    //打开输入文件，关于输入文件的所有就保存到fmt_ctx中了
    result = avformat_open_input(&fmt_ctx, src, NULL, NULL);
    
    if(result < 0) {
        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(result));
        avformat_close_input(&fmt_ctx);
        return;
    }
    
    //查看流信息
//    if ((result = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
//            av_strerror(result, errors, 1024);
//            av_log(NULL, AV_LOG_DEBUG, "failed to find stream info: %s, %d(%s)\n",
//                   src,
//                   result,
//                   errors);
//            return;
//        }

    
//    av_dump_format(fmt_ctx, 0, src, 0);// 输入0 输出1

    if(fmt_ctx->nb_streams < 2) {
        //流数小于2，说明这个文件音频、视频流这两条都不能保证，输入文件有错误
        av_log(NULL, AV_LOG_ERROR, "输入文件错误，流不足2条\n");
        return;
    }
    //拿到文件中音频流
    // 2. get stream
//    audio_index = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1,-1, NULL, 0);
//    if(audio_index < 0) {
//        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(audio_index));
//        avformat_close_input(&fmt_ctx);
//        return;
//    }
    
    video_index = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if(video_index < 0) {
        av_log(NULL,AV_LOG_ERROR, "%s", av_err2str(audio_index));
        avformat_close_input(&fmt_ctx);
        return;
    }
    
    in_stream = fmt_ctx->streams[video_index];
    
    //参数信息
    AVCodecParameters *in_codecpar = in_stream->codecpar;
    
    //输出环境上下文
    fmt_out = avformat_alloc_context();
    //根据目标文件名生成最适合的输出容器
    output_fmt = av_guess_format(NULL,dst,NULL);
    if(!output_fmt){
        av_log(NULL, AV_LOG_DEBUG, "根据目标生成输出容器失败！\n");
        return;
    }
    
    fmt_out->oformat = output_fmt;
    
    //新建输出流
    out_stream = avformat_new_stream(fmt_out, NULL);
    if(!out_stream){
        av_log(NULL, AV_LOG_DEBUG, "创建输出流失败！%s\n", av_err2str(out_stream));
        return;
     }
    
    //将参数信息拷贝到输出流中，我们只是抽取音频流，并不做音频处理，所以这里只是Copy
    if((result = avcodec_parameters_copy(out_stream->codecpar, in_codecpar)) < 0 ){
        av_strerror(result, errors, 1024);
        av_log(NULL, AV_LOG_ERROR,"拷贝编码参数失败！, %d(%s)\n",
               result, errors);
        return;
    }
    
    out_stream->codecpar->codec_tag = 0;

    //初始化AVIOContext,文件操作由它完成
    if((result = avio_open(&fmt_out->pb, dst, AVIO_FLAG_WRITE)) < 0) {
        av_strerror(result, errors, 1024);
        av_log(NULL, AV_LOG_DEBUG, "Could not open file %s, %d(%s)\n",
               dst,
               result,
               errors);
        return;
    }
    
    
//    av_dump_format(fmt_out, 0, dst, 1);

    
    //初始化 AVPacket， 我们从文件中读出的数据会暂存在其中
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;
    
    //写头部信息
    if(avformat_write_header(fmt_out, NULL) < 0) {
        av_log(NULL,AV_LOG_ERROR, "打开输出文件时发生错误");
        return;
    }
    
    //读出每一帧数据
    while (av_read_frame(fmt_ctx,&pkt) >= 0) {
        if(pkt.stream_index == video_index) {
            pkt.pts = av_rescale_q_rnd(pkt.pts,in_stream->time_base, out_stream->time_base,(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
            pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));

//            pkt.dts = av_rescale_q_rnd(pkt.dts
//                                       , in_stream->time_base, out_stream->time_base, (AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            
            pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;
            pkt.stream_index = 0;
            //将包写到输出媒体文件
            av_interleaved_write_frame(fmt_out, &pkt);
            //减少引用计数（避免内存泄漏）
            av_packet_unref(&pkt);
        }
        
    }
    //写尾部信息
    av_write_trailer(fmt_out);
    avformat_close_input(&fmt_ctx);
    avio_close(fmt_out->pb);
}

/**
 获取音频数据
 */
void get_audio_data(void){
    //初始化一个数据包结构体
//    av_init_packet(<#AVPacket *pkt#>)
    //在多媒体文件中找到想要的流
//    av_find_best_stream(<#AVFormatContext *ic#>, <#enum AVMediaType type#>, <#int wanted_stream_nb#>, <#int related_stream#>, <#const AVCodec **decoder_ret#>, <#int flags#>)
    //获取流中的数据包
//    av_read_frame(<#AVFormatContext *s#>, <#AVPacket *pkt#>)
    //释放引用计数 防止内存泄漏
//    av_packet_unref(<#AVPacket *pkt#>)
    char* src = MEDIA_BASE_PATH"/ffmpeg_1.mp4";
    char* dst = MEDIA_BASE_PATH"/ffmpeg_2.mov";

    _get_audio(src, dst);
}
