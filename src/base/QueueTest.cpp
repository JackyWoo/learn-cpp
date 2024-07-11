//
// Created by wujianchao5 on 2024/6/12.
//
#include <iostream>
#include <thread>

#include "ThreadSafeQueue.h"
#include "ConcurrentBoundedQueue.h"
#include "LockFreeConcurrentBoundedQueue.h"
#include "MPMCQueue.h"
#include "ConcurrentBoundedSingleThreadQueue.h"
#include "../../contrib/concurrentqueue/concurrentqueue.h"
#include "../../contrib/concurrentqueue/blockingconcurrentqueue.h"

inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

template <class T>
void testTimedPushAndPop(T & queue, size_t thread_count)
{
    auto start_time = getCurrentTimestamp();

    int count = 1000000;
    size_t timeout_ms = 100;

    std::atomic_long empty_event_count{};
    std::atomic_long full_event_count{};

    std::vector<std::thread> produce_threads;
    std::vector<std::thread> consume_threads;

    // Producer thread
    auto produce_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            while (!queue.tryPush(i, timeout_ms))
            {
                // Queue is full, retry
                full_event_count++;
            }
        }
    };

    // Consumer thread
    auto consume_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            int item;
            while (!queue.tryPop(item, timeout_ms))
            {
                // Queue is empty, retry
                empty_event_count++;
            }
        }
    };

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads.push_back(std::thread(produce_thread));
        consume_threads.push_back(std::thread(consume_thread));
    }

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads[i].join();
        consume_threads[i].join();
    }

    std::cout << "Test timed push and pop. thread count: " << std::to_string(thread_count) << ", Time cost: " << std::to_string(getCurrentTimestamp() - start_time)
              << " us" << ", empty_event_count: " << std::to_string(empty_event_count)
              << ", full_event_count: " << std::to_string(full_event_count) << std::endl;
}

template <class T>
void testTimedPushAndPopV2(T & queue, size_t thread_count)
{
    auto start_time = getCurrentTimestamp();

    int count = 1000000;
    size_t timeout_ms = 100;

    std::atomic_long empty_event_count{};
    std::atomic_long full_event_count{};

    std::vector<std::thread> produce_threads;
    std::vector<std::thread> consume_threads;

    // Producer thread
    auto produce_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            while (!queue.try_enqueue(i))
            {
                // Queue is full, retry
                full_event_count++;
            }
        }
    };

    // Consumer thread
    auto consume_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            int item;
            while (!queue.wait_dequeue_timed(item, timeout_ms))
            {
                // Queue is empty, retry
                empty_event_count++;
            }
        }
    };

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads.push_back(std::thread(produce_thread));
        consume_threads.push_back(std::thread(consume_thread));
    }

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads[i].join();
        consume_threads[i].join();
    }

    std::cout << "Test timed push and pop. thread count: " << std::to_string(thread_count) << ", Time cost: " << std::to_string(getCurrentTimestamp() - start_time)
              << " us" << ", empty_event_count: " << std::to_string(empty_event_count)
              << ", full_event_count: " << std::to_string(full_event_count) << std::endl;
}



template <class T>
void testPushAndPop(T & queue, size_t thread_count)
{
    auto start_time = getCurrentTimestamp();

    int count = 1000000;
    size_t timeout_ms = 100;

    std::atomic_long empty_event_count{};
    std::atomic_long full_event_count{};

    std::vector<std::thread> produce_threads;
    std::vector<std::thread> consume_threads;

    // Producer thread
    auto produce_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            queue.push(i);
        }
    };

    // Consumer thread
    auto consume_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            int item;
            queue.pop(item);
        }
    };

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads.push_back(std::thread(produce_thread));
        consume_threads.push_back(std::thread(consume_thread));
    }

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads[i].join();
        consume_threads[i].join();
    }

    std::cout << "Test blocked push and pop. thread count: " << std::to_string(thread_count) << ", Time cost: " << std::to_string(getCurrentTimestamp() - start_time)
              << " us" << std::endl;
}

template <class T>
void testPushAndPopV2(T & queue, size_t thread_count)
{
    auto start_time = getCurrentTimestamp();

    int count = 1000000;
    size_t timeout_ms = 100;

    std::atomic_long empty_event_count{};
    std::atomic_long full_event_count{};

    std::vector<std::thread> produce_threads;
    std::vector<std::thread> consume_threads;

    // Producer thread
    auto produce_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            queue.enqueue(i);
        }
    };

    // Consumer thread
    auto consume_thread = [&]()
    {
        for (int i = 0; i < count; ++i)
        {
            int item;
            queue.try_dequeue(item);
        }
    };

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads.push_back(std::thread(produce_thread));
        consume_threads.push_back(std::thread(consume_thread));
    }

    for (int i = 0; i < thread_count; i++)
    {
        produce_threads[i].join();
        consume_threads[i].join();
    }

    std::cout << "Test blocked push and pop. thread count: " << std::to_string(thread_count) << ", Time cost: " << std::to_string(getCurrentTimestamp() - start_time)
              << " us" << std::endl;
}


int main()
{
//    ConcurrentBoundedQueue<int> queue(100);
//    LockFreeConcurrentBoundedQueue<int> bound_queue(100);

//    testTimedPushAndPop(queue, 1);
//    testTimedPushAndPop(bound_queue, 1);
//
//    testTimedPushAndPop(queue, 5);
//    testTimedPushAndPop(bound_queue, 5);

//    testTimedPushAndPop(queue, 10);
//    testTimedPushAndPop(bound_queue, 10);


    ConcurrentBoundedQueue<int> queue(10000);
    ThreadSafeQueue<int> thread_safe_queue;
    LockFreeConcurrentBoundedQueue<int> bound_queue(10000);
    ConcurrentBoundedSingleThreadQueue<int> single_thread_queue(10000);
    moodycamel::BlockingConcurrentQueue<int> mood_queue(10000);
    MPMCQueue<int> mpmc_queue(10000);

//    int item;
//    mpmc_queue.pop(item);
//    std::this_thread::sleep_for(std::chrono::seconds(1000));
//
    testPushAndPop(queue, 1);
    testPushAndPop(thread_safe_queue, 1);
    testPushAndPop(single_thread_queue, 1);
    testPushAndPop(mpmc_queue, 1);
    testPushAndPopV2(mood_queue, 1);
//
    testTimedPushAndPop(queue, 1);
    testTimedPushAndPop(thread_safe_queue, 1);
    testTimedPushAndPop(single_thread_queue, 1);
    testTimedPushAndPopV2(mood_queue, 1);

//    test(queue, 5);
//    test(bound_queue, 5);
//
//    test(queue, 10);
//    test(bound_queue, 10);

//    testPushAndPopV2(mood_queue, 1);
//    testPushAndPopV2(mood_queue, 5);
//    testPushAndPopV2(mood_queue, 10);

}
