//
// Created by wujianchao5 on 2024/12/26.
//

/// 416 non-dp medium

#include <vector>
#include <iostream>
#include <unordered_map>


using namespace std;

struct State
{
    int n;
    int diff;
};

bool canPartition(vector<int> & nums, State state)
{
    if (state.n < 0)
        return state.diff == 0;

    /// left
    if (canPartition(nums, {state.n - 1, state.diff + nums[state.n]}))
        return true;
    /// right
    if (canPartition(nums, {state.n - 1, state.diff - nums[state.n]}))
        return true;
    return false;
}

int main()
{
    vector<int> nums = {1,5,11,5};
    cout << canPartition(nums, {int(nums.size() - 1), 0}) << endl;
}