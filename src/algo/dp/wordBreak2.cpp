//
// Created by wujianchao5 on 2024/12/26.
//

/// #140 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<size_t, bool> memo;
vector<vector<int>> res;

bool equals(const string & s, size_t n, const string & d)
{
    if (s.size() - n < d.size())
        return false;

    for (size_t i = 0; i < d.size(); i++)
    {
        if (s[n + i] != d[i])
            return false;
    }
    return true;
}

void wordBreak2(vector<int> & trace, const string & s, const vector<string> & dict, size_t n)
{
    if (n == s.size())
    {
        res.push_back(trace); /// add a new sentence
        return;
    }
    if (n > s.size())
        return;

    for (int i = 0; i < dict.size(); i++)
    {
        if (equals(s, n, dict[i]))
        {
            trace.emplace_back(i);
            wordBreak2(trace, s, dict, n + dict[i].size());
            trace.erase(trace.end() - 1);
        }
    }
}

int main()
{
//    string s = "catsanddog";
//    vector<string> dict = {"cat", "cats", "and", "sand", "dog"};
    string s = "pineapplepenapple";
    vector<string> dict = {"apple","pen","applepen","pine","pineapple"};

    vector<int> trace;
    wordBreak2(trace, s, dict, 0);

    for (auto & s : res)
    {
        for (auto & w : s)
        {
            cout << dict[w] << " ";
        }
        cout << endl;
    }
}
