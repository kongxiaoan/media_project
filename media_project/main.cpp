//
//  main.cpp
//  media_project
//
//  Created by mtkj on 2022/12/3.
//

#if defined(__cplusplus)
extern "C"
{
#endif
#include "media/media.h"
#include "ffmpeg-01.h"
#if defined(__cplusplus)
}
#endif


#include <iostream>

using namespace std;


int main(int argc, char * argv[]) {
//    ffmpeg_log();
    char* src = NULL;
    char* dst = NULL;
//    dir_use();
//    log_media_info();
    if(argc < 3) {
        av_log(NULL,AV_LOG_ERROR,"参数应该多于3个\n");
        return -1;
    }
    src = argv[1];
    dst = argv[2];
    if(!src || !dst) {
        av_log(NULL,AV_LOG_ERROR,"src or dst 是空的");
        return -1;
    }
    get_audio_data(src, dst);
    return 0;
}
