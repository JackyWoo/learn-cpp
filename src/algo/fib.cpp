//
// Created by wujianchao5 on 2024/1/12.
//

#include <iostream>
#include <unordered_map>


std::unordered_map<int, int> memo;

int fib(int n)
{
    if (n == 1 || n == 2)
        return 1;
    if (memo.contains(n))
        return memo[n];
    int r = fib(n - 1) + fib(n - 2);
    memo.emplace(n, r);
    return r;
}

int main()
{
    std::cout << std::to_string(fib(5)) << std::endl;
}
