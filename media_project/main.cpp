//
//  main.cpp
//  media_project
//
//  Created by mtkj on 2022/12/3.
//
#include "guest_room.hpp"
#include<iostream>
#include<time.h>
#include<string>
#include "room_manager.hpp"
#include "room_view.hpp"

#if defined(__cplusplus)
extern "C"
{
#endif
//#include "media/media.h"
//#include "ffmpeg-01.h"
#if defined(__cplusplus)
}
#endif

using namespace std;

int hotel_manager_system(){
    RoomView grv;   //创建RoomView类对象
    grv.run();   //启动酒店管理系统
    return 0;
}


int main(int argc, char * argv[]) {
//    ffmpeg_log();
//    dir_use();
//    log_media_info();
    hotel_manager_system();
    return 0;
}




