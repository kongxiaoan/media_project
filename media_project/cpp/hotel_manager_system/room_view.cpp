//
//  room_view.cpp
//  HotelManagementSystem
//
//  Created by mtkj on 2022/12/11.
//

#include "room_view.hpp"
#include "room_manager.hpp"
#include "guest_room.hpp"
#include<iostream>
#include<iomanip>
using namespace std;

//显示菜单
void RoomView::show_menu(){
    cout << "1. 显示客房信息" << endl;
    cout << "2. 设置客房状态" << endl;
    cout << "3. 删除客房信息" << endl;
    cout << "4. 添加客房信息" << endl;
    cout << "5. 退出管理系统" << endl;
}
// 添加客房
void RoomView::add_room(){
    string name;
    int price;
    int bed_num;
    int area;
    cout << "请输入客房名称:"; cin >> name;
    cout << "请输入客房价格:"; cin >> price;
    cout << "请输入客房床数量:"; cin >> bed_num;
    cout << "请输入客房面积:"; cin >> area;
    //创建客房对象
    GuestRoom room(name, price, bed_num, area,FREE);
    //调用客房管理模块的add_room()函数添加客房
    m_grm.add_room(room);
}

//删除客房
void RoomView::remove_data(){
    cout << "请输入您要删除的客房编号:";
    string room_number;
    cin >> room_number;
    // 调用客房管理模块的remove_data()函数
    m_grm.remove_room(room_number);
}
//设置客房状态
void RoomView::set_room(){
    string number;
    cout << "请输入要设置的客房编号:"; cin >> number;
    m_grm.set_room_state(number);
}

//显示所有客房信息
void RoomView::show_all(){

    cout << "------------------------------------------------" << endl;
    cout << "编号" << "\t   " << "名称" << "\t\t" << "面积" << "\t"
    << "价格" << "\t" << "床位数量" << "\t" << "状态" << endl;
    cout << "-------------------------------------------------" << endl;
    GuestRoom grm;
    map<string, GuestRoom> rooms;
    rooms=grm.read_data();
    if(rooms.empty()){
        cout<<"请添加客房信息后再进行操作！"<<endl;
                    }
        for (auto& room : rooms){
            cout << room.second.get_num() << "\t" << setw(10)
                << room.second.get_name() << "\t"<< room.second.get_area()
                << "平方\t" << room.second.get_price() << "元\t  "
                << room.second.get_bed_num() << "个\t\t"
                << room.second.show_state() << endl;
        }
        cout << "-------------------------------------------------" << endl;
}
//启动酒店管理系统
void RoomView::run(){
    //定义state变量标识系统是否启动
    bool state = true;
    while (state){
        //显示菜单
        show_menu();
        //获得输入的命令
        int flag = -1;
        cout << "请输入您的操作:";
        cin >> flag;
        system("cls");
        //根据输入执行相应的操作
        switch (flag){
            case 1:
                show_all();
                break;
            case 2:
                set_room();
                break;
            case 3:
                remove_data();
                break;
            case 4:
                add_room();
                break;
            case 5:
                exit(0);
            default:
                break;
            }
    }
}
