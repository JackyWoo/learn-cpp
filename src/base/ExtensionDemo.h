//
// Created by wujianchao5 on 2025/2/12.
//

#ifndef EXTENSIONDEMO_H
#define EXTENSIONDEMO_H

#include <iostream>

class Base
{
public:
    int c1{1};
    virtual int foo();
};

class D1 : virtual public Base
{
public:
    // int c1{};
    int c2{2};
    int foo() override;
};

class D2 : virtual public Base
{
public:
    // int c1{};
    int c3{3};
    int foo() override;
};

class D3 : public D1, D2
{
public:
    // int c1{};
    int c4{4};
    int foo() override;
};

#endif //EXTENSIONDEMO_H
