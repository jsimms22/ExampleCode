#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

bool buffer_file_loader()
{
    size_t bytes_loaded{};
    while (bytes_loaded < 20000) {
        std::cout << "Loading file...\n";
        std::this_thread::sleep_for(250ms);
        bytes_loaded += 1000;
    }
    return true;
}

int main()
{
    // Launch thread asynchronously, and execute in the background
    auto background_thread = std::async(std::launch::async, buffer_file_loader);

    // Store status of our future;
    std::future_status status{};
    // Meanwhile we have our main thread of execution
    while (true) {
        std::cout << "Main thread running\n";
        // Artificial pause
        std::this_thread::sleep_for(50ms);
        // Check if our
        status = background_thread.wait_for(1ms);
        // If our data is ready -> do something
        // we'll just terminate for now
        if (status == std::future_status::ready) {
            std::cout << "data ready...\n";
            break;
        }
    }

    return 0;
}