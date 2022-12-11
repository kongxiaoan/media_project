//
//  guest_room.cpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
//

#define _CRT_SECURE_NO_WARNINGS
#include "guest_room.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

//定义字符串指针，指向一个文件
const char* const room_data_file = "room.dat";
GuestRoom::GuestRoom(string name, int price, int bed_num, int area, ROOM_STATE state=FREE) {
    this->m_name = name;
    this->m_price = price;
    this->m_bed_number = bed_num;
    this->m_area = area;
    this->m_number = generate_number();
    this->m_state = state;
}
/**
 生成客房编号
 */
string GuestRoom::generate_number() {
    //本地时间字符串
    time_t my_time = time(NULL);
    struct tm* my_tm = localtime(&my_time);
    char time_buff[128] = {0};
    sprintf(time_buff, "%d%d", my_tm->tm_yday, my_tm->tm_sec);
    //生成随机数
    int rand_num = rand() % 50;
    char buf[128] = {0};
    sprintf(buf, "%d", rand_num);
    //拼接字符串作为房间编号
    return string(time_buff) + string(buf);
}

string GuestRoom::show_state() {
    if(m_state == FREE)
        return "空闲";
    if(m_state == CHECK_IN)
        return "入住";
    return "状态异常";
}

/**
 保存数据
 */
bool GuestRoom::save_data(map<string, GuestRoom>& room_list) {
    //1.打开文件
    ofstream ofs(room_data_file, ios::out);
    if(!ofs) {
        return false;
    }
    //2.写入对象数据
    for(auto& room : room_list) {
       //写入m_name成员变量所占内存大小及其值
        size_t name_len = room.second.m_name.size();
        ofs.write(reinterpret_cast<const char*>(&name_len), sizeof(size_t));
        ofs.write(room.second.m_name.c_str(), name_len);
        ofs.write(reinterpret_cast<const char*>(&room.second.m_price), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&room.second.m_area), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&room.second.m_bed_number), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&room.second.m_state), sizeof(enum ROOM_STATE));
        //写入number成员变量所占内存大小及值
        size_t number_len = room.second.m_number.size();
        ofs.write(reinterpret_cast<const char*>(&number_len), sizeof(size_t));
        ofs.write(room.second.m_number.c_str(), number_len);
    }
    ofs.close();
    return true;
}

map<string, GuestRoom> GuestRoom::read_data() {
    //打开文件
    map<string, GuestRoom> room_list;
    ifstream ifs(room_data_file, ios::in);
    if(!ifs) {
        return room_list;
    }
    
    //写入对象数据
    while (ifs.peek() != EOF) {
        GuestRoom room;
        //读m_name 成员变量及所占内存
        size_t name_len = 0;
        ifs.read(reinterpret_cast<char*>(&name_len), sizeof(size_t));
        char name_buffer[128] = {};
        ifs.read(name_buffer, name_len);
        room.m_name = name_buffer;
        //写入m_price
        ifs.read(reinterpret_cast<char*>(&room.m_price),sizeof(int));
        //写入m_area
        ifs.read(reinterpret_cast<char*>(&room.m_area),sizeof(int));
        //写入 bed_number
        ifs.read(reinterpret_cast<char*>(&room.m_bed_number),
                 sizeof(int));
        //写入 state
        ifs.read(reinterpret_cast<char*>(&room.m_state),
                sizeof(enum ROOM_STATE));
        //写入m_number成员变量所占内存大小及其值
        size_t number_len = 0;
        ifs.read(reinterpret_cast<char*>(&number_len),sizeof(size_t));
                char number_buffer[128] = { 0 };
        ifs.read(number_buffer, number_len);
                room.m_number = number_buffer;
        //将数据存储到map容器中
        room_list.insert(make_pair(room.m_number, room));
        }
    //3.关闭文件
    ifs.close();
    return room_list;
}

string GuestRoom::get_num() {
    return m_number;
}


void GuestRoom::set_state() {
    m_state = CHECK_IN;
}

string GuestRoom::get_name() {
    return m_name;
}

int GuestRoom::get_price(){
    return m_price;
}

int GuestRoom::get_area() {
    return m_area;
}

int GuestRoom::get_bed_num() {
    return m_bed_number;
}




