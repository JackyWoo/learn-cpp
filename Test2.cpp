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
#include <type_traits>

using namespace std;
using String = std::string;

struct Foo
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
};

int main()
{
    std::aligned_union_t<32, uint64_t, std::string> storage;
    String foo = "123456";
    new (&storage) String(foo.data(), foo.size());
}