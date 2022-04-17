//
// Created by wujianchao5 on 2020/12/21.
//

#include <memory>
#include <string>
#include <iostream>

using namespace std;

using StringPtr = std::shared_ptr<std::string>;
using String = std::string;

struct Node
{
    String name;
    StringPtr desc;
    int type{};
    char * child{};
};

/**
 * 参数类型：
 *      1. const Node& node : 那么main函数中的node不会被move
 *      2. Node node : 那么main函数中的node会被move
 *
 * 默认的move构造函数的动作是：
 *      1. 递归调用字段（包含集成类中的字段）的移动构造函数
 *
 * 当一下情况是默认不生成移动构造函数：
 *      1. 有些字段不包含移动构造函数
 *      2. 类或class有自定义的析构函数
 */
void addNode(const Node& node){
    std::cout<<node.name<<std::endl;
    std::cout<<node.desc<<std::endl;
    std::cout<<node.type<<std::endl;
}

int main(){
    Node node;
    std::cout<<node.type<<" "<<std::endl;
    if(node.child)
    {
        cout<<"aa"<<endl;
    }
    node.type = 10;
    node.name = "Lina";
    node.desc = std::make_shared<String>("Lina is a hero.");
    node.child = "I am a child";
    addNode(std::move(node));
    return 0;
}