//
// Created by wujianchao5 on 2024/12/27.
//

/// dp easy

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int knapsack(const vector<int> & wt, const vector<int> & val, int w, int n)
{
    if (n < 0)
        return 0;

    int res = INT_MIN;

    /// choose n
    if (w - wt[n] >= 0)
        res = std::max(res, knapsack(wt, val, w - wt[n], n - 1) + val[n]);

    /// not choose n
    res = std::max(res, knapsack(wt, val, w, n - 1));

    return res;
}

int main()
{
    int w = 4;
    vector<int> wt = {2, 1, 3};
    vector<int> val = {4, 2, 3};

    cout << knapsack(wt, val, w, wt.size() - 1) << endl;
}
