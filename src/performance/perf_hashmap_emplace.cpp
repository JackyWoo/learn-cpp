#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>


inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

int main()
{
    size_t n = 100000;
    size_t m = 100;

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

    std::unordered_map<std::string, std::string> map1;
    map1.reserve(2*n);
    std::unordered_map<std::string, std::string> map2;
    map2.reserve(2*n);
    std::unordered_map<std::string, std::string> map3;
    map3.reserve(2*n);

    std::vector<std::string> vals1 = keys;
    std::vector<std::string> vals2 = keys;
    std::vector<std::string> vals3 = keys;

    auto test = [&] ()
    {
        auto t1 = getCurrentTimestamp();
        for (size_t i=0; i< n; i++)
            map1.emplace(keys[i], vals1[i]);

        auto t2 = getCurrentTimestamp();

        for (size_t i=0; i< n; i++)
            map2.insert({keys[i], vals1[i]});

        auto t3 = getCurrentTimestamp();

        for (size_t i=0; i< n; i++)
            map3.insert_or_assign(keys[i], vals1[i]);

        auto t4 = getCurrentTimestamp();

        for (size_t i=0; i< n; i++)
            std::hash<std::string>()(keys[i]);

        auto t5 = getCurrentTimestamp();


        std::cout << "Emplace " << std::to_string(t2 - t1) << "us" << std::endl;
        std::cout << "Insert " << std::to_string(t3 - t2) << "us" << std::endl;
        std::cout << "Insert or assign " << std::to_string(t4 - t3) << "us" << std::endl;
        std::cout << "Hash " << std::to_string(t5 - t4) << "us" << std::endl;
    };


    test();
    std::cout << std::endl;
    test();
}
