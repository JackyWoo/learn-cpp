//
// Created by wujianchao5 on 2024/12/30.
//
/// #486 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool predictTheWinner(vector<int> &nums, int s, int e, int score_a, int score_b, bool turns_a) {
    if (s > e)
        return score_a >= score_b;

    if (turns_a)
        return predictTheWinner(nums, s + 1, e, score_a + nums[s], score_b, false)
               || predictTheWinner(nums, s, e - 1, score_a + nums[e], score_b, false);
    else
        return predictTheWinner(nums, s + 1, e, score_a, score_b + nums[s], true)
               && predictTheWinner(nums, s, e - 1, score_a, score_b + nums[e], true);
}

int main() {
    vector<int> nums = {1, 5, 2};
    bool res = predictTheWinner(nums, 0, nums.size() - 1, 0, 0, true);
    cout << res << endl;
}
