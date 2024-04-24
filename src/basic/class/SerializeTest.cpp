//
// Created by wujianchao5 on 2020/12/30.
//

#include <iostream>
#include <memory>

using namespace std;


class Foo {
public:
    Foo(uint64_t a_, uint32_t b_) : a(a_), b(b_) {}

    /// There are 4 bytes padding at the end of object.
    uint64_t a;
    uint32_t b;

    /// Virtual function will add virtual pointer to head of object.
    virtual void func() {}
};

int main() {
    constexpr int32_t len = sizeof(Foo);
    cout << "sizeof(Foo) " << len << endl;

    Foo f{std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint32_t>::max() - 1};
    char *buf = new char[len];

    /// serialize
    memcpy(buf, (void *) &f, len);

    /// deserialize
    Foo *b;
    b = reinterpret_cast<Foo *>(buf);
    cout << (b->a == f.a) << endl;
    cout << (b->b == f.b) << endl;
}