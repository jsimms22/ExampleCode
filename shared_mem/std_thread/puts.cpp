#include <iostream>
#include <thread>

int main()
{
    std::thread thread_b = std::thread([]() {
        std::puts("Hello frome threadB!");
        // std::cout << "Hello from thread: " << std::this_thread::get_id() << '\n';
    });
    std::puts("Hello from threadA!");
    // std::cout << "Hello from thread: " << std::this_thread::get_id() << '\n';

    thread_b.join();

    return 0;
}