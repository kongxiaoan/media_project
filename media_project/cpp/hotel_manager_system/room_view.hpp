//
//  room_view.hpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
//界面模块
#pragma once
#include "room_view.hpp"
#include "room_manager.hpp"

class RoomView{
public:
    void show_menu();
    void add_room();
    void remove_data();
    void set_room();
    void show_all();
    void run();
private:
    GuestRoomManager m_grm;
};
