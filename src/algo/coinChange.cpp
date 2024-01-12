//
// Created by wujianchao5 on 2024/1/12.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>


std::unordered_map<int, int> memo;

int coinChange(const std::vector<int> & coins, int amount)
{
    assert(amount != INT_MAX);

    if (amount == 0)
        return 0;

    if (amount < 0)
        return -1;

    if (memo.contains(amount))
    {
        return memo[amount];
    }

    int min = INT_MAX;
    for (int coin : coins)
    {
        int current = coinChange(coins, amount - coin);
        if (current != -1 && min > current)
            min = current;
    }

    if (min == INT_MAX)
        min = -1;

    memo.emplace(amount, min + 1);
    return min + 1;
}

int main()
{
    std::vector<int> coins = {1, 2, 5, 10, 20};
    std::cout << std::to_string(coinChange(coins, 57)) << std::endl;
}
