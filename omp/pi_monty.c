#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

static unsigned long int n = 100000000;

int main (int argc, char *argv[])
{
  unsigned long int count, i = 0;
  long double x,y,pi = 0.0;
  double start,end;
  
  srand48((int)time(NULL));

  //===========================================//
  //------------------PARALLEL-----------------//
  //===========================================//

  /* This parallel code will not be faster than the serial
   * with only 12 threads.
   */
  start = omp_get_wtime();

  omp_set_num_threads(omp_get_max_threads());
  int nthreads = omp_get_max_threads();

  /* you don't need to make iterators private in parallel for directives
   *
   * schedule(kind [,chunk_size])
   *
   * kinds: static, dynamic, runtime, auto
   *
   * static: used for when we know what chunk size will be best before runtime
   * dynamic: used when best chunk size is unknown and it will adjust 
   * runtime: determined at runtime
   * auto: we let the compiler determine wht the chunksize will be
   */
#pragma omp parellel for private(x,y) reduction(+:count) schedule(static [,50])
{
  /* The Monty Carlo method for finding Pi works by calculating
   * random points inside a box, with width and height of 1.
   * Points (n) to lie on or within a quarter circle of radius 1 is
   * known to be n = (pi * N) / 4. Therefore we need to randomly
   * generate an x and y coordinate and apply the rule of x*x + y*y <= 1 
   */

  for (i = 0;i < n;i++)
  {
    x = (double)drand48();
    y = (double)drand48();
    if (x*x + y*y <= 1.0) count++; 
  }
//#pragma omp barrier
}
  //printf("totalCount for parallel code = %lu \n",count);
  pi = 4.0 * ((double)count / (double)n);
  
  end = omp_get_wtime();

  printf("parallel monte-carlo pi value: %Lg \n",pi);
  printf("runtime of parallel code: %g \n",end-start);

  //------------------------------------------------//

  count = 0;
  x,y,pi = 0.0;

  //===========================================//
  //------------------SERIAL-------------------//
  //===========================================//

  start = omp_get_wtime();
  for (i = 0;i < n;i++)
  {
    x = (double)drand48();
    y = (double)drand48();
    if (x*x + y*y <= 1.0) count++;
  }
  
  //printf("totalCount for serial code = %lu \n",count);
  pi = 4.0 * ((double)count / (double)n);
  end = omp_get_wtime();

  printf("serial monte-carlo pi value: %Lg \n",pi);
  printf("runtime of serial code: %g \n",end-start);
  
  return 0;
}

