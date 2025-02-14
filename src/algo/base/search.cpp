/// 704 base easy

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int searchRange(vector<int> & nums, int target)
{
    int i = 0;
    int j = nums.size() - 1;
    while (i <= j)
    {
        int mid = (i + j) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            j = mid;
        else
            i = mid;
    }
    return -1;
}

int main()
{
    vector<int> nums = {-1,0,3,5,9,12};
    cout << searchRange(nums, 9) << endl;
}
