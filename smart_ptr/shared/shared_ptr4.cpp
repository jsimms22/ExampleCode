#include <iostream>
#include <memory>

void do_something(int* ptr)
{
    std::cout << "\n--doing something with raw pointers--\n";
    std::cout << ptr << " has value " << *ptr << std::endl;
    // delete(ptr); // crashes with error code
    ptr+=sizeof(int);
    std::cout << ptr << std::endl;
    std::cout << "--exiting--\n";
}

void do_something_ref(int& ptr)
{
    std::cout << "\n--doing something with pass by ref--\n";
    std::cout << ptr << " has value " << &ptr << std::endl;
    // delete(ptr); // crashes with error code
    ptr+=sizeof(int);
    std::cout << ptr << " has value " << &ptr << std::endl;
    std::cout << "--exiting--\n";
}

void do_something(std::shared_ptr<int> ptr)
{   // makes a copy of shared_ptr, and shares ownership
    std::cout << "\n--doing something with smart pointers--\n";
    std::cout << "owner count: " << ptr.use_count() << std::endl;
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    ptr.reset(new int(2));
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    std::cout << "--exiting--\n";
}

void do_something_ref(std::shared_ptr<int>& ptr)
{   // does not make a copy of our shared_ptr, and has full, mutable control
    std::cout << "\n--doing something with ref smart pointers--\n";
    std::cout << "owner count: " << ptr.use_count() << std::endl;
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    ptr.reset(new int(2));
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    std::cout << "--exiting--\n";
}

void do_something_const_ref(const std::shared_ptr<int>& ptr)
{   // does not make a copy of our shared_ptr, and has non-mutable control
    std::cout << "\n--doing something with ref smart pointers--\n";
    std::cout << "owner count: " << ptr.use_count() << std::endl;
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    // ptr.reset(); // error: attempts to change the ptr
    std::cout << ptr.get() << " has value " << *ptr << std::endl;
    std::cout << "--exiting--\n";
}

int main()
{
    auto test_ptr = std::make_shared<int>(1);

    std::cout << test_ptr.get() << " has value " << *test_ptr << std::endl;
    do_something(test_ptr.get());
    // do_something_ref(&test_ptr.get()); // error: not an l-value
    // std::cout << '\n' << test_ptr.get() << std::endl;   
    do_something(test_ptr);
    std::cout << '\n' << test_ptr.get() << " has value " << *test_ptr << std::endl;
    // do_something_const_ref(test_ptr); // error: not mutable
    // std::cout << '\n' << test_ptr.get() << std::endl;    
    do_something_ref(test_ptr);
    std::cout << '\n' << test_ptr.get() << " has value " << *test_ptr << std::endl;
}