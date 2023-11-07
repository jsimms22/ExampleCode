#include<vector>
#include<iostream>
#include<fstream>
#include<cmath>
#include<omp.h>

using namespace std;

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    std::vector<int> x(n,1);
    int sum = 0;

    omp_set_num_threads(3);
    int i;
    double start,end;

    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += x[i];
    }
    end = omp_get_wtime();

    cout << "total parallel time: " << end-start << "\tsum = " << sum << endl;

    sum = 0;
    start = omp_get_wtime();
    for (i = 0; i < n; i++) {
        sum += x[i];
    }
    end = omp_get_wtime();

    cout << "total serial time: " << end-start << "\tsum = " << sum << endl;
}