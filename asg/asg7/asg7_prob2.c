#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char* argv[]) 
{ 
   int thread_count;
   long long int n_tosses;

   thread_count = strtol(argv[1], NULL, 10); 
   n_tosses = strtol(argv[2], NULL, 10);
 
  time_t start, stop; time(&start);
  double x, y, pi_estimate;
  srand(0);
  long long int n_in_circle = 0;
  int i;
 
  #pragma omp parallel num_threads(thread_count) 
  {
      #pragma omp master
      {
          thread_count =  omp_get_num_threads();
      }
   
    #pragma omp parallel private(x, y, i) reduction(+:n_in_circle)
    for (i=0; i < n_tosses; i++) {
        
      double x = (double) rand()/RAND_MAX;
      double y = (double) rand()/RAND_MAX;
      if ((x*x + y*y) <= 1) n_in_circle++;
    }
    
    #pragma omp master
    {
    pi_estimate = 4 * n_in_circle /n_tosses;
    }
  } time(&stop);
   printf("estimated pi = %f \n", pi_estimate);
   printf("finished in about = %g seconds\n", difftime(stop, start));
   return 0;
}