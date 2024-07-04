#include <iostream>
#include <memory>

struct Foo
{
    int m_data;
    Foo() { }
    Foo(int value) :m_data{value} { std::cout << "calling constructor\n"; }
    ~Foo() { std::cout << "Destroyed Foo with data: "
                       << this->m_data << std::endl; }
};

struct Point
{
    int x; int y;
    Point(int _x, int _y) :x{_x}, y{_y} { }
    ~Point() { std::cout << "Destroyed Point with data: "
                        << this->x << ", "
                        << this->y << std::endl; }
};

// Memory model: 
// ptr -> Foo
// reset ptr
// ptr -> 
// ref count goes to 0
// invoke deletion of Foo
int main()
{
    // single owner of Foo example
    std::cout << "\nsingle shared owner\n";
    std::shared_ptr<Foo> ptr = std::make_shared<Foo>(1);
    std::cout << "ptrs to foo: " << ptr.use_count() << std::endl;
    ptr.reset();
    std::cout << "reset our ptr, current ref count: " << ptr.use_count() << std::endl;

    // multiple owners of Foo example
    std::cout << "\nmultiple shared owners\n";
    ptr = std::make_shared<Foo>(2);
    std::cout << "ptrs to foo: " << ptr.use_count() << std::endl;
    std::shared_ptr<Foo> ptr2 = ptr;
    std::shared_ptr<Foo> ptr3 = ptr;
    std::cout << "expanding ownership of Foo, current ref count: " << ptr2.use_count() << std::endl;
    ptr.reset();
    std::cout << "reset ptr, current ref count: " << ptr2.use_count() << std::endl;
    ptr2.reset();
    std::cout << "reset ptr2, current ref count: " << ptr3.use_count() << std::endl;

    // single owner, swap owned object to different Foo
    std::cout << "\nsingle shared owner, and object swap with another ptr\n";
    std::shared_ptr<Foo> ptr4 = std::make_shared<Foo>(3);
    std::shared_ptr<Foo> ptr5 = nullptr;
    std::cout << "ptrs to foo: " << ptr4.use_count() << std::endl;
    ptr4.swap(ptr5);
    std::cout << "swap our ptr4 to ptr5 (nullptr): " << ptr4.use_count() << std::endl;
    std::cout << "ref count for owners of Foo handled atomically\n";

    // using make_shared with multiple inputs for Foo
    std::cout << "\nsingle shared owner, and object with 2 inputs\n";
    std::shared_ptr<Point> ptr6 = std::make_shared<Point>(3,4);

    std::cout << "\nexiting\n";
    return 0;
}