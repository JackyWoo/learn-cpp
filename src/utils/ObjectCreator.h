//
// Created by wujianchao5 on 2022/8/9.
//

#ifndef LEARN_CPP_OBJECTCREATOR_H
#define LEARN_CPP_OBJECTCREATOR_H

#include <tuple>

template <class T, class ...Params>
struct ObjectCreator
{
    template<int ...> struct Seq {};

    template<int N, int ...S>
    struct Gens : Gens<N - 1, N - 1, S...> {};

    template<int ...S>
    struct Gens<0, S...>
    {
        typedef Seq<S...> type;
    };

    static T* create(std::tuple<Params...>& params)
    {
        return createInternal(typename Gens<sizeof...(Params)>::type(), params);
    }

private:
    template<int ...S>
    static T* createInternal(Seq<S...>, std::tuple<Params...>& params)
    {
        return new T(std::get<S>(params)...);
    }
};

#endif //LEARN_CPP_OBJECTCREATOR_H
