#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> ptr(new int(5));
    //equivalent to:
    auto ptr2 = std::make_shared<int>(5); // hides the new for us

    return 0;
}