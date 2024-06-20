/*
  This program explores using parallel methods (openmp) to evaluate potential
    performance and optimization increases over a serial implementation.

  The methodolody employs a simple integration method to calculate pi.

  Test Run Output:
    pi = 3.14159
    parallel time = 0.0110002 seconds
    serial pi = 3.14159
    serial time = 0.15 seconds
*/

#include <stdio.h>
#include <omp.h>

static const unsigned long int num_steps = 100000000;

int main() 
{
    //===========================================//
    //------------------PARALLEL-----------------//
    //===========================================//
  
/* 
    replaced by using omp_get_max_threads() in line 26
    omp_get_max_threads gets as many threads available on the machine
    int numthreads = 12;
*/
  double x, sum, pi = 0.0;
  double TIME1, TIME2;  

  const double step = 1.0/(double) num_steps;

  TIME1 = omp_get_wtime();
  omp_set_num_threads(omp_get_max_threads());

/* 
  #pragma omp parallel {
      #pragme omp for
  }  
*/
    // The above directive is the same as using the directive below

    // Private makes variables private to each thread

    // Reduction makes local copy of the variable for each thread
    // then after the loop ends it adds the local copies into a
    // global variable of the same name.

  #pragma omp parallel for private(x) reduction(+:sum) //schedule(auto)
    for (register unsigned long int i = 0; i < num_steps;i++) {
      x = (i+0.5)*step;

      // didn't need this because of reduction(+:sum) was much faster
      //#pragma omp critical
      sum += 4.0/(1.0+x*x);

      // didn't need the below lines since 'pragma omp for' makes the iterater private
      //#pragma omp atomic
      //i++;
    }

  TIME2 = omp_get_wtime();
  
  pi = sum*step;
  printf("pi = %g\n",pi);
  printf("parallel time = %g seconds\n",TIME2-TIME1);
 
  //===========================================//
  //------------------SERIAL-------------------//
  //===========================================//
  x = 0.0; 
  pi = 0.0;
  sum = 0.0;
  
  TIME1 = omp_get_wtime();
  for (register unsigned long int i = 0; i < num_steps;) {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
    i++;
  }
  TIME2 = omp_get_wtime();

  pi = sum*step;
  printf("serial pi = %g\n",pi);
  printf("serial time = %g seconds\n",TIME2-TIME1);

  return 0;
}
