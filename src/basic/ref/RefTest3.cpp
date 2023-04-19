//
// Created by wujianchao5 on 2020/12/25.
//

#include <iostream>
#include <memory>
#include <queue>
#include <type_traits>

struct Pos
{
    std::string a;
    std::string b;

    Pos(const std::string & a, const std::string & b) : a(a), b(b) { }

    Pos(const Pos & other) : a(other.a), b(other.b) { std::cout << "copy constructor\n"; }
    Pos(Pos && other) : a(std::move(other.a)), b(std::move(other.b)) { std::cout << "move constructor\n"; }

    friend std::ostream & operator<<(std::ostream & os, const Pos & pos)
    {
        os << "a: " << pos.a << " b: " << pos.b;
        return os;
    }
};

template <typename T>
class MyQueue
{
private:
    std::queue<T> queue;

public:
    MyQueue() = default;
    void push(T && value)
    {
        std::cout << "push T&&\n";
        queue.push(std::forward<T>(value));
    }
    void push(const T & value)
    {
        std::cout << "const push T&\n";
        queue.push(value);
    }
};

void bar(const Pos & value)
{
    std::cout << "rvalue" << std::endl;
}

void bar(Pos && value)
{
    std::cout << "lvalue" << std::endl;
}

template <typename T>
void foo(T && value)
{
    bar(std::forward<T>(value));
}

int main()
{
    Pos pos("1", "2");

    foo(pos);
    foo<Pos>({"1", "2"});

    MyQueue<Pos> queue;
    queue.push(pos);
    queue.push(std::move(pos));
}