//
// Created by wujianchao5 on 2024/12/26.
//
/// #115 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct State
{
    size_t a_idx;
    size_t b_idx;

    bool operator==(const State & other) const { return a_idx == other.a_idx && b_idx == other.b_idx; }
};

namespace std
{
template <>
struct hash<State>
{
    size_t operator()(const State & state) const { return state.a_idx + state.b_idx; }
};
}

unordered_map<State, int> memo;

int numDistinct(const string & a, const string & b, State state)
{
    if (state.b_idx == b.size())
        return 1;

    if (state.a_idx == a.size() && state.b_idx != b.size())
        return 0;

    if (memo.count(state))
        return memo[state];

    int res = 0;
    for (size_t i = state.a_idx; i < a.size(); i++)
    {
        if (a[i] == b[state.b_idx])
            res += numDistinct(a, b, {i + 1, state.b_idx + 1});
    }
    memo[state] = res;
    return res;
}

int main()
{
    string a = "rabbbit";
    string b = "rabbit";
    cout << numDistinct(a, b, {0, 0}) << endl;
}
