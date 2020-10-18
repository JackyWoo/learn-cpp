//
// Created by wujianchao5 on 2020/12/15.
//

#include <iostream>
#include <memory>
#include <string>

using String = std::string;
using namespace std;

struct Foo
{
    String name;
    explicit Foo(const String & name_)
    {
        this->name = name_;
    }
    ~Foo() { cout << "destroy : " << name << endl; }
};

void test()
{
    //对象指针
    std::unique_ptr<String> ptr1(new String("123"));

    std::unique_ptr<String> ptr2;

    //    std::cout << *ptr1 << std::endl;
    //    std::cout << ptr1->size() << std::endl;

    //ptr1指向的内容转移给ptr4后，ptr1就指向了空
    std::unique_ptr<String> ptr4 = std::move(ptr1);

    //    std::cout << *ptr1 << std::endl;
    std::cout << *ptr4 << std::endl;

    //释放unique_ptr，但是内存空间不会被释放
    String * ptr3 = ptr4.release();
    std::cout << *ptr3 << std::endl;


    //——----------------使用场景是：new的资源忘记释放的场景
    //  new的对象不需要显示释放

    // 数组
    std::unique_ptr<int[]> p(new int[5]{1, 2, 3, 4, 5});
    p[0] = 0;

    //STL
}

/**
 *
 */
void restTest()
{
    String * ptr1 = new String("123");
    std::unique_ptr<String> uniqPtr(ptr1);

    std::cout << *ptr1 << std::endl;

    String * ptr2 = new String("abc");
    /**
     * rest 将 ptr2清空，并把uniqPtr内容替换
     */
    uniqPtr.reset(ptr2);

    std::cout << *uniqPtr << std::endl;
    //    std::cout << *ptr1 << std::endl;
    std::cout << *ptr2 << std::endl;

    /**
     * 没有参数将清空uniqPtr
     */
    uniqPtr.reset();
    std::cout << *uniqPtr << std::endl;
}

//TODO
void releaseTest()
{
    int * ptr1 = new int(123);
    std::unique_ptr<int> uniqPtr(ptr1);

    std::cout << *uniqPtr << std::endl;

    int * ptr2 = uniqPtr.release();

    /**
     * uniqPtr 释放后将不能在访问，否则segfault
     */
    //    std::cout << *uniqPtr << std::endl;
    std::cout << *ptr1 << std::endl;
    std::cout << *ptr2 << std::endl;
}

void test10()
{
    using namespace std;
    std::unique_ptr<int> p5(new int);
    *p5 = 10;
    // p 接收 p5 释放的堆内存
    int * p = p5.release();
    cout << *p << endl;
    //判断 p5 是否为空指针
    if (p5)
    {
        cout << "p5 is not nullptr" << endl;
    }
    else
    {
        cout << "p5 is nullptr" << endl;
    }
    std::unique_ptr<int> p6;
    //p6 获取 p 的所有权
    p6.reset(p);
    cout << *p6 << endl;
}

void test20()
{
    std::unique_ptr<Foo> ptr1 = make_unique<Foo>("Jacky");
    std::unique_ptr<Foo> ptr2 = make_unique<Foo>("Tom");
    ptr1 = move(ptr2);
    cout<< "aa" <<endl;

    std::shared_ptr<Foo> sptr1 = make_shared<Foo>("car");
    std::shared_ptr<Foo> sptr2 = make_shared<Foo>("bike");
    sptr1 = sptr2;
    cout<< "aa" <<endl;
}

int main()
{
//    test();
    //    restTest();
    //    releaseTest();
    //    test10();
    test20();
}