//
// Created by wujianchao5 on 2020/12/25.
//

#include <iostream>
#include <memory>
#include <queue>
#include <type_traits>

struct Foo
{
    Foo()
    {
        std::cout << "invoke Foo constructor\n";
    }

    std::string a;
    std::string b;

    Foo(const std::string & a, const std::string & b) : a(a), b(b) { }

    // copy constructor
    Foo(const Foo & other) : a(other.a), b(other.b)
    {
        std::cout << "invoke Foo copy constructor\n";
    }

    // move constructor
    Foo(Foo && other) : a(std::move(other.a)), b(std::move(other.b))
    {
        std::cout << "invoke Foo move constructor\n";
    }

    // copy = operator
    Foo & operator=(const Foo & other)
    {
        std::cout << "invoke Foo copy = operator\n";
        if (this != &other)
        {
            a = other.a;
            b = other.b;
        }
        return *this;
    }

    // move = operator
    Foo & operator=(Foo && other) noexcept
    {
        std::cout << "invoke Foo move = operator\n";
        if (this != &other)
        {
            a = std::move(other.a);
            b = std::move(other.b);
        }
        return *this;
    }

    friend std::ostream & operator<<(std::ostream & os, const Foo & foo)
    {
        os << "a: " << foo.a << " b: " << foo.b;
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

    // (1) value is not a universal reference, method just receives a rvalue
    void push(T && value)
    {
        std::cout << "Queue1 push T&&\n";
        // (2) here value is a lvalue, we need cast it to rvalue by std::move.
        queue.push(std::move(value));
    }

    void push(const T & value)
    {
        std::cout << "Queue1 const push T&\n";
        queue.push(value);
    }

    void pop(Foo & foo)
    {
        // (5) value of queue.front() is a lvalue, will use copy = operator
        //foo = queue.front();
        // (6) move method translate value of queue.front() to a rvalue,
        //     and will use move = operator
        foo = std::move(queue.front());
        queue.pop();
    }
};


class Queue2
{
private:
    std::queue<Foo> queue;

public:
    Queue2() = default;

    // (3) value is a universal reference who can match both rvalue and lvalue
    template <typename T>
    void push(T && value)
    {
        std::cout << "Queue2 push T&&\n";
        // (4) here value is a lvalue, we need cast it to what it originally was by std::forward,
        //     and this is called perfect forward.
        queue.push(std::forward<T>(value));
    }

    void pop(Foo & foo)
    {
        // use copy = operator
        foo = queue.front();
        // move method translate value of queue.front() to a rvalue
        // use move = operator
        // foo = std::move(queue.front());
        queue.pop();
    }
};


// copy elision case
Foo f()
{
    std::cout << "invoke f" << std::endl;
    return Foo();  // only one call to default constructor of Foo
}


int main()
{
//    Foo foo1("1", "2");
//
//    Queue1<Foo> queue1;
////    queue1.push(foo1);            // invoke push const T&
//    queue1.push(std::move(foo1));   // invoke push T&&
//    Foo foo;
//    queue1.pop(foo);

    //    Foo foo2("1", "2");
    //    Queue2 queue2;
    //
    //    queue2.push(foo2);              // invoke push T&&
    //    queue2.push(std::move(foo2));   // invoke push T&&
    //
    //    Foo foo;
    //    queue2.pop(foo);

    Foo foo = f();

    // temporary materialization
    const Foo & tm = {};
}