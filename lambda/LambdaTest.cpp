//
// Created by wujianchao5 on 2020/12/18.
//

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

struct Bike
{
    int distance;
};

using namespace std;
using String = std::string;

class People
{
public:
    template <typename T>
    using Ptr = std::shared_ptr<T>;

    String name;
    int age;

    std::atomic_bool stop = false;

    using arrive_listener = std::function<void(const String & destination)>;

    struct GoTask
    {
        GoTask(Ptr<String> & from, arrive_listener & listener) : from(from), listener(listener) { }
        int32_t mark = 1;
        Ptr<String> from;
        /// Must not be reference for local function variable will be destroyed when function completed
        arrive_listener listener;
    };

    Ptr<GoTask> go_task;
    std::thread go_thread;

    People(String name, int age) : name(std::move(name)), age(age)
    {
        go_thread = std::thread([this] { goThread(); });
    }

    ~People()
    {
        cout<<"destroy People"<<endl;
    }

    void shutdown()
    {
        stop = true;
        go_thread.join();
    }

    void onArrive(const Ptr<Bike> & bike, const String & destination)
    {
        cout << "dest " << endl;
        cout << "dest " << destination << endl;
        bike->distance = 100;
        cout << "onArrived " << destination << ", bike distance is " << bike->distance << endl;
    }

    void go(Ptr<String> & from, arrive_listener & listener) { go_task = std::make_shared<GoTask>(from, listener); }

    void goThread()
    {
        while (!stop)
        {
            if (go_task)
            {
                cout << "go ... from " << *go_task->from << endl;
                go_task->listener("dest");
                go_task = nullptr;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void trip()
    {
        std::cout << "name:" << name << ", age:" << age << std::endl;
        Ptr<Bike> bike = std::make_shared<Bike>();
        bike->distance = 100;
        Ptr<String> from = std::make_shared<String>("bj");
//        arrive_listener listener = [this, bike](auto && dest) { onArrive(bike, std::forward<decltype(dest)>(dest)); };
        /// bind 和 lambda函数如果定义到本地，在异步线程下应该采用值传递的方式。
        arrive_listener listener = [this, bike](const String & dest) { onArrive(bike, std::forward<const String &>(dest)); };
        /// std::bind 预先绑定的参数采用值传递的方式，lambda可以自定义是值传递还是引用传递
//        arrive_listener listener = std::bind(&People::onArrive, this, bike, std::placeholders::_1);
        go(from, listener);
    }
};

int main()
{
    //    test();
    People people("lili", 20);
    people.trip();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    people.shutdown();
}
