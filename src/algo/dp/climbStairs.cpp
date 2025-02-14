//
// Created by wujianchao5 on 2024/12/26.
//

/// #70 dp easy

#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> memo;

int climbStairs(int n, int next)
{
    if (next == n + 1)
        return 1;

    if (next > n + 1)
        return 0;

    if (memo.contains(next))
        return memo[next];
    int sum = 0;
    sum += climbStairs(n, next + 1);
    sum += climbStairs(n, next + 2);

    memo[next] = sum;
    return sum;
}

int main()
{
    int n = 3;
    cout << climbStairs(n, 1) << endl;
}
