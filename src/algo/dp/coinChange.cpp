//
// Created by wujianchao5 on 2024/12/25.
//

/// #322 dp medium

#include <vector>
#include <iostream>
#include <unordered_map>


using namespace std;

std::unordered_map<int, int> memo;

int coinChange(const vector<int> &coins, int amount)
{
    if (amount == 0)
        return 0;

    if (amount < 0)
        return -1;

    if (memo.contains(amount))
        return memo[amount];

    int res = INT_MAX;
    for (int coin : coins)
    {
        int subRes = coinChange(coins, amount - coin);
        if (subRes >= 0)
            res = min(res, subRes + 1);
    }

    memo[amount] = res;
    return (res == INT_MAX) ? -1 : res;
}

int main()
{
    vector<int> coins = {1, 2, 5, 10, 20};
    int mount = 100;
    cout << to_string(coinChange(coins, mount)) << endl;
}
