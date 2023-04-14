//
// Created by wujianchao5 on 2023/4/14.
//

#include <iostream>
#include <mutex>

int main()
{
    std::mutex m1;
    std::mutex m2;

    m1.lock();
    m2.lock();
    std::cout << "m1=>m2" << std::endl;
    m2.unlock();
    m1.unlock();

    m2.lock();
    m1.lock();
    std::cout << "m2=>m1" << std::endl;
    m1.unlock();
    m2.unlock();

    std::cout << "done" << std::endl;
}
