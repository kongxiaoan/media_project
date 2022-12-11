//
//  guest_room.hpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
// 客房模块实现

#ifndef guest_room_hpp
#define guest_room_hpp
#pragma once
#include <string>
#include <map>
using namespace std;

//定义enum ROOM_STATE枚举类型，表示客房状态：空闲、入住
enum ROOM_STATE {
    FREE = 0,
    CHECK_IN
};
//定义客房类
class GuestRoom{
public:
    //定义默认构造函数
    GuestRoom() = default;
    GuestRoom(string,int,int,int,ROOM_STATE);
    //生成客房编号
    string generate_number();
    //展示客户状态
    string show_state();
    //保存数据
    bool save_data(map<string, GuestRoom>&);
    map<string,GuestRoom> read_data();
public:
    //获取客房编号
    string get_num();
    //获取客房名称
    string get_name();
    //获取客房价格
    int get_price();
    //获取客房面积
    int get_area();
    //获取客房床位数量
    int get_bed_num();
    //设置客房状态
    void set_state();
private:
    //客房编号
    string m_number;
    //客房价格
    int m_price;
    //客房面积
    int m_area;
    //客房床位数量
    int m_bed_number;
    //客房名称
    string m_name;
    //客房状态
    enum ROOM_STATE m_state;
};

#endif /* guest_room_hpp */
