//
// Created by JackyWoo on 2021/10/30.
//

#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <list>
#include <map>

using namespace std;

template <typename V>
struct HasMemberSize
{
private:
    template <typename T>
    static auto check(int) -> decltype(std::declval<T>().size(), std::true_type());
    template <typename T>
    static std::false_type check(...);

public:
    static constexpr bool value = std::is_same<decltype(check<V>(0)), std::true_type>::value;
};

template <typename T>
inline size_t sizeOf(typename std::enable_if<HasMemberSize<T>::value, T>::type * obj)
{
    return obj->size();
}

template <typename T>
inline size_t sizeOf(typename  std::enable_if<!HasMemberSize<T>::value, T>::type * obj)
{
    return 0;
}


struct Node
{
    int a{2};
    int b{2};
    size_t size() { return sizeof(a) + sizeof(b) + 4; }
};

template <class V>
struct Table
{
    vector<V> container;
    size_t size()
    {
        for (const auto & e : container)
        {
            size(e);
        }
    }
};
using UInt64 = size_t;
using String = std::string;
using ChildrenSet = std::unordered_set<std::string>;

struct Node2
{
    String data;
    uint64_t acl_id = 0; /// 0 -- no ACL by default
    bool is_sequental = false;
    int32_t seq_num = 0;
    ChildrenSet children{};

    /// object memory size
    UInt64 size() const
    {
        UInt64 child_size{0};
        for (const auto & child : children)
        {
            child_size += child.size();
        }
        return data.size() + sizeof(Node) + child_size;
    }
};


struct Node2Wrapper
{
    Node2 value;
    bool flag{false};
};
int main()
{
    bool a = HasMemberSize<string>::value;
    cout << "string has member size() : " << a << endl;

    bool b = HasMemberSize<int>::value;
    cout << "int has member size() : " << b << endl;
    bool c = HasMemberSize<Node>::value;
    cout << "Node has member size() : " << c << endl;

    string ss = "123";
    cout << "string(123) size is " << sizeOf<string>(&ss) << endl;
//    cout << "string(123) size is " << sizeOfV2(&ss) << endl;
//    cout << "string(123) size is " << sizeOf(&ss) << endl;

    int *i = new int;
    cout << "i size is " << sizeOf<int>(i) << endl;
//    cout << "i size is " << sizeOfV2<int>(i) << endl;
//    cout << "i size is " << sizeOf(i) << endl;

    Node n;
    cout << "n size is " << sizeOf<Node>(&n) << endl;
//    cout << "n size is " << sizeOfV2<Node>(&n) << endl;
//    cout << "n size is " << sizeOf(&n) << endl;

    unsigned num{0};
    cout<<num - 1<<endl;

    cout<<"------"<<endl;
    Node2 n2;
    n2.data = "123456";
    n2.children.insert("1");

    list<Node2Wrapper> l;
    l.push_back({n2, false});

    auto itr = l.begin();
    auto backup = itr;
//    l.erase(itr);
    cout<<itr->value.size()<<endl;
//    UInt64 len = sizeOf<Node2>(&(itr->value));
//    cout<<"len" << len<<endl;


}