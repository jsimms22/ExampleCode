// example following along with: https://www.youtube.com/watch?v=b6pYieNd_OY
#include <iostream>
#include <coroutine>
#include <generator>    // requires c++23
#include <utility>      // for std::exchange
#include <ranges>       // for std::views
#include "simple_logger.hpp"

std::generator<int> f()
{
    LOGF();
    int a = 0;
    int b = 1;
    co_yield a;
    while (true)
    {
        co_yield a = std::exchange(b, a+b);
    }
}

auto main() -> int
{
    LOGF();
    for (int i : f() | std::views::take(10))
    {
        LOG(i);
    }
}