
 #include <stdio.h> 
 #include <stdlib.h>
 #include <pthread.h> 
 
 /* Global variable: accessible to all threads */
 int thread_count; 
 void* Pth_mat_vect(void* rank); //function Pth_mat_vect
 
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
 pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread); 
 
 printf("Hello from the main thread\n"); 
 
 for (thread = 0; thread < thread_count; thread++) 
 pthread_join(thread_handles[thread], NULL); 
 
 /* delete pointer object*/
 free(thread_handles); 
 
 return 0;  } 




void* Pth_mat_vect(void* rank) 
{
    long_my_rank = (long) rank; 
    int i, j; 
    int local_m = m/thread_count; 
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m - 1; 
    int result = 0 ;
    
    for (i = my_first_row; i <= my_last_row; i++) 
    {
        y[i] = 0.0;
        for (j = 0; j < n; j++) 
        y[i] += A[i][j]*x[j]; 
        
        result +=y[i];
    } 
    
    printf("%d", result);
    
    return NULL;
    
    } /* Pth_mat_vect */
