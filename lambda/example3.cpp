// generic lambdas

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main()
{
    constexpr std::array months {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                            [](const auto& a, const auto& b) {
                                return a[0] == b[0];
                            }) };

    // Make sure that two months were found
    if (sameLetter != months.end())
    {
        // std::next returns the next iterator after sameLetter
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
                  << " start with the same letter\n";
    }

    const auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                [](std::string_view str) {
                                    return str.length() == 5;
                                }) };

    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";


    // since c++17 lambdas can be constexpr, if:
    // -> no captures, or all captures are constexpr
    // -> functions called by the lamdba must be constexpr
    // note: much of the std library was not made constexpr until c++20

    // valid for c++20 or newer
    /*
    constexpr auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                    [](std::string_view str) {
                                        return str.length() == 5;
                                    })}
    */

    
    return 0;
}