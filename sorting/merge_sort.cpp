// merge Sort
// O(nlogn) at best
// O(nlogn) at worst

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <iterator>

template <typename T, size_t N>
void merge(std::array<T,N>& input, const size_t left, 
           const size_t mid, const size_t right)
{
    const size_t subA = mid - left + 1;
    const size_t subB = right - mid;

    // create temp arrays
    std::unique_ptr<T[]> lhs(new T[subA]);
    std::unique_ptr<T[]> rhs(new T[subB]);

    // copy date to temp arrays
    for (size_t i=0; i<subA; ++i){ lhs[i] = input[left+i]; }
    for (size_t i=0; i<subB; ++i){ rhs[i] = input[mid+1+i]; }

    size_t lhs_index{0}, rhs_index{0};
    size_t merge_index{left};

    // merge temp arrays back into array[left...right]
    while (lhs_index < subA && rhs_index < subB) {
        if (lhs[lhs_index] <= rhs[rhs_index]) { 
            input[merge_index] = lhs[lhs_index];
            ++lhs_index;
        } else {
            input[merge_index] = rhs[rhs_index];
            ++rhs_index;
        }
        ++merge_index;
    }
    
    // fringe cases
    while (lhs_index < subA) {
        input[merge_index] = lhs[lhs_index];
        ++lhs_index; ++merge_index;
    }

    while (rhs_index < subB) {
        input[merge_index] = rhs[rhs_index];
        ++rhs_index; ++merge_index;
    }
}

template <typename T, size_t N>
void merge_sort(std::array<T,N>& input, const size_t begin, const size_t end)
{
    if (begin >= end) return;

    const size_t mid = begin + (end - begin) / 2;
    merge_sort(input, begin, mid);
    merge_sort(input, mid + 1, end);
    merge(input, begin, mid, end);
}

int main()
{
    std::array<int,10> array{ 69, 1, 2, 3, 4, 5, 7, 0, 8, 0 };
    auto it = array.begin();

    for (auto i : array) std::cout << i << ", ";
    std::cout << std::endl;
    merge_sort(array, 0, array.size()-1);
    for (auto i : array) std::cout << i << ", ";
}