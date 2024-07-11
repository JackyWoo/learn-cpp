//
// Created by wujianchao5 on 2021/1/4.
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
#include <bit>

using Task = std::function<void()>;

void execute(Task task)
{
    task();
}

int main()
{
    using namespace std;
    using String = std::string;

    using Job = std::function<void>();

    Job job;
    cout << "not null job" << endl;

    list<int> l;

    cout << l.size() << endl;
    cout << *l.begin() << endl;

    //    l.emplace_back("1");
    //    l.emplace_back("2");
    //    l.emplace_back("3");
    l.emplace_back(1);
    l.emplace_back(2);
    l.emplace_back(3);


    for (auto it = l.begin(); it != l.end(); it++)
    {
        cout << *it << endl;
    }

    map<String, int> map = {{"1", 1}};

    auto tmp = map.find("2");
    if (tmp != map.end())
    {
        cout << tmp->second << endl;
    }

    cout << "priority_queue" << endl;
    priority_queue<int> queue;
    // seg fault
    //    int a = queue.top();

    std::cout << sizeof(unsigned long long) << std::endl;
    std::cout << sizeof(unsigned long) << std::endl;

    // no building error
    auto f = [&map] { std::cout << "a" << std::endl; };


    std::cout << sizeof(byte) << std::endl;
    std::cout << sizeof(char) << std::endl;

    //    char * a = "a";
    //    byte * b = reinterpret_cast<byte *>('a');


    std::atomic<char> aa('a');
    std::cout << sizeof(atomic<char>) << std::endl;

    cout << "---not init int-----" << endl;

    int i100;
    int j100 = {};
    cout << i100 << endl;
    cout << j100 << endl;

    cout << "--------" << endl;

    cout << "shared_mutex size :" << sizeof(std::shared_mutex) << endl;
    cout << "mutex size :" << sizeof(std::mutex) << endl;
    cout << "long size :" << sizeof(long) << endl;
    cout << "string size :" << sizeof(std::string) << endl;

    cout << "--------" << endl;

    std::shared_ptr<std::map<String, String>> mm = make_shared<std::map<String, String>>();
    if (mm)
    {
        cout << "mm is initialized" << endl;
    }
    string ss = "aa";
    mm->emplace(ss, move(ss));
    cout << mm->cbegin()->first << mm->cbegin()->second << endl;
    cout << ss << endl;

    Task task = [&mm] {
        cout << "in task\n";
        cout << mm->cbegin()->first << mm->cbegin()->second << endl;
    };

    std::thread t(task);
    t.detach();

    this_thread::sleep_for(chrono::seconds(1));
    //    execute(task);

    cout << "--------" << endl;

    struct Pod
    {
        int32_t a;
        int32_t b;
    };
    std::unordered_map<int32_t, Pod> mm1 = {{1, {1, 1}}, {1, {1, 1}}, {1, {1, 1}}};
    std::unordered_map<int32_t, Pod> mm2 = {{1, {1, 1}}};
    std::cout << sizeof(mm1) << std::endl;
    std::cout << sizeof(mm2) << std::endl;

    std::vector<int> aaa = {1, 2, 3};
    for (auto it = aaa.rbegin(); it != aaa.rend(); it++)
    {
        cout << *it << endl;
    }

    std::vector<int> a{};
    if (a.empty())
    {
        cout << "lalaal" << endl;
    }
    cout << "--------" << endl;

    struct Car
    {
        int price;
    };

    const Car * car = new Car;
    //    car->price = 10;

    String a10 = "plus(sum(plus(a, 2)), 1)";
    String old_value = "plus";
    String new_value = "minus";
    string::size_type pos(0);
    while ((pos = a10.find(old_value)) != string::npos)
    {
        a10.replace(pos, old_value.length(), new_value);
    }

    std::cout << a10 << std::endl;


    struct Ca
    {
        String name;
        Ca(String && name_) : name(name_){};
    };

    String name_ca = "a";
    Ca ca(std::move(name_ca));
    std::cout << name_ca << endl;

    //    thread t1([]()-> void {
    //        throw "exception in thread t1";
    //    });
    //    t1.detach();
    //    std::this_thread::sleep_for(2000ms);

    struct Ob
    {
        int a;

        bool operator<(const Ob & rhs) const
        {
            return this->a < rhs.a;
            ;
        }

        bool operator>(const Ob & rhs) const
        {
            return this->a > rhs.a;
            ;
        }

        bool operator<=(const Ob & rhs) const { return this->a <= rhs.a; }

        bool operator>=(const Ob & rhs) const { return this->a >= rhs.a; }

        bool operator==(const Ob & rhs) const { return a == rhs.a; }

        bool operator!=(const Ob & rhs) const { return !(rhs == *this); }
    };
    struct ObHash
    {
        size_t operator()(const Ob & ob) { return std::hash<int>{}(ob.a); };
    };

    unordered_map<long, Ob> mmpp{};

    Ob k1{1};
    mmpp.emplace(1, k1);
    unordered_set<Ob, ObHash> paths;

    for (auto & p : mmpp)
    {
        paths.insert(p.second);
    }

    String ccc = "1000";
    char ccc_data[4] = {'\1', '\0', '\0', '\0'};
    int int_val = *reinterpret_cast<int *>(ccc_data);
    cout << int_val << endl;

    cout << int_val << endl;

    int32_t aaa2 = 2003003507;
    //    int32_t aaa2=1936221047;
    char * ccc2 = "wchs";
    cout << "rr\t";
    cout << *reinterpret_cast<char *>(&aaa2) << endl;
    cout << *reinterpret_cast<int32_t *>(ccc2) << endl;

    int i10 = 2;
    cout << hex << __builtin_bswap32(i10) << endl;
    cout << hex << __builtin_bswap32(__builtin_bswap32(i10)) << endl;

    std::stringstream ss1;
    ss1 << hex;
    ss1 << 20 << endl;
    cout << ss1.str() << endl;

    std::stringstream ss2;
    //    ss2<<hex;
    ss2 << 20 << endl;
    cout << ss2.str() << endl;

    String ssss2("123", 2);
    cout << ssss2 << endl;
    cout << sizeof(ssss2.size()) << endl;
    cout << ssss2.max_size() << endl;
    char * cccc2 = ssss2.data();
    char aaaa = *(cccc2 + 2);
    cout << aaaa << endl;

    char a101[5] = {'\0'};
    a101[0] = '1';

    String ss10(a101, 2);
    cout << ss10.size() << endl;
    cout << ss10.data() << endl;

    String sss0;
    //    int aaa0 = std::stoi(sss0);
    //    cout<<"st0i "<<aaa0<<endl;


    cout << "-------vector-------" << endl;
    vector<int> vv;
    cout << vv.size() << endl;
    cout << vv.capacity() << endl;
    vv.push_back(1);
    vv.push_back(2);
    vv.push_back(3);
    cout << vv.size() << endl;
    cout << vv.capacity() << endl;
    vv.resize(1);
    cout << vv.size() << endl;
    cout << vv.capacity() << endl;

    cout << "-------split string-------" << endl;
    size_t pos1;
    std::string token;
    String list_str = "1,2,3";
    while ((pos1 = list_str.find(',')) != std::string::npos)
    {
        token = list_str.substr(0, pos1);
        list_str.erase(0, pos1 + 1);
        cout << token << endl;
    }
    cout << list_str << endl;


    cout << "-------split string-------" << endl;
    if (std::is_integral<int>::value)
    {
        cout << "int is integral" << endl;
    }
    struct A
    {
        String size() { return "1"; }
    };

    String (A::*ptr)() = &A::size;
    std::cout << "A has member function size() : " << std::is_member_function_pointer<decltype(ptr)>::value << std::endl;

    cout << "-------username-------" << endl;

    char user_name[64];
    getlogin_r(user_name, 64);
    cout << user_name << endl;


    cout << "-------aa-------" << endl;

    int32_t aa11 = __builtin_bswap32(1835955314);
    int32_t aa12 = __builtin_bswap32(1835955314);
    cout << String(reinterpret_cast<char *>(&aa11), 4) << endl;

    String regex = "[a-zA-Z0-9_:]";
    String ss15 = "-aa-bb";

    if (!isalpha(*ss15.begin()) && *ss15.begin() != '_' && *ss15.begin() != ':')
    {
        ss15 = "m_" + ss15;
    }

    String metric_name = "0_a0a-b--b--";
    metric_name = std::regex_replace(metric_name, std::regex("[^a-zA-Z0-9_:]"), "_");
    cout << metric_name << endl;
    metric_name = std::regex_replace(metric_name, std::regex("^[^a-zA-Z]*"), "");

    cout << metric_name << endl;

    cout << dec << std::numeric_limits<int64_t>::max() << endl;
    cout << "218129922835423721" << endl;

    int64_t num1 = std::numeric_limits<int64_t>::max();
    cout << num1 + 1 << endl;

    cout << "-------aa-------" << endl;

    int fd = ::open("a.log", O_RDWR | O_CREAT | O_TRUNC, 0644);

    char * to_write = "123456";
    int size = write(fd, to_write, 6);
    cout << "write size " << size << endl;
    ftruncate(fd, 2);
    char read_content[6];
    int size2 = read(fd, read_content, 2);
    cout << "read size " << size2 << endl;
    cout << "read content " << read_content << endl;
    close(fd);

//    printf("the size of i is %zu \n", -1);

    cout << sizeof(bool) << endl;

    struct TastS
    {
        int32_t a;
    };
    TastS ts;
    TastS ts2{};

    cout << "struct default value:" << endl;
    cout << "ts: " << ts.a << endl;
    cout << "ts2: " << ts2.a << endl;

    cout << "-------aa-------" << endl;
    unordered_map<int64_t, int64_t> mmmmp;

    cout << mmmmp[0] << endl;

    cout << "-------alignment-------" << endl;
    struct Foo100
    {
        char a;
        int32_t b;
        double c;
    };
    struct Foo101
    {
        int32_t b;
        double c;
        char a;
    };
    struct Foo102
    {
        char a;
        Foo101 f;
    };
    struct Foo103
    {
        char a;
        char b;
    };
    struct Foo104
    {
        int32_t a;
        char b;
    };
    cout << "Foo100 size " << sizeof(Foo100) << endl; // size 包含了alignment 和 padding的空间， 字段顺序不同，size可能不同
    cout << "Foo101 size " << sizeof(Foo101) << endl;
    cout << "Foo102 size " << sizeof(Foo102) << endl;
    cout << "Foo103 size " << sizeof(Foo103) << endl;
    cout << "Foo104 size " << sizeof(Foo104) << endl;
    cout << "Foo100 alignment " << alignof(Foo100) << endl; // struct的对齐是最大字段的类型的对齐的大小
    cout << "Foo101 alignment " << alignof(Foo101) << endl;
    cout << "Foo102 alignment " << alignof(Foo102) << endl;
    cout << "Foo103 alignment " << alignof(Foo103) << endl;
    cout << "Foo104 alignment " << alignof(Foo104) << endl;


    cout << "-------pirnt %zu %d-------" << endl;
    size_t ass = 94081208070;
    cout << int(ass)<< endl;
    cout << sizeof(mm1.size());

    cout << "-------resize-------" << endl;
    String ssss = "123";
    ssss.resize(2);
    cout << ssss <<endl;

    cout << "-------map emplace resut-------" << endl;

    unordered_map<String, int32_t> map_ret_test;
    map_ret_test.emplace("a", 1);
    auto map_ret = map_ret_test.emplace("a", 2);
    cout << map_ret_test.size() << " "<< map_ret_test.at("a") << " " << map_ret.second << endl;

    auto& aamm = map_ret_test["b"];
    aamm = 5;
    cout<< map_ret_test["b"] <<endl;
    cout<< sizeof(String) <<endl;

    cout << "-------queue111-------" << endl;


    int8_t aaaa_aab[2] = {1, 2};
    unique_ptr<int8_t *> uniquePtr = std::make_unique<int8_t *>(aaaa_aab);
    int8_t * ffffff = *uniquePtr;
    int8_t fff = *(static_cast<int8_t *>(*uniquePtr));
    cout << string(fff, 1) << endl;
    cout << (char *)ffffff << endl;
    int8_t bbb_aa = 1;
    cout << bbb_aa << endl;

    cout << "-------lower to upper-------" << endl;
    const auto flip_case_mask = 'A' ^ 'a';
    uint8_t ccc1 = 'b';
    cout << (0 ^ 0) << endl;

    cout << "-------string-------" << endl;
    String ss111 = "0000000000";
    cout<< sizeof(String) <<endl;
    cout<< "capacity: " << ss111.capacity() << ", size: " << ss111.size() << endl;

    cout << "-------bit test-------" << endl;
    uint64_t bit_a = 7;
    cout << __builtin_clzll(bit_a) << endl;
    uint8_t bit_b = reinterpret_cast<uint8_t*>(&bit_a)[0];
    cout << bit_b << endl;

    cout << "-------atomic test-------" << endl;
    struct RangesPos
    {
        size_t x;
        size_t y;
    };

    using AtomicRangePos = std::atomic<RangesPos>;
    AtomicRangePos pos11({1, 1});
    RangesPos start = pos11.load();
    RangesPos end(2, 2);
    pos11.compare_exchange_strong(start, end);
    cout << pos11.load().x << endl;

    struct RangesState
    {
        RangesPos pos;
        mutable std::mutex mutex;
    };

    using RangesStatePtr = std::shared_ptr<RangesState>;
    auto state_ptr = std::make_shared<RangesState>();
//    state_ptr->pos = {1, 1};
    std::lock_guard lock(state_ptr->mutex);
    cout << state_ptr->pos.x << endl;

    cout << "-------double overflow test-------" << endl;
    double double_max = std::numeric_limits<double>::max();
    double long_max = std::numeric_limits<uint64_t>::max();
    double d1235 = double_max + double_max / 2;
    cout << d1235 << endl;
    cout << d1235 / 2 << endl;
    cout << (d1235 > d1235 / 2) << endl;
    cout << (d1235 > double_max) << endl;
    cout << (d1235 > 1.0) << endl;

    cout << "max value of double larger than max value of long? " << (double_max > long_max) << endl;

    int64_t i1 = 1;
    uint64_t i2 = 2;
    int64_t i3 = i1 - i2;
    cout << std::to_string(i3) << endl;
    cout << std::to_string(i1 - i2) << endl;
}
