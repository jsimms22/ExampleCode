#include<vector>
#include<iostream>
#include<fstream>
#include<omp.h>
#include<ctime>
#include<cmath>

//constexpr int n = 12;

int main(int argc, char** argv)
{
    srand(time(NULL));

    int n = atoi(argv[1]);

    std::vector<int> x(n,1);
    std::vector<int> y(n,0);
    std::vector<int> prefix_sums(n,0);

    // for (int i = 0; i < x.size(); i++) {
    //     x[i] = rand() % 10;
    // }

    prefix_sums[0] = x[0];

    int j, i, p;
    double start, end;
    std::ofstream os {"results.dat"};

    omp_set_num_threads(3);

    #pragma omp parallel shared(x,prefix_sums)
    {   
        p = omp_get_num_threads();
        start = omp_get_wtime();
        #pragma omp for private(j)
        for (i = 0; i <= p-1; i++) {
            //i = index of current processing element
            for (j = (i * (n/(p+1))); j <= (((i+1) * (n/(p+1)))-1); j++) {
                //#pragma omp critical
                //std::cout << "thread id: " << omp_get_thread_num() << '\t' << "i: " << i << '\t' << "j: " << j << '\n';
                prefix_sums[j+1] =  x[j+1] + x[j];  // calculates 
            }
        }
        end = omp_get_wtime();
    }

    int temp_val = 0;
    #pragma omp master
    for (i = 1; i <= p; i++) {
        std::cout << i * n / (p+1)-1  << '\t' << i * n / (p+1) << '\n';
        temp_val += prefix_sums[i * n / (p+1)-1];
        prefix_sums[i * n / (p+1)] = temp_val;
    }

    os << "loop time: " << end - start << std::endl;
    for (i = 0; i < x.size(); i++) {
        os << x[i] << " " << prefix_sums[i] << '\n';
    }

    os.close();
}