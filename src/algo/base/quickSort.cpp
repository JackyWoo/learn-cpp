//
// Created by wujianchao5 on 2024/1/10.
//

#include <vector>
#include <iostream>

using namespace std;

void quickSort(vector<int> & data, int left, int right)
{
    if (left >= right)
        return;

    int pivot = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (data[i] < data[pivot])
        {
            swap(data[pivot], data[pivot + 1]);
            if ( i!= pivot + 1)
                swap(data[pivot], data[i]);
            pivot ++;
        }
    }

    quickSort(data, left, pivot - 1);
    quickSort(data, pivot + 1, right);
}

int main()
{
    vector<int> data = {1, 3, 5, 6, 2};
    quickSort(data, 0, static_cast<int>(data.size()) - 1);
    for (auto & e : data)
    {
        cout << to_string(e) << endl;
    }
}