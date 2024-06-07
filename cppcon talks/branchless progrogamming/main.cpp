/* Branchless Programming in C++ - Fedor Pikus - CppCon 2021 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <type_traits>
#include <tuple>
// SIMD libraries
#include <mmintrin.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <emmintrin.h>

// constexpr size_t LENGTH = 8;

void fill_matrix(size_t LENGTH, std::vector<bool>& v);

template <typename UNIT>
void fill_matrix(size_t LENGTH, const UNIT ALPHA, std::vector<UNIT>& v);

template <typename UNIT>
void naiveVVM(UNIT& a, std::vector<UNIT>& v1, std::vector<UNIT>& v2, std::vector<bool>& v3);

template <typename UNIT>
void unrolledVVM(UNIT& a, std::vector<UNIT> &v1, std::vector<UNIT> &v2, std::vector<bool>& v3);

template <typename UNIT>
void pipelineVVM(UNIT& a, std::vector<UNIT> &v1, std::vector<UNIT> &v2, std::vector<bool> &v3);

int main(int argc, char* argv[]) 
{
    if (argc != 2) { return 1; }
    size_t LENGTH = std::stoi(argv[1]);
    float a = 0.0f;
    std::vector<float> b, c;
    std::vector<bool> d;
    fill_matrix(LENGTH, 1.0f, b);
    fill_matrix(LENGTH, 1.0f, c);
    fill_matrix(LENGTH, d);

    std::cout << "Beginning naiveVVM" << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    naiveVVM(a,b,c,d);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "solution from function naiveVVM: " << a << std::endl;
    std::cout << "Time taken by function: " << duration.count() << " ns" << std::endl;

    std::cout << std::endl;

    std::cout << "Beginning unrolledVVM" << std::endl;
    startTime = std::chrono::high_resolution_clock::now();
    unrolledVVM(a,b,c,d);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "solution from function unrolledVVM: " << a << std::endl;
    std::cout << "Time taken by function: " << duration.count() << " ns" << std::endl;

    std::cout << std::endl;

    std::cout << "Beginning pipelineVVM" << std::endl;
    startTime = std::chrono::high_resolution_clock::now();
    pipelineVVM(a,b,c,d);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "solution from function pipelineVVM: " << a << std::endl;
    std::cout << "Time taken by function: " << duration.count() << " ns" << std::endl;

}

void fill_matrix(size_t LENGTH, std::vector<bool>& v) 
{
    srand(0);
    for(std::size_t i = 0; i < LENGTH; ++i) {
        // rand() >= 0, ensures we do not solve at compile time
        v.push_back(rand() >= 0);
    }
}

template <typename UNIT>
void fill_matrix(size_t LENGTH, const UNIT ALPHA, std::vector<UNIT>& v) 
{
    for(std::size_t i = 0; i < LENGTH; ++i) {
        v.push_back(ALPHA*(rand() % 10));
    }
}

template <typename UNIT>
void naiveVVM(UNIT& a, std::vector<UNIT> &v1, std::vector<UNIT> &v2, std::vector<bool> &v3)
// inefficient use of the cpu, it can handle more instructions simultaneously
{
    a = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        if (v3[i]) {
            a += v1[i]*v2[i];
        }
    }
}

template <typename UNIT>
void unrolledVVM(UNIT& a, std::vector<UNIT> &v1, std::vector<UNIT> &v2, std::vector<bool> &v3)
// ~2x increase of naive, loop unrolling, potential data dependencies
{
    a = 0.0; UNIT a1 = 0; UNIT a2 = 0; size_t i = 0;
    size_t unrolled_itr = 2; // could be a function input or dynamically identified
    for (; i < (v1.size() - (unrolled_itr - 1)); i += unrolled_itr) {
        if (v3[i]) {
            a1 += v1[i]*v2[i];
            a2 += v1[i+1]*v2[i+1];
            // ... i+n, cpu core dependent
        }
    }

    a = a1 + a2;

    // edge cases
    if ( v1.size() % unrolled_itr != 0) {
        for (;i < v1.size(); ++i) {
            if (v3[i]) {
                a += v1[i]*v2[i];
            }
        }
    }
}

template <typename UNIT>
void pipelineVVM(UNIT& a, std::vector<UNIT> &v1, std::vector<UNIT> &v2, std::vector<bool> &v3)
// pipelining: a += (v1[i] + v2[i]) * (v1[i] - v2[i])
// using SIMD instructions to load simulatenous ops into registers
// could be further optimized with handling the add/sub/multi on different cores
{
    a = 0.0;
    // Ensure the size is a multiple of 8 for SIMD processing
    std::size_t simd_end = v1.size() - (v1.size() % 8);
    // Use SIMD to process 8 elements at a time
    for (size_t i = 0; i < simd_end; i += 8) {
        if (v3[i]) {
            __m256 v1_part = _mm256_loadu_ps(&v1[i]);
            __m256 v2_part = _mm256_loadu_ps(&v2[i]);
            __m256 sum = _mm256_add_ps(v1_part, v2_part);
            __m256 diff = _mm256_sub_ps(v1_part, v2_part);
            __m256 prod = _mm256_mul_ps(sum, diff);

            // Sum the results using horizontal add
            __m256 hsum = _mm256_hadd_ps(prod, prod);
            hsum = _mm256_hadd_ps(hsum, hsum);
            float temp[8];
            _mm256_storeu_ps(temp, hsum);
            a += temp[0] + temp[4]; // Add the horizontal sum to 'a'
        }
    }

    // Process any remaining elements
    for (size_t i = simd_end; i < v1.size(); ++i) {
        if (v3[i]) {
            a += (v1[i] + v2[i]) * (v1[i] - v2[i]);
        }
    }
}