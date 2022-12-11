//
//  cpp_01.cpp
//  media_project
//
//  Created by mtkj on 2022/12/10.
//

#include "cpp_01.hpp"

#include <iostream>

//标准命名空间（解决命名冲突问题）
/**
 std是C++标准命名空间，由于C++标准库几乎都定义在std命名空间中，因此编写的所有C++程序都需要引入下列语句
 */
//使用using语句直接引用命名空间
using namespace std;

//自定义命名空间
namespace lib  {
    void func(){
        cout<<"hello c++"<<std::endl;
    }
};

int main1(int argc, char * argv[]) {
//命名空间的使用方式
//    lib::func();
    using lib::func;
    func();
    
    // 输入单个变量
    char c1,c2;
    cin>>c1;
    cin>>c2;
    // 输入多个变量
    string s;
    float f;
    cin>>s>>f;
    
    return 0;
}
