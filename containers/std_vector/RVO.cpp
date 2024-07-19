// g++ .\RVO.cpp -o RVO -O0
// SAMPLE OUTPUT:
// f2 took 7140ms
// f3 took 7335ms
// f4 took 7080ms
// f6 took 7560ms

// g++ .\RVO.cpp -o RVO -O1
// f2 took 3464ms
// f3 took 3804ms
// f4 took 3319ms
// f6 took 3747ms

// diving into this topic:
// https://youtu.be/fHNmRkzxHWs?si=jVsllj9FPZ-7Rl2v&t=1909

//RVO or NVRO (for named returns) is an easy optimization for the compiler to do
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

struct DATA { int data; };

// vector ends up being size 0
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
    result.reserve(n);
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5}); }
    return result;
}

std::vector<DATA> f3(int n)
{
    std::vector<DATA> result;
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5}); }
    return result;
}

void f4(int n, std::vector<DATA>& result)
{
    result.reserve(n);
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5}); }
}

// vector ends up being size 0
// void f5(int n, std::vector<DATA>& result)
// {
//     result.reserve(n);
//     for (auto i : result) { i = DATA{rand() % 5};  }
// }

void f6(int n, std::vector<DATA>& result)
{
    for (int i = 0; i < n; ++i) { result.push_back(DATA{rand() % 5});  }
}

// bad, vector ends up being size 0 
// and doesn't actually encapsulate the memory you wrote to
// void f6(int n, DATA* result)
// {
//     for (int i = 0; i < n; ++i) { result[i] = DATA{rand() % 5}; }
// }

int main()
{
    srand(0);
    constexpr int N = 500000;

    // vector is size 0
    // std::vector<DATA> capture1;
    // auto start = std::chrono::high_resolution_clock::now();
    // capture1 = f1(N);
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << "f1 took " << duration.count() << "ms\n";
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    int warm_up{};
    for (int i = 0; i < N; ++i) {
        warm_up += i;
    }

    std::vector<DATA> capture2;
    start = std::chrono::high_resolution_clock::now();
    capture2 = f2(N);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f2 took " << duration.count() << "ms\n";

    std::vector<DATA> capture3;
    start = std::chrono::high_resolution_clock::now();
    capture3 = f3(N);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f3 took " << duration.count() << "ms\n";

    std::vector<DATA> capture4;
    start = std::chrono::high_resolution_clock::now();
    f4(N,capture4);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f4 took " << duration.count() << "ms\n";

    // vector is size 0
    // std::vector<DATA> capture5;
    // start = std::chrono::high_resolution_clock::now();
    // f5(N,capture5);
    // end = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << capture6.size() << '\n';
    // std::cout << capture6[450000].data << '\n';
    // for (auto i : capture6) { std::cout << i.data << '\n'; }
    // std::cout << "f5 took " << duration.count() << "ms\n";

    std::vector<DATA> capture6;
    start = std::chrono::high_resolution_clock::now();
    f6(500000,capture6);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "f6 took " << duration.count() << "ms\n";

    return 0;
}