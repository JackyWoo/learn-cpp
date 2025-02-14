//
// Created by wujianchao5 on 2024/12/25.
//

/// 494 dp medium

#include <vector>
#include <iostream>
#include <unordered_map>


using namespace std;

std::unordered_map<int, int> memo;

int findTargetSumWays(const vector<int> & nums, int target, int n)
{
    if (n < 0)
        return target == 0 ? 1 : 0;

    int res = 0;
    res += findTargetSumWays(nums, target - nums[n], n-1); /// -
    res += findTargetSumWays(nums, target + nums[n], n-1); /// +
    return res;
}

int main()
{
    vector<int> nums = {1,1,1,1,1};
    int target = 3;
    cout << findTargetSumWays(nums, target, nums.size() - 1) << endl;
}
