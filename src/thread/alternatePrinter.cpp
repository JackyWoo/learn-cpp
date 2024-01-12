//
// Created by wujianchao5 on 2024/1/10.
//
#include <iostream>
#include <string>
#include <thread>

using String = std::string;

void print(std::mutex & mutex, std::condition_variable & cv, bool & turn_a, const String & content)
{
    for (size_t i = 0; i < 100; i++)
    {
        std::unique_lock lock(mutex);

        /// print content if my turn
        if (turn_a && content == "A")
        {
            std::cout << content << std::endl;
            turn_a = false;
        }
        else if (!turn_a && content != "A")
        {
            std::cout << content << std::endl;
            turn_a = true;
        }

        /// notify another thread
        cv.notify_one();

        /// waiting
        cv.wait(lock);
    }
}

int main()
{
    bool turn_a = true;
    std::mutex mutex;
    std::condition_variable cv;

    std::thread t1([&] { print(mutex, cv, turn_a, "A"); });
    std::thread t2([&] { print(mutex, cv, turn_a, "B"); });

    t1.join();
    t2.join();
}