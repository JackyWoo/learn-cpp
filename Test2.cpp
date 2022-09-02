//
// Created by JackyWoo on 2022/6/15.
//

#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <fcntl.h>
#include <unistd.h>
#include <deque>
#include <sys/event.h>
#include <tuple>
#include <filesystem>
#include <random>

using namespace std;

struct Foo
{
    int32_t a;
    int32_t b;
};

enum Options
{
    OPT_NONE = 0,
    OPT_PREFIX = 1,
    OPT_LOWERCASE = 2
};

void format(int value, Options options = OPT_NONE)
{
    cout << "match" << endl;
}

int main()
{

    int16_t aaaa_aab[2] = {1, 2};
    unique_ptr<int16_t *> uniquePtr = std::make_unique<int16_t *>(aaaa_aab);

    cout << *(aaaa_aab) << endl;

    int16_t * aa = *(uniquePtr.get());
    int16_t * bb = *(uniquePtr.release());

    cout << *(aa) << endl;
    cout << *(bb) << endl;

//    cout << **(uniquePtr.get()) << endl;
//    cout << **(uniquePtr.release()) << endl;

    /// eventfd test buffer

#ifdef __linux__
    int efd = eventfd(0, 0);
#endif

    unordered_map<int32_t, int32_t> amap;

    cout << &amap<<endl;
    amap[1] = 1;
    cout << &amap<<endl;
    amap[1] = 2;
    cout << &amap<<endl;
    amap[2] = 2;
    cout << &amap<<endl;


    int32_t  i = 3;
    cout << (i & ~1)<<endl;

    Foo * foo_prt = new Foo();
    void * ptr = foo_prt;
    auto * cast_ptr = static_cast<Foo *>(ptr);
    cout << (cast_ptr == nullptr) << endl;

    cout << "--------------random-------------"<<endl;
    uint seed = (uint)( std::chrono::system_clock::now()
                           .time_since_epoch().count() * 1 );
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int32_t>
        distribution( 0, 5 / 2 );
    cout << 5 / 2 + distribution(engine) << endl;

}