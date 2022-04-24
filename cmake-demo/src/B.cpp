//
// Created by JackyWoo on 2022/4/22.
//

#include "B.h"
#include "A.h"


void B::say()
{
    cout << "I'am B!" << endl;
    A a;
    a.say();
    cout << "B Done!" << endl;
    cout << endl;
};