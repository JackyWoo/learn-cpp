/// 2951 greedy medium
#include <iostream>
#include <vector>

using namespace std;

vector<int> findPeaks(vector<int> & mountain)
{
    vector<int> ret;
    for (int i = 1; i < mountain.size() - 1; i++)
    {
        if (mountain[i] > mountain[i-1] && mountain[i] > mountain[i+1])
        {
            ret.push_back(i);
            i++;
        }
    }
    return ret;
}

int main()
{
    vector<int> mountain = {1, 4, 3, 8, 5};
    for (auto i : findPeaks(mountain))
    {
        cout << std::to_string(i) << ", ";
    }
}