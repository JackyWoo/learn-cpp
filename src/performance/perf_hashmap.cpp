#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <ranges>
#include "SipHash.h"


inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

int main()
{
    size_t n = 1000000;
    size_t m = 1000;

    std::vector<std::string> keys;
    keys.reserve(n);

    for (size_t i=0; i<n; i++)
    {
        std::string k;
        k.resize(m);
        for (size_t j=0; j<m; j++)
            k[j] = char(i);
        keys.push_back(std::move(k));
    }

//    std::vector<std::string> values;
//    values.reserve(n);
//
//    for (size_t i=0; i<n; i++)
//    {
//        std::string v;
//        v.resize(m);
//        for (size_t j=0; j<m; j++)
//            v[j] = char(i);
//        values.push_back(std::move(v));
//    }

    std::unordered_map<std::string, char> map1;
    map1.reserve(2*n);
    std::unordered_map<std::string, char> map2;
    map2.reserve(2*n);

    auto t1 = getCurrentTimestamp();

    for (const auto & k : keys)
        std::hash<std::string>()(k);

    auto t2 = getCurrentTimestamp();

    for (const auto & k : keys)
    {
        SipHash hash;
        hash.update(k);
        hash.get64();
    }

    auto t3 = getCurrentTimestamp();

    for (size_t i=0; i< n; i++)
        map1.emplace(keys[i], 0);

    auto t4 = getCurrentTimestamp();

    for (size_t i=0; i< n; i++)
        map2.emplace(std::move(keys[i]), 0);

    auto t5 = getCurrentTimestamp();

    std::cout << "Generate hash time " << std::to_string(t2 - t1) << "us" << std::endl;
    std::cout << "Generate hash with SipHash time " << std::to_string(t3 - t2) << "us" << std::endl;
    std::cout << "Emplace hash map time " << std::to_string(t4 - t3) << "us" << std::endl;
    std::cout << "Emplace hash map with move time " << std::to_string(t5 - t4) << "us" << std::endl;

}
