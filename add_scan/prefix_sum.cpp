#include<vector>
#include<iostream>
#include<omp.h>

std::vector<int> prefix_sum(std::vector<int> elements)
{
    omp_set_num_threads(2);
    int n = elements.size();
    int p = omp_get_num_threads();

    std::vector<int> prefix_sums(n,0);

#pragma omp parallel
{
    for (int i = 0; i < (p-1); i++) {
        //i = index of current processing element
        for (int j = (i * (n/(p+1))); j <= ((i+1) * (n/(p+1))); j++ ) {

        }
    }
}
    
    return prefix_sums;
}

int main()
{
    std::vector<int> x {0,1,2,3,4,5,6,7,8,9};
    std::vector<int> y;

    y = prefix_sum(x);
}