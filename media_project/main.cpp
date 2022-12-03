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


int main(int argc, const char * argv[]) {
//    ffmpeg_log();
    dir_use();
    log_media_info();
    return 0;
}
