#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

struct Season
{
    std::string_view name;
    double avgTemp;
};

int main()
{
    std::array<Season,4> season{
        { {"Spring", 285.0},
          {"Summer", 296.0},
          {"Fall", 288.0},
          {"Winter", 263.0} }
    };

    std::sort(season.begin(), season.end(), [](Season& a, Season& b) {
        return a.avgTemp < b.avgTemp;
    });

    for (const auto& s : season) { std::cout << s.name << std::endl; }

    return 0;
}