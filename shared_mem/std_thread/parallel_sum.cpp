// Only efficient for when N is large
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <atomic>

// lock surrounding our main summation calculation
std::atomic<unsigned long> sum1{0};
void do_work1(size_t N, unsigned long* a)
{
    for (size_t i = 0; i < N; ++i) { sum1 += a[i]; }
}

// no lock surrounding our main summation calculation
unsigned long sum2{0};
std::mutex my_lock;
void do_work2(size_t N, unsigned long* a)
{
    unsigned long s{0};
    for (size_t i = 0; i < N; ++i) { s += a[i]; }
    std::scoped_lock<std::mutex> L(my_lock);
    sum2 += s;
}

main()
{
    srand(0);
    size_t N{100000};
    std::vector<unsigned long> a(N);
    for (auto& i : a) { i = rand() % 10; }

    for (size_t itr = 0; itr <= 16; ++itr)
    {
        std::cout << "\nStarting new loop: " << itr << std::endl;

        std::vector<std::thread> threadBin(itr);
        auto startTime = std::chrono::high_resolution_clock::now();
        for (auto& thr : threadBin) { thr = std::thread(do_work1,N,a.data()); }
        for (auto& thr : threadBin) { thr.join(); }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        std::cout << "sum1 = " << sum1 << std::endl;
        std::cout << "Time taken: " << duration.count() << " us" << std::endl;
        sum1 = 0;

        startTime = std::chrono::high_resolution_clock::now();
        for (auto& thr : threadBin) { thr = std::thread(do_work2,N,a.data()); }
        for (auto& thr : threadBin) { thr.join(); }
        endTime = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

        std::cout << "sum2 = " << sum2 << std::endl;
        std::cout << "Time taken: " << duration.count() << " us" << std::endl;
        sum2 = 0;

        std::cout << "Ending loop: " << itr << std::endl;
    }

    return 0;
}