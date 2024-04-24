//
// Created by wujianchao5 on 2020/12/30.
//

#include <iostream>
#include <memory>

using namespace std;


class Foo
{
public:
    int a;
    void func()
    {
        std::cout << "Foo::func" << std::endl;
    }
};

class Base
{
public:
    long a;
    virtual void func()
    {
        std::cout << "Base::func" << std::endl;
    }
    virtual void func1()
    {
        std::cout << "Base::func1" << std::endl;
    }
};

class Derived : public Base
{
public:
    void func() override
    {
        std::cout << "Derived::func" << std::endl;
    }
    void func1() override
    {
        std::cout << "Derived::func1" << std::endl;
    }
};


int main()
{
    cout << "sizeof(Foo) " << sizeof (Foo) << endl;
    cout << "sizeof(Base) " << sizeof (Base) << endl;
    cout << "sizeof(Derived) " << sizeof (Derived) << endl;

    auto * b = new Base;
    b->a = 1;

    cout << "address of b " << b << endl;
    cout << "address of b virtual ptr " << *reinterpret_cast<uint64_t *>(b) << endl;
    cout << "address of b.a " << &b->a << endl;

    auto * d = new Derived;
    d->a = 1;

    cout << "address of d " << d << endl;
    cout << "address of d virtual ptr " << *reinterpret_cast<uint64_t *>(d) << endl;
    cout << "address of d.a " << &d->a << endl;

    delete b;
    delete d;
}