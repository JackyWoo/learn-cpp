#include <chrono>
#include <iostream>


inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
}

int main()
{
    size_t n = 3;
    auto t1 = getCurrentTimestamp();

    for (size_t i=0; i<n; i++)
        std::chrono::steady_clock::now();

    auto t2 = getCurrentTimestamp();

    for (size_t i=0; i<n; i++)
        std::chrono::system_clock::now();

    auto t3 = getCurrentTimestamp();

    std::cout << "steady clock: " << std::to_string(t2 - t1) << "ns" << std::endl;
    std::cout << "system clock: " << std::to_string(t3 - t2) << "ns" << std::endl;
}