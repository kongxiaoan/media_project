//
//  logger.c
//  media_project
//
//  Created by mtkj on 2022/12/3.
//

#include "logger.h"


void LOGE(void *avcl, int level, const char *fmt, ...) {
    //1. 头文件 libavutil/log.h
    //2. 设置日志级别
    av_log_set_level(AV_LOG_DEBUG);
    //3. 打印日志

    av_log(avcl,AV_LOG_DEBUG, fmt, ...);


}
