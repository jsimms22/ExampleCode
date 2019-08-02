#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) 
{
  int nthreads, tid;
  #pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    printf("Hello world from thread %d\n",tid);
        
    #pragma omp barrier
    #pragma omp master
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
  }
}
