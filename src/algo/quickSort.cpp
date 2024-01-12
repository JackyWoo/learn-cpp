//
// Created by wujianchao5 on 2024/1/10.
//

#include <vector>
#include <iostream>


void quickSort(std::vector<int32_t> & data, int32_t left, int32_t right)
{
    if (left >= right)
        return;

    int32_t pivot = left;
    for (int32_t i = left + 1; i <= right; i++)
    {
        if (data[i] < data[pivot])
        {
            if (pivot + 1 != i)
                std::swap(data[pivot + 1], data[i]);
            std::swap(data[pivot], data[pivot + 1]);
            pivot++;
        }
    }

    quickSort(data, left, pivot - 1);
    quickSort(data, pivot + 1, right);
}

int main()
{
    std::vector<int32_t> data = {1, 3, 5, 6, 2};
    quickSort(data, 0, static_cast<int32_t>(data.size()) - 1);
    for (auto & e : data)
    {
        std::cout << std::to_string(e) << std::endl;
    }
}