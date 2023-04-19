//
// Created by wujianchao5 on 2020/12/25.
//

#include <memory>
#include <iostream>
#include <type_traits>

class MyQueue
{
public:
    MyQueue() { std::cout << "Foo Default constructor\n"; }
    MyQueue(const MyQueue &) { std::cout << "Foo Copy\n"; }
    MyQueue(MyQueue &&)  noexcept { std::cout << "Foo Move\n"; }
};

std::aligned_storage<sizeof(MyQueue)> contents;
MyQueue &alias = *reinterpret_cast<MyQueue *>(&contents);

void ByVal(MyQueue a) {
    new(&contents) MyQueue(std::move(a));
    alias.~MyQueue();
}

void ByLCRef(MyQueue const &a) {
    new(&contents) MyQueue(a);
    alias.~MyQueue();
}

void ByRRef(MyQueue &&a) {
    new(&contents) MyQueue(std::move(a));
    alias.~MyQueue();
}

int main() {
    std::cout << "Foo a\n";
    MyQueue a;
    std::cout << "\n";

    std::cout << "ByVal(a);\n";
    ByVal(a);

    std::cout << "\nByVal(std::move(a));\n";
    ByVal(std::move(a));

    std::cout << "\nByVal(Foo());\n";
    ByVal(MyQueue());

    std::cout << "\nByLCRef(a);\n";
    ByLCRef(a);

    std::cout << "\nByRRef(std::move(a));\n";
    ByRRef(std::move(a));

    std::cout << "\nByRRef(Foo());\n";
    ByRRef(MyQueue());
}