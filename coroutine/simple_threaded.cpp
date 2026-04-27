// example following along with: https://www.youtube.com/watch?v=b6pYieNd_OY
#include <iostream>
#include <coroutine>
#include <generator>    // requires c++23
#include <utility>      // for std::exchange
#include <ranges>       // for std::views
#include <thread>      // for std::jthread
#include <print>        // for std::print

#include "simple_logger.hpp"

// We as programmer need to determine our interface to our coroutine type
// C++20 example, C++26 has std::generators to avoid as much boilerplate
struct Task
{
    struct promise_type
    {
        auto get_return_object() 
        {
            LOGF();
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }

        // or std::suspend_never
        auto initial_suspend() 
        {
            LOGF(); 
            return std::suspend_always{}; 
        }

        // or std:::suspend_never, but usually...
        auto final_suspend() noexcept 
        {
            LOGF();
            return std::suspend_always{}; 
        }

        void unhandled_exception() 
        {
            LOGF();
        }

        void return_value(auto value)
        {
            LOGF();
            completed = true;
            final_value = value;
        }

        int final_value;
        bool completed = false;
    };

    std::coroutine_handle<promise_type> handle;

    ~Task() { if (handle) { handle.destroy(); } }

    // we can get promises from handles
    int get_returned_value() const 
    { 
        return handle.promise().final_value;
    }

    // void resume()
    bool resume()
    {
        handle.resume();
        return handle.done();
    }

    bool is_done()
    {
        return handle.promise().completed;
    }
};

Task fake_gpu()
{
    int a = 0;
    int b = 1;
    { /* imagine this some just some tasks generated for the gpu */
        while (true)
        {
            a = std::exchange(b, a+b);
            if (a > 1000000) break;
        }
    }

    co_return a;
}

int cpu()
{
    int a = 0;
    int b = 1;
    while (true)
    {
        a = std::exchange(b, a+b);
        if (a > 10) { return a; }
    }
}

auto main() -> int
{
    LOGF();

    auto gpu = fake_gpu();
    std::jthread worker1([h = gpu.handle]() 
    {
        if (h && !h.done()) {
            h.resume();
        }
    });
    
    auto ret = cpu();
    LOG("Finished cpu");
    LOG(ret);

    while (!gpu.is_done()) 
    {
        gpu.resume();
    }
    
    ret = gpu.get_returned_value();

    LOG("Finished gpu");
    LOG(ret);
}