// example following along with: https://www.youtube.com/watch?v=b6pYieNd_OY
#include <iostream>
#include <coroutine>
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
            // we can get a handle from a promise
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
            // if we make it suspend_never here then the coroutine handles its own clean up
            // be careful of a double delete or losing access to a return value from our handle

            // almost always, suspend_always
            return std::suspend_always{}; 
        }

        void unhandled_exception() 
        {
            LOGF(); 
            /* error handling */
            std::abort(); 
        }

        // void return_void() 
        void return_value(auto value)
        {
            LOGF();
            // store our return
            returned_value = value;
        }

        // this does return a value
        auto yield_value(auto value)
        {
            LOGF();
            // almost always, suspend_always
            yielded_value = value;
            return std::suspend_always();
        }

        int returned_value;
        int yielded_value;
    };

    std::coroutine_handle<promise_type> handle;

    ~Task() 
    {
        if (handle) { handle.destroy(); }
    }
    
    // we can get promises from handles
    int get_returned_value() const 
    { 
        return handle.promise().returned_value;
    }

    // we can get promises from handles
    int get_yielded_value() const 
    { 
        return handle.promise().yielded_value;
    }

    // void resume()
    bool resume()
    {
        handle.resume();
        return handle.done();
    }
};

Task f()
{
    LOGF();
    co_yield 1;
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_yield 5;
    co_return 42;
}

auto main() -> int
{
    LOGF();
    auto task = f();

    while (!task.resume())
    {
        LOG(task.get_yielded_value());
    }

    LOG(task.get_returned_value());
}