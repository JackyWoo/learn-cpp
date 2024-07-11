#pragma once

#include <atomic>
#include <chrono>
#include <vector>


/**
 * A lock free concurrent bounded queue which behaves better than ConcurrentBoundedQueue when there are less consumer and producer threads.
 *
 * LockFreeConcurrentBoundedQueue:
 *  Thread count: 1, Time cost: 403083 us, empty_event_count: 0, full_event_count: 0
 *  Thread count: 5, Time cost: 6898097 us, empty_event_count: 0, full_event_count: 0
 *  Thread count: 10, Time cost: 13480722 us, empty_event_count: 0, full_event_count: 0
 *
 * ConcurrentBoundedQueue:
 *  Thread count: 1, Time cost: 164419 us, empty_event_count: 0, full_event_count: 0
 *  Thread count: 5, Time cost: 4689485 us, empty_event_count: 0, full_event_count: 0
 *  Thread count: 10, Time cost: 17639060 us, empty_event_count: 0, full_event_count: 0
 */
template <typename T>
class LockFreeConcurrentBoundedQueue
{
public:
    explicit LockFreeConcurrentBoundedQueue(size_t capacity = 10000);

    void push(const T & item);
    void pop(T & item);

    bool tryPush(const T & item, uint64_t timeout_ms);
    bool tryPop(T & item, uint64_t timeout_ms);

    /// not exactly accurate
    size_t size() const;
    /// not exactly accurate
    bool empty() const;

private:
    std::vector<T> buffer;
    std::atomic<size_t> head;
    std::atomic<size_t> tail;
    std::atomic_flag head_lock = ATOMIC_FLAG_INIT;
    std::atomic_flag tail_lock = ATOMIC_FLAG_INIT;
    size_t capacity;
};

template <typename T>
LockFreeConcurrentBoundedQueue<T>::LockFreeConcurrentBoundedQueue(size_t capacity_)
    : buffer(capacity_), head(0), tail(0), capacity(capacity_)
{
}

template <typename T>
void LockFreeConcurrentBoundedQueue<T>::push(const T & item)
{
    // Spin until we acquire the tail lock
    while (tail_lock.test_and_set())
        ;

    size_t current_tail = tail.load();
    size_t next_tail = (current_tail + 1) % capacity;

    // Queue is full
    while (next_tail == head.load());

    buffer[current_tail] = item;
    tail.store(next_tail);

    // Release the tail lock
    tail_lock.clear();
}

template <typename T>
bool LockFreeConcurrentBoundedQueue<T>::tryPush(const T & item, uint64_t timeout_ms)
{
    using namespace std::chrono;

    auto start_time = steady_clock::now();
    milliseconds timeout(timeout_ms);

    // Spin until we acquire the tail lock or timed out
    while (tail_lock.test_and_set())
    {
        if (steady_clock::now() - start_time > timeout)
            return false;
    }

    size_t current_tail = tail.load();
    size_t next_tail = (current_tail + 1) % capacity;

    while (next_tail == head.load())
    {
        // Queue is full
        if (steady_clock::now() - start_time > timeout)
        {
            tail_lock.clear();
            return false;
        }
    }

    buffer[current_tail] = item;
    tail.store(next_tail);

    // Release the tail lock
    tail_lock.clear();
    return true;
}

template <typename T>
void LockFreeConcurrentBoundedQueue<T>::pop(T & item)
{
    // Spin until we acquire the head lock
    while (head_lock.test_and_set())
        ;

    size_t current_head = head.load();

    // Queue is empty
    while (current_head == tail.load());

    item = buffer[current_head];
    head.store((current_head + 1) % capacity);

    // Release the head lock
    head_lock.clear();
}


template <typename T>
bool LockFreeConcurrentBoundedQueue<T>::tryPop(T & item, uint64_t timeout_ms)
{
    using namespace std::chrono;

    auto start_time = steady_clock::now();
    milliseconds timeout(timeout_ms);

    // Spin until we acquire the head lock or timed out
    while (head_lock.test_and_set())
    {
        if (steady_clock::now() - start_time > timeout)
            return false;
    }

    head_lock.wait(true);
    head_lock.notify_one();

    size_t current_head = head.load();

    while (current_head == tail.load())
    {
        // Queue is empty
        if (steady_clock::now() - start_time > timeout)
        {
            head_lock.clear();
            return false;
        }
    }

    item = buffer[current_head];
    head.store((current_head + 1) % capacity);

    // Release the head lock
    head_lock.clear();
    return true;
}

template <typename T>
size_t LockFreeConcurrentBoundedQueue<T>::size() const
{
    size_t current_head = head.load();
    size_t current_tail = tail.load();

    if (current_tail >= current_head)
    {
        return current_tail - current_head;
    }
    else
    {
        return capacity - current_head + current_tail;
    }
}

template <typename T>
bool LockFreeConcurrentBoundedQueue<T>::empty() const
{
    size_t current_head = head.load();
    size_t current_tail = tail.load();

    return current_tail == current_head;
}

