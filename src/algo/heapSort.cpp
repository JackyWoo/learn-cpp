//
// Created by wujianchao5 on 2024/1/11.
//

#include <iostream>
#include <string>
#include <vector>

void buildHeap(std::vector<int32_t> & data, size_t index)
{
    size_t left_child = index * 2 + 1;
    size_t right_child = index * 2 + 2;

    /// has no child
    if (left_child >= data.size())
        return;

    /// has left child, but no right
    if (right_child >= data.size())
    {
        if (data[index] < data[left_child])
            std::swap(data[index], data[left_child]);
        return;
    }

    buildHeap(data, left_child);
    buildHeap(data, right_child);

    if (data[index] < data[left_child])
        std::swap(data[index], data[left_child]);

    if (data[index] < data[right_child])
        std::swap(data[index], data[right_child]);
}

void adjustHeap(std::vector<int32_t> & data, size_t head, size_t tail/* not included*/)
{
    if (head == tail - 1)
        return;

    size_t left_child = head * 2 + 1;
    size_t right_child = head * 2 + 2;

    /// has no child
    if (left_child >= tail)
        return;

    /// has left child, but no right
    if (right_child >= tail)
    {
        if (data[head] < data[left_child])
            std::swap(data[head], data[left_child]);
        return;
    }

    if (data[left_child] > data[right_child])
    {
        if (data[head] < data[left_child])
        {
            std::swap(data[head], data[left_child]);
            adjustHeap(data, left_child, tail);
            return;
        }
    }
    else
    {
        if (data[head] < data[right_child])
        {
            std::swap(data[head], data[right_child]);
            adjustHeap(data, right_child, tail);
            return;
        }
    }
}

void heapSort(std::vector<int32_t> & data)
{
    if (data.size() <= 1)
        return;

    /// build heap
    buildHeap(data, 0);

    for (size_t i = 0; i < data.size() - 1; i++)
    {
        /// move i to sorted area
        std::swap(data[0], data[data.size() - 1 - i]);
        /// adjust heap
        adjustHeap(data, 0, data.size() - 1 - i);
    }
}

int main()
{
    std::vector<int32_t> data = {4, 3, 5, 6, 2};
    heapSort(data);
    for (auto & e : data)
    {
        std::cout << std::to_string(e) << std::endl;
    }
}
