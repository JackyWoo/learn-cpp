//
// Created by wujianchao5 on 2022/8/9.
//

#include "ObjectCreator.h"
#include <string>
#include <iostream>

using namespace std;

struct Queue1
{
    Queue1(const string & name, int age) : _name(name), _age(age)
    {
    }
    string _name;
    int _age;
};

struct Bar
{
    Bar()
    {
        cout << "create bar" <<endl;
    }
    string _name = "bar";
    int _age = 18;
};

int main()
{
    auto args = std::make_tuple<string, int>("Jacky", 20);
    auto * foo = ObjectCreator<Queue1, string, int>::create(args);
    cout << foo->_name << foo->_age << endl;

    auto args2 = std::make_tuple();
    auto * bar = ObjectCreator<Bar>::create(args2);
    cout << bar->_name << bar->_age << endl;


}