//
// Created by wujianchao5 on 2024/12/26.
//
/// #1143 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct PairHash
{
    auto operator()(const std::pair<int, int> & pair) const -> size_t { return size_t(pair.first + pair.second); }
};

unordered_map<std::pair<int, int>, int, PairHash> memo;

int longestCommonSubsequence(string & s1, string & s2, int i1, int i2)
{
    if (i1 == s1.size() || i2 == s2.size())
        return 0;

    if (memo.count({i1, i2}))
        return memo[{i1, i2}];

    int res = 0;
    if (s1[i1] == s2[i2])
    {
        res = longestCommonSubsequence(s1, s2, i1+1, i2 + 1) + 1;
    }
    else
    {
        res = std::max(res, longestCommonSubsequence(s1, s2, i1+1, i2));
        res = std::max(res, longestCommonSubsequence(s1, s2, i1, i2+1));
    }

    memo[{i1, i2}] = res;
    return res;
}

int main()
{
    string s1 = "abcde";
    string s2 = "ace";

    cout << longestCommonSubsequence(s1, s2, 0, 0) << endl;
}
