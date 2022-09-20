//
// Created by wujianchao5 on 2022/9/6.
//

#include <type_traits>
#include <iostream>
#include <exception>

struct JavaIntHash
{
    using ReturnType = int32_t;

#define IS_BOOL std::is_same_v<T, bool>
#define IS_INT64 std::is_same_v<T, std::int64_t>
#define IS_INTEGER  std::is_integral_v<T>
#define NOT_LONG sizeof(T) <= 4

    template <class T, typename std::enable_if_t<IS_BOOL, T>* = nullptr>
    static int32_t apply(T x)
    {
        return x ? 1231 : 1237;
    }

    template <class T, typename std::enable_if_t<IS_INT64, T>* = nullptr>
    static int32_t apply(T x)
    {
        T copy = x;
        /// Implement Java >>> operation
        copy = copy >> 32;
        struct Long
        {
            int32_t low;
            int32_t high;
        } * l = reinterpret_cast<Long *>(&copy);
        l->high = 0;
        return static_cast<int32_t>(x ^ copy);
    }

    template <class T, typename std::enable_if<IS_INTEGER && NOT_LONG, T>::type* = nullptr>
    static int32_t apply(T x)
    {
        return x;
    }

    template <class T, typename std::enable_if<!(IS_BOOL || IS_INT64 || (IS_INTEGER && NOT_LONG)), T>::type * = nullptr>
    static int32_t apply(T /*x*/)
    {
        throw "Not implemented type for Java int hash";
    }

};

int main()
{
    int32_t i = 1;
    std::cout << JavaIntHash::apply(i) << std::endl;
    int64_t l = 50;
    std::cout << JavaIntHash::apply(l) << std::endl;
    int64_t ll = -50;
    std::cout << JavaIntHash::apply(ll) << std::endl;
//    float ft = 1.0;
//    std::cout << JavaIntHash::apply(ft) << std::endl;

    int ii = -2;
    std::cout << static_cast<uint32_t >(ii) << std::endl;
    return 0;
}