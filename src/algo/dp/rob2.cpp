//
// Created by wujianchao5 on 2024/12/30.
//
/// 337 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/// TODO add memo;

int rob2(vector<int> &nums, int n, bool parent_robbed)
{
    if (nums[n] == -1)
        return 0;

    if (2 * n + 1 > nums.size() - 1) /// no child
        return parent_robbed ? 0 : nums[n];

    if (parent_robbed)
    {
        int res = rob2(nums, 2 * n + 1, false); /// left child
        if (nums.size() - 1 >= 2 * n + 2)
            res = res + rob2(nums, 2 * n + 2, false); /// right child
        return res;
    }

    /// rob n
    int has_n;
    {
        has_n = nums[n] + rob2(nums, 2 * n + 1, true); /// left child
        if (nums.size() - 1 >= 2 * n + 2)
            has_n = has_n + rob2(nums, 2 * n + 2, true); /// right child
    }

    /// not rob n
    int no_n;
    {
        no_n = rob2(nums, 2 * n + 1, false); /// left child
        if (nums.size() - 1 >= 2 * n + 2)
            no_n = no_n + rob2(nums, 2 * n + 2, false); /// right child
    }

    return std::max(has_n, no_n);
}

int main() {
    vector<int> nums = {3,2,3,-1,3,-1,1}; /// -1 means node not exist
    int res = rob2(nums, 0, false);
    cout << res << endl;
}
