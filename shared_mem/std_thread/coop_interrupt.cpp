// requires -std=c++20 for jthread
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std::chrono_literals;

std::mutex my_lock;

auto func = [](std::stop_token stoken) {
                int counter{0};
                auto thread_id = std::this_thread::get_id();

                // identify call back op if our stop_token is given
                std::stop_callback callBack(stoken, [&counter,thread_id]() {
                    std::cout << "Thread id: " << thread_id
                              << "; counter: " << counter << '\n';
                });

                // execute loop until main thread calls join()
                while (counter < 20) {
                    std::this_thread::sleep_for(0.2s);
                    ++counter;
                }
            };



auto sleep = []() { std::this_thread::sleep_for(1s); };

int main()
{
    std::cout << "\ncoop interrupt - jthread example:\n";
    std::vector<std::jthread> vecThreads(10);
    for (auto& thr : vecThreads) { thr = std::jthread(func); }  // start execution of operation func
    std::this_thread::sleep_for(2s);                            // main thread sleep
                                                                // main thread will enter loop and stop each thread mid-operation (if still executing)
    for (auto& thr : vecThreads) { thr.request_stop(); }        // causes interrupt of current operation, executes stop_callback lambda
                                                                // jthreads call join() in their destructor and will persist until destroyed

    std::cout << '\n';

    std::cout << "size of jthread: " << sizeof(std::jthread) << "\n";
    std::cout << "size of thread: " << sizeof(std::thread) << "\n";

    std::cout << '\n';

    return 0;
}