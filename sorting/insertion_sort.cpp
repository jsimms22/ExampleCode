// Insertion Sort
// O(n) at best
// O(n^2) at worst

#include <iostream>
#include <array>
#include <algorithm>

template <typename T, size_t N>
void insertion_sort(std::array<T,N>& input)
{
    T key{}; int j{};
    for (int i=1; i<N; ++i) {
        key = input[i];
        j = i - 1;

        // Move elements of input[0...i-1]
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j>=0 && input[j] > key) {
            std::cout << "swapping: " << input[j+1] << " and " << input[j] << '\n'; 
            std::swap(input[j+1],input[j]);
            j -= 1;
        }
        input[j+1] = key;
    }
}

int main()
{
    std::array<int,10> array{ 69, 1, 2, 3, 4, 5, 7, 0, 8, 0 };

    for (auto i : array) std::cout << i << ", ";
    std::cout << std::endl;
    insertion_sort(array);
    for (auto i : array) std::cout << i << ", ";
}