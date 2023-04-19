//
// Created by wujianchao5 on 2020/12/15.
//

#ifndef LEARN_CPP_BLOCKINGQUEUE_H
#define LEARN_CPP_BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <climits>
#include <iostream>
#include <condition_variable>

/**
 * bounded blocking queue implemented by mutex
 * @tparam T
 */
template<typename T>
class BlockingQueue
{

public:
    explicit BlockingQueue(int maxSize = INT_MAX);

    T take();

    void push(T&& e);
    void push(const T& e);

    bool isEmpty();

private:
    int maxSize{};
    std::queue<T> queue;

    std::mutex mutex;

    std::condition_variable canTake;
    std::condition_variable canPush;

    bool isFull();
    template <typename ... Args> void pushImpl(Args &&...args);
};


template <typename T>
BlockingQueue<T>::BlockingQueue(int maxSize)
{
    this->maxSize = maxSize;
}

template <typename T> template <typename... Args>
void BlockingQueue<T>::pushImpl(Args &&... args)
{
    std::cout << "pushImpl" << std::endl;
//    std::cout << &args << std::endl;
    std::unique_lock<std::mutex> lock(mutex);

    while(queue.size() == maxSize)
    {
        canPush.wait(lock);
    }

    // emplace
    queue.emplace(std::forward<Args>(args)...);
    // notify waiters
    canTake.notify_all();
}

template <typename T>
void BlockingQueue<T>::push(const T& e)
{
    std::cout << "push const &" << std::endl;
    std::cout << &e << std::endl;
    pushImpl(e);
}

template <typename T>
void BlockingQueue<T>::push(T&& e)
{
    std::cout << "push &&" << std::endl;
    std::cout << &e << std::endl;
    pushImpl(std::forward<T>(e));
}

template <typename T>
T BlockingQueue<T>::take()
{
    std::unique_lock<std::mutex> lock(mutex);

    while (queue.empty())
    {
        canTake.wait(lock);
    }

    // take
    T e = std::move(queue.front());
    queue.pop();

    // notify waiters
    canPush.notify_all();
    return std::move(e);
}

template<typename T>
bool BlockingQueue<T>::isEmpty()
{
    std::unique_lock<std::mutex> lock(mutex);
    return queue.size() == 0;
}

template<typename T>
bool BlockingQueue<T>::isFull()
{
    std::unique_lock<std::mutex> lock(mutex);
    return queue.size() == maxSize;
}

#endif //LEARN_CPP_BLOCKINGQUEUE_H
