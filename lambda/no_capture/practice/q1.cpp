#include <iostream>
#include <string>
#include <algorithm>
#include <array>

struct Student
{
    std::string name;
    int points;
};

int main()
{
    constexpr auto max { [](Student& a, Student& b) -> bool {
            return a.points > b.points;
        } };

    std::array<Student, 8> arr{
    {   { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 }     }
    };

    const auto best { std::max_element(arr.begin(), arr.end(), max) };
    
    std::cout << best->name << " is the best student\n";

    return 0;
}