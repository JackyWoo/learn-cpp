/// 1 base easy

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
struct Pos
{
    int i;
    int j;
};

Pos search(vector<int> & nums, int sum)
{
    unordered_map<int, int> map;
    for (int i=0; i<nums.size(); i++)
    {
        map.emplace(nums[i], i);
    }
    for (int i=0; i<nums.size(); i++)
    {
        if (map.contains(sum - nums[i]))
            return {i, map[sum - nums[i]]};
    }
    throw 1;
}

int main()
{
    vector<int> nums = {2,7,11,15};
    cout << search(nums, 9).i << " " << search(nums, 9).j << endl;
}
