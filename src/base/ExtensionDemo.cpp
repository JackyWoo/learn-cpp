//
// Created by wujianchao5 on 2025/2/12.
//

#include "ExtensionDemo.h"

int Base::foo() {
    return 1;
}
int D1::foo() {
    return 1;
}
int D2::foo() {
    return 1;
}
int D3::foo() {
    return 1;
}

class B
{
public:
    virtual void updateTreeHash()
    {
        updateTreeHashIml();
        std::cout << "B::updateTreeHash" << std::endl;
    }

    virtual void updateTreeHashIml()
    {
        std::cout << "B::updateTreeHashIml" << std::endl;
    }
};

class D : public B
{
public:
    void updateTreeHash()
    {
        std::cout << "D::updateTreeHash" << std::endl;
        B::updateTreeHash();
    }

    void updateTreeHashIml()
    {
        std::cout << "D::updateTreeHashIml" << std::endl;
    }
};

int main()
{
    Base * d3 = new D3();
    Base * d1 = new D1();
    auto * d11 = dynamic_cast<D1 *>(d1);
    std::cout << d11->c1 << std::endl;
    std::cout << d3->c1 << std::endl;

    D d;
    d.updateTreeHash();
}
