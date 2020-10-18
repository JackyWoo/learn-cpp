//
// Created by JackyWoo on 2022/1/26.
//

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

int main(int argc, char * argv[])
{
    using String = std::string;
    using MMap = std::unordered_map<String, String>;
    MMap container;

    //    size_t max_node = 100000000;
    size_t max_node = 3;
    if (argc > 1)
    {
        max_node = std::atoi(argv[1]);
        std::cout << "node size: " << max_node << std::endl;
    }

    auto begin_time = std::chrono::system_clock::now();

    for (size_t i = 0; i < max_node; i++)
    {
        size_t previous_bucket_count = container.bucket_count();

        /// 30 bytes
        String key = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" + String(reinterpret_cast<char *>(&i), sizeof(size_t));
        char chars[300] = {};
        for (char & j : chars)
            j = 'v';
        String val(chars, 300);

        auto begin = std::chrono::system_clock::now();
        container.emplace(key , val);
        auto end = std::chrono::system_clock::now();

        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        if (time > 10)
            std::cout << "time_ms : " << time << ", index : " << i << ", size : " << container.size()
                      << ", bucket size : " << container.bucket_count()
                      << ", bucket inc : " << container.bucket_count() - previous_bucket_count << std::endl;
    }

    auto end_time = std::chrono::system_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

    std::cout << "Done! container size : " << container.size() << ", map bucket size : "
    << container.bucket_count() << ", cost time_ms " << time_ms << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(60));
    return 0;
}