#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;

int main() 
{
  //===========================================//
  //------------------PARALLEL-----------------//
  //===========================================//
  
/* replaced by using omp_get_max_threads() in line 26
 * omp_get_max_threads gets as many threads available on the machine
 *
 * int numthreads = 12;
 */

  register int i;
  double x, sum, pi = 0.0;
  double TIME1, TIME2;  

  step = 1.0/(double) num_steps;
  
  TIME1 = omp_get_wtime();
  omp_set_num_threads(omp_get_max_threads());

/* #pragma omp parallel
 * {
 *    #pragme omp for
 * }  
 * ^^^^^^^^
 * -Is the same as the following active directive
 *
 * -Private makes variables private to each thread
 *
 * -Reduction makes local copy of the variable for each thread
 * then after the loop ends it adds the local copies into a
 * global variable of the same name.
 */
#pragma omp parallel for private(x) reduction(+:sum)
  for (i = 0; i < num_steps;i++)
  {
    x = (i+0.5)*step;

/*didn't need this because of reduction(+:sum) was much faster*/
//#pragma omp critical
    sum += 4.0/(1.0+x*x);

/*didn't need this because of pragma omp for makes the iterater private*/
//#pragma omp atomic
//    i++;
  }

  TIME2 = omp_get_wtime();
  
  pi = sum*step;
  printf("pi = %g\n",pi);
  printf("parallel time = %g seconds\n",TIME2-TIME1);
 
  //===========================================//
  //------------------SERIAL-------------------//
  //===========================================//

  i = 0;
  x = 0.0; 
  pi = 0.0;
  sum = 0.0;
  
  TIME1 = omp_get_wtime();
  for (; i < num_steps;)
  {
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
