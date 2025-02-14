/// 3 sliding-window medium

#include <string>
#include <iostream>

using namespace std;

int windowContains(const string & s, int window_start, int index)
{
    for (int i=window_start; i<index; i++)
    {
        if (s[i] == s[index])
            return i + 1;
    }
    return -1;
}

int findAnagrams(string & s)
{
    int res = 1;
    int window_start = 0;
    for (int i=1; i<s.size(); i++)
    {
        int new_window = windowContains(s, window_start, i);
        if (new_window != -1)
        {
            res = max(res, i - window_start);
            window_start = new_window;
        }
    }
    return res;
}

int main()
{
    string s = "abcabcbb";
    cout << findAnagrams(s) << endl;
}
