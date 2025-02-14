//
// Created by wujianchao5 on 2024/12/30.
//
/// 121 dp easy

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> memo;

int maxProfit(vector<int> & prices, int n) {
    if (n == 0)
        return prices[n];
    if (memo.count(n))
        return memo[n];
    int res = prices[n];
    res = std::min(res,  maxProfit(prices, n - 1));
    memo[n] = res;
    return res;
}

int main() {
    vector<int> prices = {7,1,5,3,6,4};
    int res = INT_MIN;
    for (int i = 1; i < prices.size(); i++) {
        res = std::max(res, prices[i] - maxProfit(prices, i - 1));
    }
    cout << res << endl;
}
