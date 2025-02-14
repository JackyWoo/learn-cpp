/// 11 greedy medium
#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int> heights)
{
    int max = 0;
    int s = -1;
    for (int i = 0; i < heights.size() - 1; i++)
    {
        if (s != -1 && heights[s] >= heights[i])
            continue;

        int e = -1;
        for (int j = int(heights.size()) - 1; j > i; j--)
        {
            if (e != -1 && heights[e] >= heights[j])
                continue;

            auto area = (j - i) * min(heights[i], heights[j]);
            if (area > max)
            {
                max = area;
                e = j;
                s = i;
            }
        }
    }
    return max;
}


int main()
{
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << to_string(maxArea(heights)) << endl;
}
