//
// Created by wujianchao5 on 2024/4/16.
//
#include <vector>

int main()
{
    /// no auto vectorization
    constexpr size_t len = 10 * 1000 * 1000;

    std::vector<int32_t> a(len);
    std::vector<int32_t> b(len);
    std::vector<int32_t> c(len);

    for (int i=0;i<len;i++)
        c[i] = a[i] + b[i];
}
