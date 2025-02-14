//
// Created by wujianchao5 on 2024/12/25.
//

/// #354 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> memo;
int lengthOfLIS(vector<int> & nums, int end)
{
    if (end == 0)
        return 1;

    if (memo.count(end))
        return memo[end];

    int res = 0;
    for (int i = end - 1; i >= 0; i--)
    {
        if (nums[i] < nums[end])
            res = std::max(res, lengthOfLIS(nums, i) + 1);
    }

    memo[end] = res;
    return res;
}

int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    int res = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        res = std::max(res, lengthOfLIS(nums, i));
    }
    cout << res << endl;
}
