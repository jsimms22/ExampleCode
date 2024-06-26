// Bubble Sort
// O(nlogn) at best
// O(n^2) at worst

#include <iostream>
#include <array>
#include <algorithm>

template <typename T, size_t N>
void bubble_sort(std::array<T,N>& input)
{
    bool status{false};
    for (int i = 0; i < N; ++i) {
        status = false; 
        for(int j = 0; j < N-i-1; ++j) {
            if (input[j] > input[j+1]) {
                std::cout << "swapping: " << input[j] << " and " << input[j+1] << '\n'; 
                std::swap(input[j], input[j+1]);
                status = true;
            }
        }
        if (!status) { 
            std::cout << "exiting.\n"; 
            break; 
        }
    }
}

int main()
{
    std::array<int,10> array{ 69, 1, 2, 3, 4, 5, 7, 0, 8, 0 };

    for (auto i : array) std::cout << i << ", ";
    std::cout << std::endl;
    bubble_sort(array);
    for (auto i : array) std::cout << i << ", ";

    return 0;
}