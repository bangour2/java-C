#include <stdio.h>
#include <string.h>
#include <omp.h>   
#include <time.h>
#include <sys/time.h>
clock_t ticks;

int n;

main(int argc, char* argv[])
{
   time_t start, stop;
    
  if (argc < 2) printf("needs 1 command line data size\n");
n = strtol(argv[1], NULL, 10);

  time(&start);
  ticks = clock();

    int a[n];
    int i;
    
     for (i = 1; i < n; i++) 
  {a[i] = (.5*i)*(i+1); 
  printf(" %d \n",a[i]);
  printf("\n");}
    
  time(&stop);
  printf("Finished in about %.0f seconds. \n", difftime(stop, start));

    
      return 0;
}