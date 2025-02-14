//
// Created by wujianchao5 on 2024/12/26.
//
/// #931 dp medium

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


unordered_map<int, int> memo;

bool isValid(int previous_col, int col, int n)
{
    if (previous_col == -1)
        return true;
    if (previous_col == 0)
        return col == 1;
    if (previous_col == n - 1)
        return col == n - 2;
    return col <= previous_col + 1 && col >= previous_col - 1;
}

int minFallingPathSum(vector<vector<int>> matrix, int row, int previous_col)
{
    if (row == matrix.size())
        return 0;

    if (memo.count(row))
        return memo[row];

    int res = INT_MAX;
    for (int i = 0; i < matrix.size(); i++)
    {
        if (isValid(previous_col, i, matrix.size()))
            res = std::min(res, minFallingPathSum(matrix, row + 1, i) + matrix[row][i]);
    }

    memo[row] = res;
    return res;
}

int main()
{
    const int n = 3;
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << to_string(minFallingPathSum(matrix, 0, -1)) << endl;
}
