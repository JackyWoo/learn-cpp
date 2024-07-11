//
// Created by JackyWoo on 2022/6/15.
//

#include <atomic>
#include <deque>
#include <filesystem>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <random>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <thread>
#include <tuple>
#include <unordered_map>

using namespace std;

struct Foo
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
};

int main()
{
    uint32_t e = 1000000000;
    uint64_t f = static_cast<uint64_t>(e) * 100;
    cout << "aaa " << to_string(f) << endl;

    cout << std::to_string(std::numeric_limits<double>::max()) << endl;
    cout << std::to_string(std::numeric_limits<uint64_t>::max()) << endl;
}