//
// Created by wujianchao5 on 2024/1/16.
//

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

/// Test how to trigger auto vectorization

///Stop watch which can be used to measure the time of a code block
struct StopWatch
{
    StopWatch()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    uint64_t elapsed() const
    {
        const auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        return diff.count();
    }

    void reset()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

};

void loopWithUnkownTripCount(int * a, int * b, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        a[i] = b[i] * 2;
    }
}

void runtimeCheckPointer(int * a, int * b, int len, int x)
{
    for (int i = 0; i < len; i++)
    {
        a[i] = b[i] + x;
    }
}

void reduction(int * a, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += a[i];
    }
    std::cout << sum << std::endl;
}

void induntions(int * a, int len)
{
    for (int i = 0; i < len; ++i)
        a[i] = i;
}

void ifConversion(int * a, int * b, int len)
{
    unsigned sum = 0;
    for (int i = 0; i < len; ++i)
        if (a[i] > b[i])
            sum += a[i] + 5;

    std::cout << sum << std::endl;
}

void pointerInductionVariable(int * a, int len)
{
    int sum;
    sum = std::accumulate(a, a + len, 0);
    std::cout << sum << std::endl;
}

void reverseInterator(int * a, int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        a[i] = i;
    }
}

void scatterGatehr(int * a, int * b, int len)
{
    for (int i = 0; i < len; i++)
    {
        a[i] = b[i * 4];
    }
}

void mixedTypes(int * a, char * b, int len)
{
    for (int i = 0; i < len; i++)
    {
        a[i] = b[i] * 2;
    }
}

void noStdVector()
{
    std::vector<int> v_a;
    std::vector<int> v_b;
    for (int i = 0; i < 1024; i++)
    {
        v_a.push_back(i);
        v_b.push_back(i);
    }

    for (auto & i : v_a)
    {
        i = i * 2;
    }

    for (auto it = v_a.begin(); it != v_a.end(); it++)
    {
        *it = *it * 2;
    }
}

void noIf(int * a, int * b, int len)
{
    for (int i = 0; i < len; ++i)
        if (a[i] > 1)
            a[i] = b[i];
}

void noSwitch(int * arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        switch (arr[i])
        {
            case 0:
                arr[i] = i * 2;
            break;
            case 1:
                arr[i] = i;
            break;
            default:
                arr[i] = 0;
        }
    }
}

int main()
{
    constexpr int N = 1024;

    int a[N];
    int b[N];
    char c[N];
#pragma clang loop vectorize(enable)
    for (int i = 0; i < N; i++)
    {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    /// Suspect to be auto vectorized
    loopWithUnkownTripCount(a, b, 10, N);

    /// reduction
    reduction(a, N);


    /// The optimization is not only happening in compile time, but also in runtime

    /// vectorization width: 2, interleaved count: 1
    runtimeCheckPointer(a + 102, a + 100, 200, 1);
    /// vectorization width: 4, interleaved count: 2
    runtimeCheckPointer(a, a + 100, 200, 1);
    /// vectorization width: 4, interleaved count: 2
    runtimeCheckPointer(a, b, 200, 1);

    /// induction
    induntions(a, N);

    /// Flatten the IF statement in the code and generate a single stream of instructions
    /// But how ?
    ifConversion(a, b, N);

    pointerInductionVariable(a, N);
    reverseInterator(a, N);
    scatterGatehr(a, b, 100);
    mixedTypes(a, c, N);

    noStdVector();
    noIf(a, b, N);

    noSwitch(a, N);
}