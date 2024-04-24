//
// Created by wujianchao5 on 2024/2/2.
//

#include <iostream>

/// Test dispatch by target

__attribute__ ((target ("default")))
int foo ()
{
    // The default version of foo.
    return 0;
}

__attribute__ ((target ("sse4.2")))
int foo ()
{
    // foo version for SSE4.2
    return 1;
}

__attribute__ ((target ("sse4.2")))
int foo ()
{
    // foo version for the AMD Family 0x10 processors.
    return 3;
}

int main ()
{
    int (*p)() = &foo;
//    assert ((*p) () == foo ());
    std::cout << foo() << std::endl;
    return 0;
}
