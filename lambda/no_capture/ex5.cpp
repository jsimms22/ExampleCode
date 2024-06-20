// returning type deduction and trailing return types

#include <iostream>

int main()
{
    auto divide{ [](int x, int y, bool intDivision) -> double {
        if (intDivision)
            return x/y;
        else
            // will cause error unless we provide a trailing return type
            // return type deduction
            return static_cast<double>(x) / y;
    }};
}