//
// Created by wujianchao5 on 2023/4/25.
//

#include <iostream>
#include <thread>

int main()
{
    std::thread t([] {
        std::cout << 1 << std::endl;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //t.join();
}