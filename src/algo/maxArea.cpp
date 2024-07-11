/** 11. 盛水最多的容器
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。

 示例 1：
输入：[1,8,6,2,5,4,8,3,7]
输出：49

示例 2：
输入：height = [1,1]
   输出：1

   提示：
   n == height.length
   2 <= n <= 105
   0 <= height[i] <= 104
*
*/

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
