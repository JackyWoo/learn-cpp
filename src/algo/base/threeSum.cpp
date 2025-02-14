/// 1 base easy

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


vector<vector<int>> threeSum(vector<int> & nums)
{
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (int i=0; i<nums.size(); i++) // first
    {
        if (nums[i] > 0)
            break;
        for (int j=i+1; j<nums.size(); j++) // second
        {
            if (nums[i] + nums[j] > 0)
                break;
            for (int k=j+1; k<nums.size(); k++) // third
            {
                if (nums[i] + nums[j] + nums[k] == 0)
                    res.push_back({nums[i], nums[j], nums[k]});
                else if (nums[i] + nums[j] + nums[k] < 0)
                    continue;
                else
                    break;
            }
        }
    }
    // TODO duplicate
    return res;
}

int main()
{
    vector<int> nums = {-1,0,1,2,-1,-4};
    auto res = threeSum(nums);

    for (auto & vec : res)
    {
        for (auto & num : vec)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}