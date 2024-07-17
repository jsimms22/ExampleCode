#include <thread>
#include <vector>
#include <atomic>
#include <vector>

constexpr size_t N = 100;
int q[N];
std::atomic<size_t> front{0};

void push(int x) {
    // an atomic front is used as an index
    // to non-atomic memory
    size_t my_slot = front.fetch_add(1);
    q[my_slot] = x; // exclusive slot
    // this does not fully work
    // very small example
}