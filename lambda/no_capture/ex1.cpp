#include <iostream>
#include <array>
#include <algorithm>
#include <string_view>

bool containsNut(std::string_view str)
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. Otherwise it returns the index where the substring occurs
    // in str.
    return str.find("nut") != std::string_view::npos;
}

int main()
{
    constexpr std::array<std::string_view, 4> arr{ "apple", "banana",
                                                   "walnut", "lemon" };

    // Scan our array to see if any elements contain the "nut" substring
    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };
    // Above function forces us to declare another function for a singular use
    if (found == arr.end()) {
        std::cout << "No nuts\n";
    } else {
        std::cout << "Found " << *found << "\n";
    }

    // lambda expressions allow us to define an anonymous function inside another function
    // [ capture clause ] ( parameters ) -> returnType
    // {
    //      statements;   
    // }

    [] {}; // a lambda with an omitted return type, no captures, and omitted paramters

    // redefine found using a lambda
    auto found{ std::find_if(arr.begin(), arr.end(), // declare lambda expression as an argument instead of function pointer
                            [](std::string_view str)
                            {
                                return str.find("nut") != std::string_view::npos;
                            })};
    // lambdas in this use case provide several advantages:
    // -> lambdas are both const and constexpr (provides opportunity for compile time optmizations)
    // -> avoids muddying our namespace and reduce scope
    // -> avoids the use of unnecessary function pointers, slow
    // con: defining the lamdba in the same line it is used could be hard to read

    // consider...

    // return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });

    // we have to read the lamdba to make sense of the purpose

    auto isEven{
        [](int i)
        {
            return (i % 2) == 0;
        }
    };

    // return std::all_of(array.begin(), array.end(), isEven);

    

    return 0;
}