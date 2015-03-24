#include <stdio.h> 
 #include <stdlib.h>
 #include <pthread.h> 
 
 /* Global variable: accessible to all threads */
 int thread_count; 
 void* Thread_sum (void* rank); //function sum
 
 /* Thread function */ 
 int main(int argc, char* argv[]) {
 
 /* Use long in case of a 64-bit system */ 
  long thread; 

 /*pointer object */
 pthread_t* thread_handles; 

 /* Get number of threads from command line */
 thread_count = strtol(argv[1], NULL, 10); 
 
 /* size of */
 thread_handles = malloc (thread_count*sizeof(pthread_t)); 

for (thread = 0; thread < thread_count; thread++) 
 pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread); 
 
 printf("Hello from the main thread\n"); 
 
 for (thread = 0; thread < thread_count; thread++) 
 pthread_join(thread_handles[thread], NULL); 
 
 /* delete pointer object*/
 free(thread_handles); 
 
 return 0;  } 

void* Thread_sum(void* rank) 
{
    long my_rank = (long) rank; 
    double factor; 
     long i; int n = 100;
     long my_n = n/thread_count;
     long my_first_i = my_n *my_rank;
     long my_last_i = my_first_i + my_n;
     double sum = 0;
    
    if (my_first_i % 2 == 0) // /* my first_i is even */
    factor = 1.0; 
    
    else ///* my first i is odd */ 
    factor = -1.0;
    
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) 
    {
        sum += factor/(2*i+1); 
    } 
        return NULL; 
        
} /* Thread_sum */
