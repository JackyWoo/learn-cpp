//
// Created by wujianchao5 on 2023/4/25.
//

#include <iostream>
#include <thread>
#include <mutex>

void deadlockButNotReport()
{
    std::mutex m1;
    std::mutex m2;

    std::thread t([&] {

        std::cout << "t try to acquire m1\n";
        m1.lock();
        std::cout << "t got m1\n";

        std::this_thread::sleep_for(std::chrono::milliseconds (20)); // wait main got m2

        std::cout << "t try to acquire m2\n";
        m2.lock();
        std::cout << "t got m2\n"; // code never executed

        m2.unlock();
        m1.unlock();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // wait t got m1

    std::cout << "main try to acquire m2\n";
    m2.lock();
    std::cout << "main got m2\n";

    std::cout << "main try to acquire m1\n";
    m1.lock();
    std::cout << "main got m1\n"; // code never executed

    m1.unlock();
    m2.unlock();

    t.join();
}

// not deadlock, but report potential deadlock
void notDeadlockButReport()
{
    std::mutex m1;
    std::mutex m2;

    // m1 => m2
    std::cout << "t try to acquire m1\n";
    m1.lock();
    std::cout << "t got m1\n";

    //std::this_thread::sleep_for(std::chrono::microseconds (2)); // wait main got m2

    // code never executed
    std::cout << "t try to acquire m2\n";
    m2.lock();
    std::cout << "t got m2\n";

    m2.unlock();
    m1.unlock();

    // m2 => m1
    std::cout << "main try to acquire m2\n";
    m2.lock();
    std::cout << "main got m2\n";

    // code never executed
    std::cout << "main try to acquire m1\n";
    m1.lock();
    std::cout << "main got m1\n";

    m1.unlock();
    m2.unlock();
}

int main()
{
    notDeadlockButReport();
    deadlockButNotReport();
}