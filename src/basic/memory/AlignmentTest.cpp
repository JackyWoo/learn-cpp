//
// Created by wujianchao5 on 2023/5/15.
//

//#pragma pack(8)

#include <iostream>

// objects of type S can be allocated at any address
// because both S.a and S.b can be allocated at any address
struct S
{
    char a; // size: 1, alignment: 1
    char b; // size: 1, alignment: 1
}; // size: 2, alignment: 1

// objects of type X must be allocated at 4-byte boundaries
// because X.n must be allocated at 4-byte boundaries
// because int's alignment requirement is (usually) 4
struct X
{
    int n; // size: 4, alignment: 4
    char c; // size: 1, alignment: 1
    // three bytes of padding bits
}; // size: 8, alignment: 4

struct alignas(32) Y
{
    char c; // size: 1, alignment: 1
    // three bytes of padding bits
    int n; // size: 4, alignment: 4
}; // size: 8, alignment: 4

struct Z
{
    char c; // size: 1, alignment: 1
    int n; // size: 4, alignment: 4
    // three bytes of padding bits
    X x;
}; // size: 16, alignment: 4

//#define offsetof(OBJECT_TYPE, MEMBER) __builtin_offsetof (OBJECT_TYPE, MEMBER)

int main()
{
    std::cout << "alignof(S) = " << alignof(S) << '\n'
              << "sizeof(S)  = " << sizeof(S) << '\n'
              << "alignof(X) = " << alignof(X) << '\n'
              << "sizeof(X)  = " << sizeof(X) << '\n'
              << "alignof(Y) = " << alignof(Y) << '\n'
              << "sizeof(Y)  = " << sizeof(Y) << '\n'
              << "alignof(Z) = " << alignof(Z) << '\n'
              << "sizeof(Z)  = " << sizeof(Z) << '\n';

    std::cout << std::endl;

    char a, b;
    X x;
    char c;
    std::cout << "address of (a) = " << static_cast<void *>(&a) << '\n'
              << "address of (b) = " << static_cast<void *>(&b) << '\n'
              << "address of (x) = " << &x << '\n'
              << "address of (c) = " << static_cast<void *>(&c) << '\n';

    //alignof(S) = 1
    //sizeof(S)  = 2
    //alignof(X) = 4
    //sizeof(X)  = 8
    //alignof(Y) = 4
    //sizeof(Y)  = 8
    //alignof(Z) = 4
    //sizeof(Z)  = 16
    //
    //address of (a) = 0x7ff7bcaf94af
    //address of (b) = 0x7ff7bcaf94ae
    //address of (x) = 0x7ff7bcaf94a0
    //address of (c) = 0x7ff7bcaf949f

    std::cout << offsetof(X, n)  << '\n'
              << offsetof(X, c) << '\n';


    /// 1. alignment is max member alignment
    /// 2. size = n * alignment, size >= sum_of_member_size and size < sum_of_member_size + alignment
    /// 3. address of x should be 0x7ff7bcaf94a4
}