//
// Created by wujianchao5 on 2020/12/15.
//

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "BlockingQueue.h"

//typedef BlockingQueue<int> Queue;
void printThreadId(const char * threadName);

void produce(BlockingQueue<int> & queue);
void consume(BlockingQueue<int> & queue);

void test();
void simpleTest();

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

int main()
{
    //    test();
    simpleTest();
}

void test()
{
    BlockingQueue<int> queue(2);

    printThreadId("main");

    std::thread t1(produce, std::ref(queue));
    //    t1.detach();
    std::thread t2(consume, std::ref(queue));
    //    t2.detach();
    std::thread t3(consume, std::ref(queue));
    //    t3.detach();

    std::this_thread::sleep_for(std::chrono::seconds(100));
}

void simpleTest()
{
    BlockingQueue<Pos> queue(2);
    Pos e1("1", "2");
    queue.push(e1);
//    queue.push({"1", "2"});
    std::cout << "after push " << e1 << std::endl;
}

void printThreadId(const char * threadName)
{
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << threadName << ":" << std::hex << "0x" << threadId << std::oct << std::endl;
}

void produce(BlockingQueue<int> & queue)
{
    printThreadId("produce");
    const int num = 100;
    for (int i = 0; i < num; ++i)
    {
        std::cout << "push :" + std::to_string(i) << std::endl;
        queue.push(i);
    }
}

void consume(BlockingQueue<int> & queue)
{
    printThreadId("consume");
    std::thread::id threadId = std::this_thread::get_id();
    while (true)
    {
        int tmp = queue.take();
        std::cout << "take :" + std::to_string(tmp) << std::endl;
    }
}
