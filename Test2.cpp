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

struct Queue1
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

    cout << &amap << endl;
    amap[1] = 1;
    cout << &amap << endl;
    amap[1] = 2;
    cout << &amap << endl;
    amap[2] = 2;
    cout << &amap << endl;


    int32_t i = 3;
    cout << (i & ~1) << endl;

    Queue1 * foo_prt = new Queue1();
    void * ptr = foo_prt;
    auto * cast_ptr = static_cast<Queue1 *>(ptr);
    cout << (cast_ptr == nullptr) << endl;

    cout << "--------------random-------------" << endl;
    uint seed = (uint)(std::chrono::system_clock::now().time_since_epoch().count() * 1);
    std::default_random_engine engine(seed);

    for (int m = 0; m < 1000; m++)
    {
        std::uniform_int_distribution<int32_t> distribution(0, 10000);
        int n = distribution(engine);
        int ra = n % 40 % 10;
        int rb = n % 10;
        if (ra != rb)
            cout << "not equal " << n << endl;
    }

    uint32_t ui = 2484513939;
    cout << static_cast<int32_t>(ui) << endl;

    int64_t tttl = -50;
    int64_t r = tttl >> 32;
    cout << r << endl;
    struct Long
    {
        int low;
        int high;
    };
    Long * l = reinterpret_cast<Long *>(&r);
    l->high = 0;
    auto * rr = reinterpret_cast<uint64_t *>(l);
    cout << *rr << endl;

    cout << static_cast<int32_t>(tttl) << endl;


    const char * ss = "123";
    std::string sss = "123";
    cout << sizeof(sss) << endl;

    cout << "--------------shift-------------" << endl;
    uint32_t uu = std::numeric_limits<uint32_t>::max();
    cout << static_cast<int32_t>(uu) << " -- " << (uu >> 16) << endl;

#if 1 == 2 || 2 == 2
    cout << 1 << endl;
#endif

    auto * queue_ptr = new Queue1(1, 1);
    cout << "queue_ptr address:" << reinterpret_cast<uint64_t>(queue_ptr) << endl;


#define ALIGN(x, a)		__ALIGN_KERNEL((x), (a))
#define __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))

    auto aligned = ALIGN(9, 8);
    cout << "ALIGN(1, 8) is " << aligned << endl;
    cout << (aligned >> 3) << endl;

}