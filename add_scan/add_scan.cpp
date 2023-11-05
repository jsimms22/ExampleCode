#include<vector>
#include<iostream>

int main()
{
    std::vector<int> x = {0,1,2,3,4,5,6,7,8,9};
    std::vector<int> y = {0};
    for (int i = 1; i < x.size(); i++) {
        y.push_back(y[i-1] + x[i]);
    }

    for (int i = 0; i < x.size(); i++) {
        std::cout << y[i] << '\t' << x[i] << '\n';
    }
}