//
// Created by wujianchao5 on 2023/4/25.
//

#include <iostream>
#include <mutex>
#include <thread>

/// bad case
void testDataRace_1()
{
    int32_t counter = 0;

    std::thread t([&counter] { std::cout << counter << std::endl; });

    counter = 1;
    std::cout << counter << std::endl;

    t.join();
}


void testDataRace_1_a()
{
    std::atomic<int32_t> counter = 0;

    std::thread t([&counter] { std::cout << counter << std::endl; });

    counter = 1;
    std::cout << counter << std::endl;

    t.join();
}


/// expected? can not detected
void testDataRace_2()
{
    std::atomic<int32_t> counter = 0;

    std::thread t([&counter] { counter++; });

    if (counter)
        std::cout << counter << std::endl; // not deterministic

    t.join();
}


void testDataRace_2_a()
{
    int32_t counter = 0;
    std::mutex m1;

    std::thread t([&counter, &m1] {
        std::unique_lock lock(m1);
        counter++;
    });

    {
        std::unique_lock lock(m1);
        if (counter)
            std::cout << counter << std::endl;
    }

    t.join();
}


/// expected? can not detected
void testDataRace_3()
{
    std::atomic<int32_t> counter = 0;

    std::thread t([&counter] { counter = counter++ % 10; });

    std::thread t2([&counter] { counter = counter++ % 10; });

    counter = counter++ % 10;

    t.join();
    t2.join();
}

void testDataRace_3_a()
{
    int32_t counter = 0;
    std::mutex m1;

    std::thread t([&counter, &m1] {
        std::unique_lock lock(m1);
        counter = counter++ % 10;
    });

    {
        std::unique_lock lock(m1);
        counter = counter++ % 10;
    }
    t.join();
}


int main()
{
    testDataRace_3();
}
