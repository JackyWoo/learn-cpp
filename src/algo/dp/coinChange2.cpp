//
// Created by wujianchao5 on 2024/12/25.
//

/// #322 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

std::unordered_map<int, int> memo;

int coinChange2(const vector<int> & coins, int amount)
{
    if (amount < 0)
        return 0;

    if (amount == 0)
        return 1;

    if (memo.count(amount))
        return memo[amount];
    int res = 0;
    for (auto & coin : coins)
    {
        res += coinChange2(coins, amount - coin);
    }
    memo[amount] = res;
    return res;
}

int main()
{
    vector<int> coins = {
        1,
        2,
        5,
    };
    int amount = 5;
    cout << to_string(coinChange2(coins, amount)) << endl;
}
