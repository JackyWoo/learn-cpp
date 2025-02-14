//
// Created by wujianchao5 on 2024/12/26.
//

/// #746 dp easy

#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> memo;

int minCostClimbingStairs(const vector<int> & cost, int next)
{
    if (next == cost.size())
        return 0;

    if (next > cost.size())
        return -1;

    if (memo.contains(next))
        return memo[next];

    int res = INT_MAX;
    int c1 = minCostClimbingStairs(cost, next + 1) + cost[next];
    int c2 = minCostClimbingStairs(cost, next + 2) + cost[next];
    if (c1 != -1)
        res = min(res, c1);
    if (c2 != -1)
        res = min(res, c2);

    memo[next] = res;
    return res;
}

int main()
{
    vector<int> cost = {10,15,20};
    int c1 = minCostClimbingStairs(cost, 0);
    int c2 = minCostClimbingStairs(cost, 1);
    cout << min(c1, c2) << endl;
}
