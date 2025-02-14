/// 438 sliding-window medium

#include <string>
#include <iostream>

using namespace std;

bool isAnagrams(const string & s, int b, int e, const string & p)
{
    vector<int> char_nums(26, 0);
    vector<int> char_nums2(26, 0);
    for (int i=b; i<e; i++)
    {
        char_nums[s[i] - 'a']++;
        char_nums2[p[i-b] - 'a']++;
    }
    return char_nums == char_nums2;
}

vector<int> findAnagrams(const string & s, const string & p)
{
    vector<int> res;
    for (int i=0; i<s.size() - p.size(); i++)
    {
        if (isAnagrams(s, i, i+p.size(), p))
            res.push_back(i);
    }
    return res;
}

int main()
{
    string s = "cbaebabacd";
    string p = "abc";
    auto res = findAnagrams(s, p);
    for (auto & e : res)
        cout << e << endl;
}
