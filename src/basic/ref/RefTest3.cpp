//
// Created by wujianchao5 on 2020/12/25.
//

#include <iostream>
#include <memory>
#include <queue>
#include <type_traits>

struct Pos
{
    Pos() { }
    std::string a;
    std::string b;

    Pos(const std::string & a, const std::string & b) : a(a), b(b) { }

    Pos(const Pos & other) : a(other.a), b(other.b) { std::cout << "copy constructor\n"; }
    Pos(Pos && other) : a(std::move(other.a)), b(std::move(other.b)) { std::cout << "move constructor\n"; }

    // copy = operator
    Pos & operator=(const Pos & other)
    {
        std::cout << "copy =\n";
        if (this != &other)
        {
            a = other.a;
            b = other.b;
        }
        return *this;
    }

    // move = operator
    Pos & operator=(Pos && other)
    {
        std::cout << "move =\n";
        if (this != &other)
        {
            a = std::move(other.a);
            b = std::move(other.b);
        }
        return *this;
    }

    friend std::ostream & operator<<(std::ostream & os, const Pos & pos)
    {
        os << "a: " << pos.a << " b: " << pos.b;
        return os;
    }
};

template <typename T>
class Queue1
{
private:
    std::queue<T> queue;

public:
    Queue1() = default;

    void push(T && value)
    {
        std::cout << "Queue1 push T&&\n";
        queue.push(std::forward<T>(value));
    }

    void push(const T & value)
    {
        std::cout << "Queue1 const push T&\n";
        queue.push(value);
    }
};


class Queue2
{
private:
    std::queue<Pos> queue;

public:
    Queue2() = default;

    template <typename T>
    void push(T && value)
    {
        std::cout << "Queue2 push T&&\n";
        queue.push(std::forward<T>(value));
    }

    void pop(Pos & pos)
    {
        pos = queue.front(); // copy = operator
        // pos = std::move(queue.front()); // move = operator
        queue.pop();
    }
};

int main()
{
    //    Pos pos1("1", "2");
    //
    //    Queue1<Pos> queue1;
    //    queue1.push(pos1);
    //    queue1.push(std::move(pos1));

    Pos pos2("1", "2");
    Queue2 queue2;

    queue2.push(pos2); // invoke push T&&
    queue2.push(std::move(pos2)); // invoke push T&&

    Pos pos;
    queue2.pop(pos);
}