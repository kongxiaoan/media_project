//
//  room_manager.cpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
// 客房管理模块


#include "room_manager.hpp"
#include "guest_room.hpp"
#include <iostream>
using namespace std;

GuestRoomManager::GuestRoomManager() {
    GuestRoom().read_data();
}

bool GuestRoomManager::check_in(const string number) {
    GuestRoom grm;
    m_room_list = grm.read_data();
    if(m_room_list.find(number) == m_room_list.end()) {
        return false;
    } else {
        return true;
    }
}


void GuestRoomManager::add_room(GuestRoom room) {
    if(check_in(room.get_num())) {
        cout <<"房间编号已经存在"<<endl;
        return;
    }
    m_room_list.insert(make_pair(room.get_num(), room));
    GuestRoom().save_data(m_room_list);
}

//删除客房数据
 bool GuestRoomManager::remove_room(const string number){
      //判断客房编号是否存在
      if (!check_in(number))
      {
           cout << "房间编号不存在" << endl;
           return false;
      }
      //删除
      m_room_list = GuestRoom().read_data();
      m_room_list.erase(number);
      //更新文件
      GuestRoom().save_data(m_room_list);
      return true;
 }


//设置客房状态
 void GuestRoomManager::set_room_state(string number){
      if (!check_in(number)){
           cout << "房间编号不存在" << endl;
           return;
     } else {
           //将文件中的客房数据读取到文件中
           m_room_list = GuestRoom().read_data();
           //设置为入住状态
           m_room_list[number].set_state();
           //将数据保存到文件中
           GuestRoom().save_data(m_room_list);
      }
 }
