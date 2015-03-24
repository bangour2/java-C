
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define thread_number 25         	
#define numbers 

typedef mystruct   	
  {
  pthread_mutex_t  lock;       		
  int value;                  		 
  }

shared_value;
shared_value value1;

void * Input(void *id)    		
   {
   size_t tid = (size_t) id;
   int numsuccess, numtrials, i;
   numtrials = numbers/thread_number;
   numsuccess = 0;
   srand48((long) tid);

   for(i=0;i<numtrials;i++)
      {
      double x = drand48()*2-1; 
      double y = drand48()*2-1;    		
      if((x*x+y*y) <= 1.0) numsuccess++;
      }

  pthread_mutex_lock(&(value1.lock));   
  value1.value += numsuccess; 
  pthread_mutex_unlock(&(value1.lock)); 	
  return 0;
  }

int main (int argc, char *argv[])
   {
   pthread_t tids[thread_number];
   size_t i;
   double estimate;
   pthread_mutex_init(&(value1.lock),NULL);
   value1.value = 0;       
   printf("Creating Threads\n");		
   	
   for (i=0;i<thread_number;i++)
      pthread_create(&tids[i], NULL, calculate_pi, (void *) i);
      printf("joining\n");	

      for(i=0;i<thread_number;i++) pthread_join(tids[i], NULL);
      printf("Threads done\n");
      estimate = 4.0 * ((double) value1.value / (double) numbers);
      printf(" Pi = %lf\n", estimate);
      exit(0);
      }



