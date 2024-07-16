#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std::chrono_literals;

auto func = [](std::mutex& my_lock) {
                int counter{0};
                auto thread_id = std::this_thread::get_id();
                while (counter < 5) {
                    std::this_thread::sleep_for(0.2s);
                    ++counter;
                }
                my_lock.lock();                                 // identify critical section begin
                std::cout << "Thread id: " << thread_id
                          << "; counter: " << counter << '\n';
                my_lock.unlock();                               // identify critical section end
                                                                // if thread never returns lock to unlocked state we get a deadlock
                                                                // potential issue might be resolved by using a lock guard
            };

int main()
{
    std::cout << "\nmutex lock - thread example:\n";

    std::mutex my_lock{};
    std::vector<std::thread> vecThreads(10);
    for (auto& thr : vecThreads) { thr = std::thread(func,std::ref(my_lock)); } // start execution of operation func2
                                                                                // must use std::ref() to pass object by reference to lambda
    for (auto& thr : vecThreads) { thr.join(); }                                // waits for each thread to finish operation func2 before continuing
                                                                                // threads do not auto call join() and require it manually called
    
    std::cout << '\n';

    return 0;
}