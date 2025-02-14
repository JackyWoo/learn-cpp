//
// Created by wujianchao5 on 2024/5/27.
//

#include <iostream>
#include <string>
#include <unordered_map>

/** 5. 最长回文子串

 给你一个字符串 s，找到 s 中最长的回文子串。

示例 1：

    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
        示例 2：

    输入：s = "cbbd"
    输出："bb"

    提示：

    1 <= s.length <= 1000
        s 仅由数字和英文字母组成
*/

using namespace std;

unordered_map<int, int> memo;

int longestPalindrome(string s, int e)
{
    if (e < 0)
        return 0;

    if (memo.contains(e))
        return memo[e];

    int max_len;
    auto pre = longestPalindrome(s, e - 1);
    if (e - pre - 1 >= 0 && s[e - pre - 1] == s[e])
        max_len = pre + 2;
    else
        max_len = 1;

    memo.emplace(e, max_len);
    return max_len;
}

int main()
{
    string s = "babad";
    int max = 0;
    int end = 0;
    for (int i = 1; i < s.size(); i++)
    {
        auto len = longestPalindrome(s, i);
        if (max < len)
        {
            end = i;
            max = len;
        }
    }
    cout << s.substr(end + 1 - max, max) << endl;
}