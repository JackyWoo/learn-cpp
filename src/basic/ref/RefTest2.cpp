//
// Created by wujianchao5 on 2020/12/25.
//

#include <memory>
#include <iostream>
#include <type_traits>

class Queue1
{
public:
    Queue1() { std::cout << "Foo Default constructor\n"; }
    Queue1(const Queue1 &) { std::cout << "Foo Copy\n"; }
    Queue1(Queue1 &&)  noexcept { std::cout << "Foo Move\n"; }
};

std::aligned_storage<sizeof(Queue1)> contents;
Queue1 &alias = *reinterpret_cast<Queue1 *>(&contents);

void ByVal(Queue1 a) {
    new(&contents) Queue1(std::move(a));
    alias.~Queue1();
}

void ByLCRef(Queue1 const &a) {
    new(&contents) Queue1(a);
    alias.~Queue1();
}

void ByRRef(Queue1 &&a) {
    new(&contents) Queue1(std::move(a));
    alias.~Queue1();
}

int main() {
    std::cout << "Foo a\n";
    Queue1 a;
    std::cout << "\n";

    std::cout << "ByVal(a);\n";
    ByVal(a);

    std::cout << "\nByVal(std::move(a));\n";
    ByVal(std::move(a));

    std::cout << "\nByVal(Foo());\n";
    ByVal(Queue1());

    std::cout << "\nByLCRef(a);\n";
    ByLCRef(a);

    std::cout << "\nByRRef(std::move(a));\n";
    ByRRef(std::move(a));

    std::cout << "\nByRRef(Foo());\n";
    ByRRef(Queue1());
}