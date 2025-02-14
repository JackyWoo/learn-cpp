//
// Created by wujianchao5 on 2024/12/30.
//
/// #64 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct State {
    int src;
    int c;

    bool operator==(const State &other) const { return src == other.src && c == other.c; }
};

namespace std {
    template<>
    struct hash<State> {
        size_t operator()(const State &state) const { return state.src + state.c; }
    };
}

unordered_map<State, int> memo;

int calculateMinimumHP(vector<vector<int> > &dungeon, int r, int c) {
    if (r == 0 && c == 0)
        return 1 - dungeon[r][c];

    if (r < 0 || c < 0)
        return INT_MAX;

    if (memo.count({r, c}))
        return memo[{r, c}];

    int res = std::min(calculateMinimumHP(dungeon, r - 1, c), calculateMinimumHP(dungeon, r, c - 1));
    res = std::max(res, 1)  - dungeon[r][c];
    memo[{r, c}] =  res;
    return res;
}

int main() {
    vector<vector<int> > dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    int res = calculateMinimumHP(dungeon, dungeon.size() - 1, dungeon[0].size() -1);
    cout << res << endl;
}
