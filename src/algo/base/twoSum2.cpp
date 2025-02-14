/// 167 double-pointers medium

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> towSum2(vector<int> & nums, int sum)
{
    for (int i=0, j = nums.size() - 1; i<j;)
    {
        int my_sum = nums[i] + nums[j];
        if (my_sum == sum)
            return {i, j};
        else if (my_sum < sum)
            i++;
        else
            j--;
    }
    throw 1;
}

int main()
{
    vector<int> nums = {2,7,11,15};
    auto res = towSum2(nums, 9);
    cout << res[0] + 1 << " " << res[1] + 1 << endl;
}
