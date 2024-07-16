#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex my_lock{};   // global lock
std::condition_variable my_condition_var{};

int main()
{
    std::cout << "main() starts\n";

    int result{};
    bool notified{false};
    // This thread reports the result (consumes the result)
    // Could call this a "consumer" or "reporter" thread
    std::thread reporter([&](){
        // unique_lock has a level of ownership that makes 
        // it more powerful than a scoped or guard lock
        std::unique_lock<std::mutex> u_lock(my_lock);
        if (!notified) { my_condition_var.wait(u_lock); }
        std::cout << "\treporter result = " << result << std::endl;
    });

    // This thread does the work
    std::thread worker([&]() {
        std::unique_lock<std::mutex> u_lock(my_lock);
        // Do our work
        result = 42;
        // Update our condition
        notified = true;
        // Artificial paus to show our reporter will indeed wait
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Output a message
        std::cout << "\twork complete" << std::endl;
        // Notify one thread about a change
        // Could also notify_all
        my_condition_var.notify_one();
    });

    // Don't forget to call join for non-jthreads
    reporter.join();
    worker.join();
    std::cout << "main end" << std::endl;
    return 0;
};