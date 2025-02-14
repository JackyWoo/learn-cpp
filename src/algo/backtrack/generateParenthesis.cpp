/** 22 生成括号

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
示例 1：

    输入：n = 3
    输出：["((()))","(()())","(())()","()(())","()()()"]
    示例 2：

    输入：n = 1
    输出：["()"]

    提示：

    1 <= n <= 8
 */

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> results;

bool checkLeft(vector<int> &resolution, int idx)
{
    if (idx == 0)
        return true;

    int count=0;
    for (int i=0; i < idx; i++)
        if (resolution[i] == -1)
            count += 1;

    return count < resolution.size() / 2;
}

bool checkRight(vector<int> &resolution, int idx)
{
    if (idx == 0)
        return false;

    int sum=0;
    for (int i=0; i < idx; i++)
        sum += resolution[i];

    return sum < 0;
}

void backtrack(vector<int> & resolution, int idx)
{
    if (idx == resolution.size())
    {
        results.push_back(resolution);
        return;
    }

    if (checkLeft(resolution, idx))
    {
        resolution[idx] = -1;
        backtrack(resolution, idx + 1);
    }

    if (checkRight(resolution, idx))
    {
        resolution[idx] = 1;
        backtrack(resolution, idx + 1);
    }
}

void generateParenthesis(int n)
{
    vector<int> resolution(2 * n, 0);
    backtrack(resolution, 0);
}

int main()
{
    generateParenthesis(3);
    for (auto & r : results)
    {
        for (auto i : r)
            cout << ((i == -1) ? "(" : ")");
        cout << endl;
    }
}
