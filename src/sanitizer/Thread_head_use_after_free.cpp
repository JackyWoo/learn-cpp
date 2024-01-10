//
// Created by wujianchao5 on 2023/4/25.
//

#include <iostream>
#include <thread>

int main()
{
    struct Foo
    {
        int32_t id{1};
    };
    Foo * foo = new Foo();
    std::thread t([&foo] {
        // wait for main thread delete foo
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::cout << (*foo).id << std::endl; // use foo after delete
    });
    delete foo;
    t.join();
}