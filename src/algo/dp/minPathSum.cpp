//
// Created by wujianchao5 on 2024/12/30.
//
/// #64 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct State {
    int r;
    int c;

    bool operator==(const State &other) const { return r == other.r && c == other.c; }
};

namespace std {
    template<>
    struct hash<State> {
        size_t operator()(const State &state) const { return state.r + state.c; }
    };
}

unordered_map<State, int> memo;

int minPathSum(vector<vector<int> > &grid, int r, int c) {
    if (r == grid.size())
        return 0;
    if (memo.count({r, c}))
        return memo[{r, c}];
    int res = INT_MAX;
    res = std::min(res, grid[r][c] + minPathSum(grid, r + 1, c));
    if (c != grid[0].size() - 1)
        res = std::min(res, grid[r][c] + minPathSum(grid, r + 1, c + 1));
    memo[{r, c}] = res;
    return res;
}

int main() {
    vector<vector<int> > grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    int res = INT_MAX;
    for (int i = 0; i < grid.size(); i++) {
        res = std::min(res, minPathSum(grid, i, 0));
    }
    cout << res << endl;
}
