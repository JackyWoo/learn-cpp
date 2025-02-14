/// #77 backtrack medium

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> result;

void backTrack(int n, int k, vector<int> & state, int num)
{
    if (num == k)
    {
        result.push_back(state);
        return;
    }

    int last = num == 0 ? 0 : state[num - 1]; // last value in state
    for (int i = last + 1; i <= n; i++)
    {
        state[num] = i;
        backTrack(n, k, state, num + 1);
        state[num] = 0;
    }
}

void combine(int n, int k)
{
    vector<int> state(k, 0);
    backTrack(n, k, state, 0);
}

int main()
{
    int n = 4;
    int k = 2;

    combine(n, k);

    /// print result
    for (const auto & combination : result)
    {
        for (int i = 0; i < k; i++)
        {
            std::cout << combination[i] << " ";
        }
        std::cout << std::endl;
    }
}