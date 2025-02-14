//
// Created by wujianchao5 on 2024/12/26.
//

/// #139 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<size_t, bool> memo;

bool equals(const string & s, size_t n, const string & d)
{
    for (size_t i = 0; i < d.size(); i++)
    {
        if (s[n + i] != d[i])
            return false;
    }
    return true;
}

bool wordBreak(const string & s, const vector<string> & dict, size_t n)
{
    if (n == s.size())
        return true;
    if (n > s.size())
        return false;

    if (memo.count(n))
        return memo[n];

    for (size_t i = 0; i < dict.size(); i++)
    {
        if (dict[i].size() <= s.size() - n && equals(s, n, dict[i]))
            if (wordBreak(s, dict, n + dict[i].size()))
                return true;
    }
    memo[n] = false;
    return false;
}

int main()
{
    string s = "applepenapple";
    vector<string> dict = {"apple", "pen"};

    cout << wordBreak(s, dict, 0) << endl;
}
