 #include <stdio.h> 
 #include <stdlib.h>
 #include <pthread.h> 
 
 /* Global variable: accessible to all threads */
 int thread_count; 
 void* Hello(void* rank); //function hello
 
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
 pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread); 
 
 printf("Hello from the main thread\n"); 
 
 for (thread = 0; thread < thread_count; thread++) 
 pthread_join(thread_handles[thread], NULL); 
 
 /* delete pointer object*/
 free(thread_handles); 
 
 return 0;  } 
 
 /* function hello, argument rank */
 void* Hello(void* rank) {
 long my_rank = (long) rank;
 /* Use long in case of 64-bit system */
 
 printf("Hello from thread %ld of %d\n", my_rank, thread_count); 
 
 return NULL;  } 
 
 /* Hello */
