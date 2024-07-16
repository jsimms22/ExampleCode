// requires -std=c++17 for scoped lock
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std::chrono_literals;

auto func = [](std::mutex& my_lock1, std::mutex& my_lock2) {
                int counter{0};
                auto thread_id = std::this_thread::get_id();
                while (counter < 5) {
                    std::this_thread::sleep_for(0.2s);
                    ++counter;
                }
                std::scoped_lock my_scoped_lock(my_lock1, my_lock2);    // identify critical section begin
                                                                        // prefer scoped_lock to lock_guard if able to use c++17+
                                                                        // scoped lock can handle more than one lock
                std::cout << "Thread id: " << thread_id
                          << "; counter: " << counter << '\n';
            };                                                          // scoped lock will unlock my_lock1 + my_lock2 when it leaves scope
                                                                        // avoid potential issues with lock never being returned by a thread

int main()
{
    std::cout << "\nscope lock - thread example:\n";

    std::mutex my_lock1{}, my_lock2{};
    std::vector<std::thread> vecThreads(10);
    for (auto& thr : vecThreads) { 
        thr = std::thread(func,std::ref(my_lock1),std::ref(my_lock2));  // start execution of operation func
    } 
                                                                        // must use std::ref() to pass object by reference to lambda
    for (auto& thr : vecThreads) { thr.join(); }                        // waits for each thread to finish operation func before continuing
                                                                        // threads do not auto call join() and require it manually called

    std::cout << '\n';

    return 0;
}