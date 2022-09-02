//
// Created by wujianchao5 on 2022/8/22.
//

#include "StackTrace.h"
#include <iostream>
#include <string>

int main()
{
    StackTrace::Frame frame{nullptr, nullptr, "toString", "Poco::StackTrace", "StackTrace.cpp", 100};
    StackTrace st;
    std::cout << st.translate(&frame) << std::endl;
}