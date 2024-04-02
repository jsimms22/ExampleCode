#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string htmlText = "Here are some page references: pages 109-116, pp. 109-116, p. 109-116, pages A5, p.A5, (2024) ''";
    std::regex pattern1(R"(pages\s+\d+-\d+)");
    std::regex pattern2(R"(pp\.\s+\d+-\d+)");
    std::regex pattern3(R"(p\.\s+\d+-\d+)");
    std::regex pattern4(R"(pages\s+A\d+)");
    std::regex pattern5(R"(p.A\d+)");
    std::regex year_pattern(", \\(\\d{4}\\) ''"); // , (year)

    std::smatch match;

    if (std::regex_search(htmlText, match, pattern1)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    if (std::regex_search(htmlText, match, pattern2)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    if (std::regex_search(htmlText, match, pattern3)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    if (std::regex_search(htmlText, match, pattern4)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    if (std::regex_search(htmlText, match, pattern5)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    if (std::regex_search(htmlText, match, year_pattern)) {
        std::cout << "Match found: " << match.str() << std::endl;
    }

    return 0;
}