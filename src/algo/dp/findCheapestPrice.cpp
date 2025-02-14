//
// Created by wujianchao5 on 2024/12/30.
//
/// 787 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct State {
    int r;
    int k;

    bool operator==(const State &other) const { return r == other.r && k == other.k; }
};

namespace std {
    template<>
    struct hash<State> {
        size_t operator()(const State &state) const { return state.r + state.k; }
    };
}

unordered_map<State, int> memo;

int findPrice(vector<vector<int> > & flights, int src, int dst) {
    int res = INT_MAX;
    for (auto &flight: flights) {
        if (flight[0] == src && flight[1] == dst)
            res = std::min(res, flight[2]);
    }
    if (res == INT_MAX)
        return -1;
    return res;
}

vector<int> findNexts(vector<vector<int> > &flights, int src) {
    vector<int> res;
    for (int i = 0; i < flights.size(); i++) {
        if (flights[i][0] == src)
            res.emplace_back(i);
    }
    return res;
}


int findCheapestPrice(vector<vector<int> > &flights, int src, int dst, int k) {
    if (k == -1)
        return -1;

    if (k == 0)
        return findPrice(flights, src, dst);

    if (memo.count({src, k}))
        return memo[{src, k}];
    const auto nexts = findNexts(flights, src);
    if (nexts.empty())
        return -1;

    int res = INT_MAX;
    for (auto & i: nexts) {
        int rest_price = findCheapestPrice(flights, flights[i][1], dst, k - 1);
        if (rest_price != -1)
            res = std::min(res, flights[i][2] + rest_price);
    }

    if (res == INT_MAX)
        res = -1;

    memo[{src, k}] = res;
    return res;
}

int main() {
    vector<vector<int> > flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    int src = 0, dst = 3, k = 1;
    int res = findCheapestPrice(flights, src, dst, k);
    cout << res << endl;
}
