// example following along with: https://www.youtube.com/watch?v=b6pYieNd_OY
#include <iostream>
#include <coroutine>
#include "simple_logger.hpp"

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
            return std::suspend_never{}; 
        }

        // or std:::suspend_never, but usually...
        auto final_suspend() noexcept 
        {
            LOGF();
            // if we make it suspend_never here then the coroutine handles its own clean up
            // be careful of a double delete or losing access to a return value from our handle
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

        int returned_value;
    };

    std::coroutine_handle<promise_type> handle;

    ~Task() 
    {
        if (handle) { handle.destroy(); }
    }
    
    // we can get promises from handles
    int get_return_value() const { return handle.promise().returned_value; }
};

Task f()
{
    LOGF();
    co_return 42;
}

auto main() -> int
{
    LOGF();
    auto task = f();
    LOG(task.get_return_value());
}