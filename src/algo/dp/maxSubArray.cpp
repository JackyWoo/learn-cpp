//
// Created by wujianchao5 on 2024/12/26.
//

/// 53 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> memo;

int maxSubArray(vector<int> & nums, int end)
{
    if (end < 0)
        return 0;

    if (memo.count(end))
        return memo[end];

    int res = nums[end];
    int sub_problem = maxSubArray(nums, end - 1);
    if (sub_problem > 0)
        res += sub_problem;

    memo[end] = res;
    return res;
}

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int res = INT_MIN;
    for (int i = 0; i < nums.size(); i++)
    {
        res = std::max(res, maxSubArray(nums, i));
    }

    cout << res << endl;
}
