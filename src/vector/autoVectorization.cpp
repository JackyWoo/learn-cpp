//
// Created by wujianchao5 on 2024/4/10.
//
#include <iostream>
#include <vector>
#include <chrono>


void execute(uint8_t * arr_a, uint8_t * arr_b, uint8_t * arr_c, const size_t len)
{
#pragma clang loop vectorize(disable)
#pragma clang loop interleave(disable)
    for (size_t i = 0; i < len; i++)
        arr_c[i] = arr_a[i] & arr_b[i];
}

void executeByBatch(uint8_t * arr_a, uint8_t * arr_b, uint8_t * arr_c, const size_t len)
{
    for (size_t i = 0; i < len; i++)
        arr_c[i] = arr_a[i] & arr_b[i];
}

void executeByBatch2(uint8_t * arr_a, uint8_t * arr_b, uint8_t * arr_c, const size_t len)
{
    for (size_t i = 0; i < len; i++)
        arr_c[i] = arr_a[i] && arr_b[i];
}

void executeByStep(uint8_t * arr_a, uint8_t * arr_b, uint8_t * arr_c, const size_t len, const size_t step)
{
    size_t i = 0;
    for (; i + step < len; i += step)
        for (size_t j = 0; j < step; ++j)
            arr_c[i+j] = (arr_a[i+j] & arr_b[i+j]);
    for (; i < len; ++i)
        arr_c[i] = (arr_a[i] & arr_b[i]);
}

void executeByStep2(uint8_t * arr_a, uint8_t * arr_b, uint8_t * arr_c, const size_t len, const size_t step)
{
    size_t i = 0;
    for (; i + step < len; i += step)
        for (size_t j = 0; j < step; ++j)
            arr_c[i+j] = (arr_a[i+j] && arr_b[i+j]);
    for (; i < len; ++i)
        arr_c[i] = (arr_a[i] && arr_b[i]);
}


int main()
{
    constexpr size_t len = 10 * 1000 * 1000;
    const size_t step = 16;

    uint8_t * arr_a = new uint8_t[len];
    uint8_t * arr_b = new uint8_t[len];
    uint8_t * arr_c = new uint8_t[len];

    auto t1 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    execute(arr_a, arr_b, arr_c, len);
    auto t2 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    executeByBatch(arr_a, arr_b, arr_c, len);
    auto t3 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    executeByBatch2(arr_a, arr_b, arr_c, len);
    auto t4 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    executeByStep(arr_a, arr_b, arr_c, len, step);
    auto t5 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    executeByStep(arr_a, arr_b, arr_c, len, step);
    auto t6 = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();

    std::cout << "execute: " << (t2 -t1) << std::endl;
    std::cout << "executeByBatch: " << (t3 -t2) << std::endl;
    std::cout << "executeByBatch2: " << (t4 -t3) << std::endl;
    std::cout << "executeByStep: " << (t5 -t4) << std::endl;
    std::cout << "executeByStep2: " << (t6 -t5) << std::endl;

    uint8_t ret{};
    for (size_t i = 0; i < len; i++)
        ret += arr_c[i];

    delete [] arr_a;
    delete [] arr_b;
    delete [] arr_c;

    return ret;
}