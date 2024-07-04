// https://youtu.be/xGDLkt-jBJ4?si=RAX4UqGUR_i5Ex8X&t=2584

#include <iostream>
#include <memory>
#include <cassert>

class Widget 
{
    std::weak_ptr<Widget> wptr_; // = ???
    // Memory model:
    // wptr -> weak refcount
    // ctrl blk ptr -> Widget obj
public:
    std::shared_ptr<Widget> shared_from_this() const
        { return wptr_.lock(); }
};

// alternatively,

class Widget2 :
    public std::enable_shared_from_this<Widget2>
    // pulls out the weak ptr to a base class from the STL
{ };

int main()
{
    std::cout << "step 0 done\n";
    Widget2* p = new Widget2();
    std::cout << "step 1 done\n";
    assert(p->shared_from_this() == nullptr);
    std::cout << "step 2 done\n";
    std::shared_ptr<Widget2> s1(p);
    assert(p->shared_from_this() == s1);
    std::cout << "step 3 done\n";

    return 0;
}