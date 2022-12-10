//
//  h_264.h
//  media_project
//
//  Created by mtkj on 2022/12/10.
// 抽取(h264)视频数据
//

#ifndef h_264_h
#define h_264_h

#include <stdio.h>
#include "libavformat/avformat.h"

/**
 start code
 sps/pps
 codec -> extradata
 */

/**
 抽取H264信息
 */
void get_h264_info(void);

#endif /* h_264_h */
