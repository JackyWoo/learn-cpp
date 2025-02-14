/// 704 base easy

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> searchRange(vector<int> & nums, int target)
{
    int pos= -1; /// anyone of the target
    int i = 0;
    int j = nums.size() - 1;
    while (i <= j)
    {
        int mid = (i + j) / 2;
        if (nums[mid] == target)
        {
            pos = mid;
            break;
        }
        else if (nums[mid] > target)
            j = mid;
        else
            i = mid;
    }

    if (pos == -1)
        return {-1, -1};

    int s = 0, e = nums.size() - 1;
    for (int i=pos-1; i>=0; i--)
    {
        if (nums[pos] != nums[i])
        {
            s = i + 1;
            break;
        }
    }
    for (int i=pos + 1; i<nums.size(); i++)
    {
        if (nums[pos] != nums[i])
        {
            e = i - 1;
            break;
        }
    }
    return {s, e};
}

int main()
{
    vector<int> nums = {5,7,7,8,8,10};
    auto res = searchRange(nums, 8);
    cout << res[0] << " " << res[1] << endl;
}
