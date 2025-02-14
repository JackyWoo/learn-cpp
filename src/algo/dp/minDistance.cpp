//
// Created by wujianchao5 on 2024/12/26.
//

/// #73 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct State
{
    int r;
    int c;

    bool operator==(const State & other) const { return r == other.r && c == other.c; }
};


namespace std
{
template <>
struct hash<State>
{
    size_t operator()(const State & state) const { return state.r + state.c; }
};
}

unordered_map<State, int> memo;

void append(string & target, string & source, int start, int end)
{
    for (int i= start; i<end; i++)
    {
        target.push_back(source[i]);
    }
}

int minDistance(const string & w1, const string & w2, State state)
{
    if (state.r == w1.size() && state.c == w2.size())
        return 0;

    if (state.r == w1.size())
        return w2.size() - state.c;

    if (state.c == w2.size())
        return w1.size() - state.r;

    if (memo.count(state))
        return memo[state];

    int res = INT_MAX;
    if (w1[state.r] == w2[state.c])
    {
        res = std::min(res, minDistance(w1, w2, {state.r + 1, state.c + 1}));
    }
    else
    {
        /// add
        int dis_for_add = minDistance(w1, w2, {state.r, state.c + 1}) + 1;
        res = std::min(res, dis_for_add);

        /// delete
        int dis_for_del = minDistance(w1, w2, {state.r + 1, state.c}) + 1;
        res = std::min(res, dis_for_del);

        /// modify
        int dis_for_mod = minDistance(w1, w2, {state.r + 1, state.c + 1}) + 1;
        res = std::min(res, dis_for_mod);
    }

    memo[state] = res;
    return res;
}

int main()
{
    string w1 = "horse";
    string w2 = "ros";

    cout << minDistance(w1, w2, {0, 0}) << endl;
}
