//
// Created by wujianchao5 on 2024/12/30.
//
/// 188 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/// TODO add memo

// unordered_map<int, int> memo_max_profit2;
// unordered_map<int, int> memo_max_profit;

int dp_max_profit(vector<int> & prices, int src, int n) {
    if (n == src)
        return prices[n];
    int res = prices[n];
    res = std::min(res,  dp_max_profit(prices, src, n - 1));
    return res;
}

int maxProfit(vector<int> & prices, int src, int dst) {
    int res = INT_MIN;
    for (int i = src; i < dst; i++) {
        res = std::max(res, prices[i] - dp_max_profit(prices, src, i - 1));
    }
    return res;
}

int maxProfit2(vector<int> & prices, int n, int k) {
    if (k == 0)
        return 0;
    if (n < 2)
        return 0;
    if (n == 2)
        return prices[1] - prices[0] > 0 ? prices[1] - prices[0] : 0;
    
    int res = 0;
    for (int i=n-2; i>0; i--)
    {
        res = std::max(res, maxProfit2(prices, i, k - 1) + maxProfit(prices, i, n));
    }
    return res;
}

int main() {
    vector<int> prices = {2,4,1};
    int k = 2;
    int res = maxProfit2(prices, prices.size() - 1, k);
    cout << res << endl;
}
