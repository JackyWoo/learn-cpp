#pragma once

#include <atomic>
#include <chrono>
#include <vector>

template <typename T>
class LockFreeConcurrentUnboundedQueue
{
public:
    LockFreeConcurrentUnboundedQueue();
    ~LockFreeConcurrentUnboundedQueue();

    void push(const T & item);
    void pop(T & item);
    bool tryPop(T & item);

    size_t size() const;
    bool empty() const;

private:
    struct Node
    {
        T data;
        std::atomic<Node *> next;

        Node() : next(nullptr) { }
        explicit Node(const T & value) : data(value), next(nullptr) { }
        explicit Node(T && value) : data(std::move(value)), next(nullptr) { }
    };

    std::atomic<Node *> head;
    std::atomic<Node *> tail;

    std::atomic_flag push_lock = ATOMIC_FLAG_INIT;

    std::atomic<size_t> count;
};

template <typename T>
LockFreeConcurrentUnboundedQueue<T>::LockFreeConcurrentUnboundedQueue() : count(0)
{
    Node * dummy = new Node();
    head.store(dummy);
    tail.store(dummy);
}

template <typename T>
LockFreeConcurrentUnboundedQueue<T>::~LockFreeConcurrentUnboundedQueue()
{
    while (head.load() != nullptr)
    {
        Node * node = head.load();
        head.store(node->next.load());
        delete node;
    }
}

template <typename T>
void LockFreeConcurrentUnboundedQueue<T>::push(const T & item)
{
    Node * new_node = new Node(item);

    Node * old_tail = tail.load();
    old_tail->next.store(new_node);
    tail.store(new_node);

    push_lock.test_and_set();
    push_lock.notify_one(); // Notify one pop thread which is waiting element

    count.fetch_add(1);
}

template <typename T>
void LockFreeConcurrentUnboundedQueue<T>::pop(T & item)
{

    Node * old_head = head.load();
    Node * next = old_head->next.load();

    while (next == nullptr)
    {
        push_lock.wait(false);
        old_head = head.load();
        next = old_head->next.load();
    }

    item = std::move(next->data);
    head.store(next);

    delete old_head;
    count.fetch_sub(1);

    if (count.load() == 0)
        push_lock.clear();
}

template <typename T>
bool LockFreeConcurrentUnboundedQueue<T>::tryPop(T & item)
{
    Node * old_head = head.load();
    Node * next = old_head->next.load();

    if (next == nullptr)
    {
        return false; // Queue is empty
    }

    item = std::move(next->data);
    head.store(next);

    delete old_head;
    count.fetch_sub(1);
    return true;
}

template <typename T>
size_t LockFreeConcurrentUnboundedQueue<T>::size() const
{
    return count.load();
}

template <typename T>
bool LockFreeConcurrentUnboundedQueue<T>::empty() const
{
    return count.load() == 0;
}
