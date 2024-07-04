#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<int> foo()
{
    auto elts = {0,1,2,3,4};
    std::shared_ptr<std::vector<int>> pvec = std::make_shared<std::vector<int>>(elts);
    // taking advantage of shared_ptr's "aliasing constructor"
    return std::shared_ptr<int>(pvec,&(*pvec.get())[2]);
    // or return std::shared_ptr<int>(pvec,&(*pvec)[2]);

    // share ownership with pvec
    // but point to &(*pvec)[2]
    // original shared_ptr -> vec leaves scope
    // and we are left without access to the vec
}

std::shared_ptr<std::vector<int>> foo2()
{
    auto elts = {0,1,2,3,4};
    std::shared_ptr<std::vector<int>> pvec = std::make_shared<std::vector<int>>(elts);
    return pvec;
    // share ownership of pvec
}

int main()
{
    std::shared_ptr<int> ptr = foo();
    for (int i = -2; i < 3; ++i) {
        std::cout << ptr.get()[i] << std::endl;
    }
    // once ptr goes out of scope
    // ref count in control block goes to 0
    // vector gets destroyed, despite ptr only sharing ownership of an element

    std::shared_ptr<std::vector<int>> ptr2 = foo2();
    for (int i = 0; i < ptr2->size(); ++i) {
        std::cout << ptr2->data()[i] << std::endl;
    }

    return 0;
}