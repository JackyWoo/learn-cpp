//
// Created by wujianchao5 on 2024/12/30.
//
/// 198 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/// TODO add memo;

int rob2(vector<int> &nums, int n, bool parent_robbed)
{
    if (n == 0)
        return parent_robbed ? 0 : nums[0];

    if (parent_robbed)
        return rob2(nums, n - 1, false);

    return std::max(nums[n] + rob2(nums, n - 1, true), rob2(nums, n - 1, false));
}

int main() {
    vector<int> nums = {1,2,3,1};
    int res = rob2(nums, nums.size() - 1, false);
    cout << res << endl;
}
