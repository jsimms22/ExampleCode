#include <iostream>
#include <memory>
#include <functional>
#include "shared_ptr3.h"

struct D // deleter functor
{
    D() = default;
    D(const D&) { std::cout << "D copy ctor.\n"; }
    D(D&) { std::cout << "D non-const copy ctor.\n"; }
    D(D&&) { std::cout << "D move ctor.\n"; }
    void operator()(Foo* p) const
    {
        std::cout << "D is deleting a c-style heap-allocated Foo.\n";
        destroyObj(p);
    }
};

int main()
{
    D destructor;
    // unique_ptr must know the type of the custom deleter
    std::unique_ptr<Foo,D> u_ptr(createObj(5,10.1),destructor);
    // shared_ptr has a typed erased deleter, so simply pass to the constructor
    // std::shared_ptr<Foo> s_ptr(createObj(5,10.1),destructor);

    return 0;
}