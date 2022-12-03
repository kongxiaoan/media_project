//
//  ffmpeg-01.h
//  media_project
//
//  Created by mtkj on 2022/12/3.
// 1. 日志使用及目录操作
//
//

#ifndef ffmpeg_01_h
#define ffmpeg_01_h

#include <stdio.h>
#include "libavutil/log.h"
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
/**
 测试日志
 */
int ffmpeg_log();

/**
 删除文件
 */
int file_delete();

/**
 重命名
 */
int file_rename();

/**
 操作目录
 */
int dir_use();

#endif /* ffmpeg_01_h */
