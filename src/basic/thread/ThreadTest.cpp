//
// Created by wujianchao5 on 2020/12/15.
//

#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>

void throwException()
{
    std::cout << "throwException" << std::endl;
    throw std::invalid_argument("");
}


/**
 * 如果线程挂了，整个进程也会挂
 */
int main()
{
    auto ptr = std::make_shared<int32_t>(0);
    try
    {
        // std::thread t(throwException);
        std::vector<std::thread> threads;
        for (int32_t i = 0; i < 10; i++)
        {
            std::thread t([&ptr]() -> void { std::cout << *ptr << std::endl; });
            threads.push_back(std::move(t));
        }
        for (auto & t : threads)
        {
            t.join();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (...)
    {
    }
    std::cout << "main" << std::endl;

    uint8_t a{255};
    a++;
    std::cout << std::to_string(a) << std::endl;
}