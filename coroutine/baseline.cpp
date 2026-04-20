// example following along with: https://www.youtube.com/watch?v=b6pYieNd_OY

#include <iostream>
#include <coroutine>

struct Task
{
    struct promise_type
    {
        auto get_return_object() { return Task(); }
        // or std::suspend_always
        auto initial_suspend() { return std::suspend_never{}; }
        // or std:::suspend_neve, but usually...
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { /* error handling */ std::abort(); }
        void return_void() {}
    };
};

Task f()
{
    co_return;
}

auto main() -> int
{
    f();
}