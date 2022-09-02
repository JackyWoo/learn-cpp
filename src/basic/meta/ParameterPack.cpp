//
// Created by wujianchao5 on 2022/8/11.
//

#include <tuple>
#include <iostream>

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

    static T* create(const std::tuple<Params...>& params)
    {
        return createInternal(typename Gens<sizeof...(Params)>::type(), params);
    }

private:
    template<int ...S>
    static T* createInternal(Seq<S...>, const std::tuple<Params...>& params)
    {
        return new T(std::get<S>(params)...);
    }
};

struct Handler
{
    Handler() : _p(0)
    {

    }

    explicit Handler(int p) : _p(p)
    {

    }
    int _p;
};

template <class ServiceHandler, class... Parameters>
class SocketAcceptor
{
public:
    SocketAcceptor(int socket, Parameters&&... parameters): _socket(socket), _params(std::forward_as_tuple(parameters...))
    {

    }

    ServiceHandler * accept()
    {
        return ObjectCreator<ServiceHandler, Parameters...>::create(_params);
    }

private:
    int _socket;
    std::tuple<Parameters...> _params;
};

int main()
{
    int socket = 1;
    SocketAcceptor<Handler, int> acceptor(socket, 1);
    auto * handler = acceptor.accept();
    std::cout<< handler->_p<<std::endl;

    int param = 1;
    SocketAcceptor<Handler, int&> acceptor2(socket, param);
    auto * handler2 = acceptor2.accept();
    std::cout<< handler2->_p<<std::endl;

    SocketAcceptor<Handler> acceptor3(socket);
    auto * handler3 = acceptor3.accept();
    std::cout<< handler3->_p<<std::endl;
}