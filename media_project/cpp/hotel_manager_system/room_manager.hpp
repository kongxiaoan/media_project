//
//  room_manager.hpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
//客房管理模块
#pragma once
#include "guest_room.hpp"
#include "room_manager.hpp"
#include <map>
#include <string>
class GuestRoomManager {
public:
    GuestRoomManager();
    //查找客房
    bool check_in(const string);
    //添加客房
    void add_room(const GuestRoom room);
    //移除客房
    bool remove_room(const string);
    //设置客房状态
    void set_room_state(string number);
private:
    map<string, GuestRoom> m_room_list;
};


