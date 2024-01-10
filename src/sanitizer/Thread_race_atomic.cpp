//
// Created by wujianchao5 on 2023/4/25.
//

#include <iostream>
#include <mutex>
#include <thread>

// bad case: data race
void testDataRace()
{
    int32_t counter = 0;

    std::thread t1([&counter] {
        if (!counter)
            counter = 1;
    });
    std::thread t2([&counter] {
        if (!counter)
            counter = 2;
    });

    t1.join();
    t2.join();
}

// For user it is a bad case, but not detected
void testDataRaceAtomic()
{
    std::atomic<int32_t> counter = 0;

    std::thread t1([&counter] {
        counter = counter + 1;
    });
    std::thread t2([&counter] {
        counter = counter + 1;
    });

    t1.join();
    t2.join();
}

int main()
{
    testDataRace();
    testDataRaceAtomic();
}
