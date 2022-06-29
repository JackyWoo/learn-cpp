//
// Created by wujianchao5 on 2022/6/29.
//

#include <iostream>
#include <string>

#include <Poco/NumberFormatter.h>


int main()
{
    using Poco::NumberFormatter;
    std::cout<<NumberFormatter::formatHex(1, true)<<std::endl;
}