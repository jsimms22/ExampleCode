// Passing lambdas to a function
#include <functional>
#include <iostream>

// Case 1: use a std::function paramter
void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{0}; i<repetitions; ++i) 
        fn(i);
}

// Case 2: use a function template ith a type template paramter
template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for (int i{0}; i<repetitions; ++i)
        fn(i);
}

// Case 3: use the abbreviated function template syntax (C++20 or newer)
void repeat3(int repetitions, const auto& fn)
{
    for (int i{0}; i<repetitions; ++i)
        fn(i);
}

// Case 4: use function pointer (only for lambda with no captures)
void repeat4(int repetitions, void(*fn)(int))
{
    for (int i{0}; i<repetitions; ++i)
        fn(i);
}

int main()
{
    // when storing a lambda in a variable, use auto
    auto lambda = [](int i)
    {
        std::cout << i << "\n";
    };

    // when passing to a function
    // use auto as the parameter's type (c++20)
    // otherwise with a type template or std::function
    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    return 0;
}