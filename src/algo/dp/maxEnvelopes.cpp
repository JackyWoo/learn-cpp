//
// Created by wujianchao5 on 2024/12/25.
//

/// #354 dp hard

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Envelop
{
    int w;
    int h;
};

unordered_map<int, int> memo;

bool satisfy(Envelop & left, Envelop & right)
{
    return left.w < right.w && left.h < right.h;
}

int maxEnvelopes(vector<Envelop> & envelopes, int end)
{
    if (end == 0)
        return 1;
    if (memo.count(end))
        return memo[end];
    int res = 1;
    for (int i = end - 1; i >= 0; i--)
    {
        if (envelopes[i].w == envelopes[end].w)
            continue;
        if (satisfy(envelopes[i], envelopes[end]))
            res = std::max(res, maxEnvelopes(envelopes, i) + 1);
    }
    memo[end] = res;
    return res;
}

void sort(vector<Envelop> & envelopes)
{
    for (int i = 0; i < envelopes.size(); i++)
    {
        for (int j = i + 1; j < envelopes.size(); j++)
        {
            if (envelopes[i].w > envelopes[j].w)
            {
                Envelop tmp = envelopes[i];
                envelopes[i] = envelopes[j];
                envelopes[j] = tmp;
            }
            else if (envelopes[i].w == envelopes[j].w && envelopes[i].h > envelopes[j].h)
            {
                Envelop tmp = envelopes[i];
                envelopes[i] = envelopes[j];
                envelopes[j] = tmp;
            }
        }
    }
}

int main()
{
    vector<Envelop> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};

    /// sort envelopes
    sort(envelopes);

    /// find max envelopes size
    int max = 0;
    for (int i = 1; i < envelopes.size(); i++)
    {
        int max_i = maxEnvelopes(envelopes, i);
        max = std::max(max, max_i);
    }
    cout << max << endl;
}
