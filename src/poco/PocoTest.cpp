//
// Created by wujianchao5 on 2022/6/29.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <format>

#include <Poco/NumberFormatter.h>
#include <Poco/Timestamp.h>


int main()
{
    using Poco::NumberFormatter;
    using Poco::Timestamp;
    std::cout<<NumberFormatter::formatHex(10, true)<<std::endl;

    std::unordered_map<int32_t, Timestamp> operations;

    auto start = operations[0];
    auto elapsed = Poco::Timestamp() - operations[0];
    std::cout<<elapsed<<std::endl;

}