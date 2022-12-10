//
//  media.h
//  media_project
//
//  Created by mtkj on 2022/12/3.
// 多媒体文件的基本概念 （流就是容器）
// 1. 流都是由不同的编码器编码的
// 2. 从流中读出的数据成为包
// 3. 在一个包中包含着一个多个帧
//

#ifndef media_h
#define media_h
#define MEDIA_BASE_PATH "/Users/mtkj/project/kpa/media/media_project"
#include <stdio.h>
#include "libavformat/avformat.h"


/**
 常用结构体
 */
void common_stract(void);

/**
 操作流的基本步骤
 */
void use_stream(void);

/**
 打印音/视频信息
 */
void log_media_info(void);

/**
 获取音频数据
 主要操作：
 1. 打开一个文件
 2. 从里面拿出一部分数据
 3. 在把这部分数据放到另一个文件中
 */
void get_audio_data(void);

#endif /* media_h */
