#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
    // modifying ../no capture/ex1.cpp
    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    std::cout << "search for: ";
    std::string search{};
    std::cin >> search;

    auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
        // search for @search rather than nut
        // an enclosing fn local variable cannot be referenced in a lambda
        // body unless it is in the capture list
        return str.find(search) != std::string_view::npos;
    })};

    if (found == arr.end()) {
        std::cout << "not found\n";
    } else {
        std::cout << "found " << *found << '\n';
    }

    // lambdas can only access certain kinds of object that have been defined outside the lambda
    // this includes:
    // -> objects with static (or thread local) storage duration
    // -> objects that are constexpr (explicitly or implicitly)

    return 0;
}