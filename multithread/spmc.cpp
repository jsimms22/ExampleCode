#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> buffer;
const int MAX_SIZE = 10;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 20; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; });
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        lock.unlock();
        cv.notify_all();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });
        int data = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << data << std::endl;
        lock.unlock();
        cv.notify_all();
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}