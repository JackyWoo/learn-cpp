//
// Created by wujianchao5 on 2020/12/15.
//

#include <iostream>
#include <memory>
#include <string>

#include "../oop/Stock.h"

using String = std::string;

/**
 * shared_ptr为了解决堆内存释放问题，内部实现机制是引用技术
 * @return
 */
void test()
{
    //make_shared按照初始化对象本身的方式初始化：shared_ptr
    std::shared_ptr<String> ptr1 = std::make_shared<String>("123");
    //调用拷贝构造函数
    std::shared_ptr<String> ptr2(ptr1); //或者 std::shared_ptr<int> p4 = p3;

    std::shared_ptr<String> ptr3 = std::make_shared<String>("abc");
    //调用移动构造函数
    std::shared_ptr<String> ptr4(std::move(ptr3));

    std::shared_ptr<String> ptr5 = ptr1;


    ptr5.use_count();
    // exception when accessing null ptr
//    std::cout << *ptr3 << std::endl;

    //——----------------使用场景是：new的资源忘记释放的场景
    //  new的对象不需要显示释放
}


//自定义释放规则
void deleteInt(const int * p)
{
    std::cout << "delete int[] with udf deletor" << std::endl;
    delete[] p;
}

/**
 * 自定义释放规则
 */
void test1()
{
    //make_shared按照初始化对象本身的方式初始化：shared_ptr
    int * arr = new int[10];
    std::shared_ptr<int> ptr1(arr, deleteInt);
}

/**
 * lambda
 */
void test2()
{
    //make_shared按照初始化对象本身的方式初始化：shared_ptr
    int * arr = new int[10];
    std::shared_ptr<int> ptr1(arr, [](int * p) {
        std::cout << "delete int[] with lambda" << std::endl;
        delete[] p;
    });
}

void test3()
{
    //make_shared按照初始化对象本身的方式初始化：shared_ptr
    int * arr = new int[10];
    std::shared_ptr<int> ptr1(arr, [](int * p) {
        std::cout << "delete int[] with lambda" << std::endl;
        delete[] p;
    });

    std::shared_ptr<int> ptr2 = std::make_shared<int>(1);

    // 交换内容
    ptr1.swap(ptr2);

    //是否是唯一引用
    ptr1.unique();

    //释放空间
    ptr1.reset();
}

struct Pos {
    Pos(int a_, int b_): a(a_), b(b_){};
    Pos(const Pos & p): a(p.a), b(p.b){};
    int a;
    int b;

};

struct PosInvoker {
    PosInvoker(Pos & p_): p(p_){};
    Pos p;
};

std::shared_ptr<PosInvoker> stackTest()
{
    Pos p(1, 2);
    return std::make_shared<PosInvoker>(p);
}

void invoker(std::shared_ptr<int32_t> &p)
{
    p = std::make_shared<int32_t>(100);
}

int main()
{
//    test();
    //    test1();
    //    test2();
//    std::shared_ptr<PosInvoker> ptr = stackTest();
//    test();
//    std::cout<< ptr->p.a<<std::endl;

    std::shared_ptr<int32_t> p;
    invoker(p);
    std::cout << p.get() <<std::endl;
}