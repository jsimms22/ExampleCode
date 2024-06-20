// std library function objects

#include <algorithm>
#include <array>
#include <iostream>
// callable functions
#include <functional>

bool greater(int a, int b)
{
    return a > b;
}

int main()
{
    std::array arr{ 13, 90, 99, 5, 40, 80 };

    // pass greater to std::sort
    std::sort(arr.begin(), arr.end(), greater);

    for (int i : arr) { std::cout << i << ' '; }

    std::cout << '\n';

    // std::functional provides us many callable objects
    // not also required to create our own
    std::sort(arr.begin(), arr.end(), std::greater{});

    return 0;
}