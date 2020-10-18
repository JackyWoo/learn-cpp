//
// Created by JackyWoo on 2021/11/3.
//

#include <iostream>

using namespace std;
int main()
{
    enum Type
    {
        CAR = 1,
        BIKE =2
    };

    Type t = CAR;

    cout<<to_string(t)<<endl;

}