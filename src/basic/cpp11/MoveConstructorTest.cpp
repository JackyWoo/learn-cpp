//
// Created by wujianchao5 on 2020/12/21.
//

#include <iostream>

using namespace std;

class Foo
{
public:
    std::string name;
    Foo() { cout << "call default constructor\n"; }
    Foo(const Foo & foo) : name(foo.name) { cout << "call copy constructor\n"; }
    //    Foo(Foo && foo) : name(std::move(foo.name)) { cout << "call move constructor\n"; }
    ~Foo() { cout << "class destroy" << endl; }
};

Foo getFoo()
{
    Foo f;
    return f; // NRVO
    // return Foo(); // RVO
}

void useFoo(Foo foo)
{
}

int main()
{
    /**
     * 使用命令可以去掉编译器优化：
     *      clang++ MoveConstructorTest.cpp -std=c++11 -fno-elide-constructors
     *
     * 运行程序：./a.out，结果如下：
     *      default constructor         <-- 执行 Foo()
     *      call copy constructor       <-- 执行 return Foo()
     *      class destroy               <-- 销毁 Foo() 产生的匿名对象
     *      call copy constructor       <-- 执行 a = getFoo()
     *      class destroy               <-- 销毁 getFoo() 返回的临时对象
     *      class destroy               <-- 销毁 a
     *
     *
     * 中间会产生两次临时变量的开销
     */
    {
        cout << "getFoo()" << endl;
        Foo a = getFoo();
    }

    /**
     * 事实上，对于程序执行过程中产生的临时对象，往往只用于传递数据（没有其它的用处），并且会很快会被销毁。
     * 因此在使用临时对象初始化新对象时，我们可以将其包含的指针成员指向的内存资源直接移给新对象所有，无需
     * 再新拷贝一份，这大大提高了初始化的执行效率。
     *
     * C++11引入了移动语义，它避免了临时的拷贝，移动语义需要被移动数据有移动构造函数，添加移动构造函数后，使用如下命令进行编译
     *      clang++ MoveConstructorTest.cpp -std=c++11 -fno-elide-constructors
     *
     * 此时执行流程为：
            call default constructor        <-- 执行 Foo()
            call move constructor           <-- 执行 return Foo()，这里避免了name的数据拷贝
            class destroy                   <-- 销毁 Foo() 产生的匿名对象
            call move constructor           <-- 执行 a = getFoo()，这里避免了name的数据拷贝
            class destroy                   <-- 销毁 getFoo() 返回的临时对象
            class destroy                   <-- 销毁 a
     */

    /**
     * 虽然移动语义避免了一些数据拷贝，但是依然会创建2个临时对象，这里还可以进一步优化。
     * C++17引入了copy elision语义，它会忽略拷贝和构造函数，实现zero-copy语义。
     * 参考：https://en.cppreference.com/w/cpp/language/copy_elision
     *
     * 编译程序：
     *      clang++ MoveConstructorTest.cpp -std=c++17 -fno-elide-constructors
     *
     * 执行流程：
            call default constructor    <-- 执行 Foo() 并直接用其初始化a
            class destroy               <-- 销毁 a
     */


    {
        cout << endl;
        cout << "useFoo()" << endl;
        useFoo(Foo());

        // c++03
        //            call default constructor  <-- 执行 Foo()
        //            call copy constructor     <-- 使用 Foo()产生的临时对象初始化变量foo
        //            class destroy             <-- 销毁 Foo()产生的临时对象
        //            class destroy             <-- 销毁 foo
        // c++11
        //            call default constructor  <-- 执行 Foo()
        //            call move constructor     <-- 使用 Foo()产生的临时对象初始化变量foo
        //            class destroy             <-- 销毁 Foo()产生的临时对象
        //            class destroy             <-- 销毁 foo
        // c++17
        //            call default constructor  <-- 执行 Foo()，并量直接使用其初始化foo
        //            class destroy             <-- 销毁 foo
    }

    /// 结论：c++ 是一种极度灵活的高级语言，它开放了大量的特性给开发人员，以便可以编写高性能的程序，
    /// 但是这种思路导致了程序开发的复杂性。为此C++在持续优化语言，帮助开发人员尽可能简单的开发出高
    /// 性能的程序。
}