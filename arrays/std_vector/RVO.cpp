// SAMPLE OUTPUT:
// f1 took 5ms
// f2 took 7414ms
// f3 took 7040ms
// f4 took 3056ms

// verifying return value optimization as discussed from:
// https://youtu.be/fHNmRkzxHWs?si=jVsllj9FPZ-7Rl2v&t=1909
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

struct DATA { int data; };

std::vector<DATA> f1(int n)
{
    std::vector<DATA> result;
    result.reserve(n);
    for (auto i : result) { i = DATA{rand() % 5}; }
    return result;
}

std::vector<DATA> f2(int n)
{
    std::vector<DATA> result;
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5}); }
    return result;
}

void f3(int n, std::vector<DATA>& result)
{
    result.reserve(n);
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5}); }
}

void f4(int n, DATA* result)
{
    for (int i = 0; i < n; ++i) { result[i] = DATA{rand() % 5}; }
}

int main()
{
    srand(0);
    std::vector<DATA> capture1;
    auto start = std::chrono::high_resolution_clock::now();
    capture1 = f1(5000000);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f1 took " << duration.count() << "ms\n";

    std::vector<DATA> capture2;
    start = std::chrono::high_resolution_clock::now();
    capture2 = f2(5000000);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f2 took " << duration.count() << "ms\n";

    std::vector<DATA> capture3;
    start = std::chrono::high_resolution_clock::now();
    f3(5000000,capture3);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f3 took " << duration.count() << "ms\n";

    std::vector<DATA> capture4;
    start = std::chrono::high_resolution_clock::now();
    capture4.reserve(5000000);
    f4(500000,capture4.data());
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f4 took " << duration.count() << "ms\n";
    return 0;
}