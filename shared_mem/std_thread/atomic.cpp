#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

static std::atomic<long long int> my_atomic{};
static std::mutex my_lock{};

auto func = []() {
                auto my_id = std::hash<std::thread::id>{}(std::this_thread::get_id());  // get size_t value for thread id
                {
                    std::scoped_lock slock(my_lock);
                    std::cout << "my id: " << my_id << '\n';
                }
                my_atomic = (my_id % 2) == 0 ? (my_atomic+my_id) : (my_atomic-my_id);   // object is atomic
            };

int main()
{
    std::cout << "\natomic count - thread example:\n";

    std::vector<std::thread> vecThreads(10);
    for (auto& thr : vecThreads) { thr = std::thread(func); }   // start execution of operation func                            
    for (auto& thr : vecThreads) { thr.join(); }                // waits for each thread to finish operation func before continuing
                                                                // threads do not auto call join() and require it manually called
    std::cout << "count value: " << my_atomic << '\n';

    std::cout << '\n';

    return 0;
}