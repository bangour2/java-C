/*
The purpose of the assignment is to help reinforce pthreads concepts.  Specifically, the assignment modify the merge sort program to parallelize the merge function.  Execute both versions for 10 different data sizes and 4 different numbers of threads.  Discuss the impact of the parallelization of the merge function on the efficiency.   
----------------------------
**
the efficiency is clearly high because, we split our input and recombine the results. In order words, wtih more than 1 thread, the job overload is cut down.  

we have cut down the execution of serial code blocks.

of course at first there is high overhead specially if the data size is very large due to the creation threads.

according to  http://www.cs.princeton.edu/courses/archive/fall13/cos326/notes/parallel-complexity.php,

"the effectiveness of a divide-and-conquer algorithm can often be determined by the cost of splitting and merging data. These costs are in turn dictated by the choice of data structure used."

Execution of 10 diffrent data sizes and 4 different number of threads:


---------------------------

1 threads, 5000 data:

[mbangour@vogel ~]$ ./merge 1 5000
array is sorted
Finished in about 0 seconds. 

10 threads, 10,000 data

array is sorted
Finished in about 1 seconds. 

25 threads, 100,000 data

[mbangour@vogel ~]$ ./merge 25 100000
array is sorted
Finished in about 4 seconds.

50 threads, 1000000 data

[mbangour@vogel ~]$ ./merge 50 1000000
array is sorted
Finished in about 42 seconds. 

500 threads, 5000000 data

no value

-------------------------------------------------------------

2 threads, 5000 data:

[mbangour@vogel ~]$ ./merge 2 5000
array is sorted
Finished in about 0 seconds. 


20 threads, 10,000 data

[mbangour@vogel ~]$ ./merge 20 10000
array is sorted
Finished in about 1 seconds. 

50 threads, 100,000 data

[mbangour@vogel ~]$ ./merge 50 100000
array is sorted
Finished in about 4 seconds. 

100 threads, 1000000 data

[mbangour@vogel ~]$ ./merge 100 1000000
array is sorted
Finished in about 41 seconds.


1000 threads, 5000000 data

no vlaue
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float* get_data (int data_count);

void err_sys (const char* message);

void* thread_merge_sort (void* args);

void merge (float* data, int lower, int upper, int mid);

void* choice (void* args);

int first (long my_rank);

int last (long my_rank);

int size (long my_rank);

float* putInTemp(long my_rank); //each thread stores

int is_sorted (float* data, int size);


typedef struct
{
  float* data;
  int left;
  int right;
} subarray;

long track = 0; //keep track of # of merge execution
long array_size_copy;
int mid_copy;
float* current_data;
float* temp;
int thread_count;
long int tv_sec;
clock_t ticks;


int main (int argc, char* argv[])
{
   
       time_t start, stop;
       long long array_size;
       
       if (argc < 3)
       err_sys ("missing command line argument, need # of thread and arrays-size");
   
 thread_count = strtol(argv[1], NULL, 10); 
 if(thread_count > array_size/2) err_sys("number of thread should not be greater than half of data size");
 
 array_size = strtol(argv[2], NULL, 10);
 
  
  array_size_copy = array_size;
  mid_copy = array_size/2;     

  float* data = get_data (array_size);   
  pthread_t array_thread;
  
  
  subarray entire_array = {data, 0, array_size - 1};
  time(&start);
  int result = pthread_create (&array_thread, NULL, thread_merge_sort,
                   (void*)(&entire_array));
  if (result != 0)
    err_sys ("pthread create error");
  result = pthread_join (array_thread, NULL);
  
  time(&stop);

  if (result != 0)
    err_sys ("pthread join error");
  if (is_sorted (data, array_size))
    printf ("array is sorted\n");
  else
    printf ("array is not sorted\n");
    
  printf("Finished in about %.0f seconds. \n", difftime(stop, start));
  return 0;
}

void* thread_merge_sort (void* args)
{
    ticks = clock();
    /*pointer object */
 pthread_t* thread_handles; 
 int thread_count = 2;
 /* size of */
 thread_handles = malloc (thread_count*sizeof(pthread_t)); 
    
  subarray* params = (subarray*)args;
  if (params -> left < params -> right)
  {
        
    pthread_t right_thread;
    int right_created = 0;
    int mid = (params -> left + params -> right) / 2;
    
    
    if (params -> left < mid)
    {

     subarray left_array = {params -> data, params -> left, mid};
     thread_merge_sort ((void*)(&left_array));
      //printf("left_array %d, %d, %d \n", params -> left, params -> right, mid);

    }
    if (mid < params -> right)
    {       
    //printf("right_array, create_thread %d, %d, %d \n", params -> left, params -> right, mid);    
      right_created = 1;
      subarray right_array = {params -> data, mid + 1, params -> right};
      
      int result = pthread_create (&right_thread, NULL, thread_merge_sort,(void*)(&right_array));
      
      if (result != 0)
    err_sys ("pthread create error\n");
    } 
    if (right_created)
    {
      int result = pthread_join (right_thread, NULL);
      if (result != 0)
    err_sys ("pthread join error\n");
    } 
    
    if(track == array_size_copy -4) //the subarrays are ordered
   {
        
 current_data  = params -> data;
 int thread;

    for(thread = 0; thread <thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, choice, (void*) thread); 
    for(thread = 0; thread <thread_count; thread++)
    pthread_join (thread_handles[thread], NULL);
        
    /* delete pointer object*/  
     free(thread_handles); 
     
      if (is_sorted (temp, array_size_copy))
    printf ("array is sorted\n");
  else
    printf ("array is not sorted\n");
    
    exit(0);
                
    }    
    merge (params -> data, params -> left, params -> right, mid);
  }
  return NULL;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

int first (long my_rank)
{
    if(my_rank == 0) return (array_size_copy/(mid_copy*thread_count))-1; //thread_i index 
    else return my_rank*(array_size_copy/(mid_copy*thread_count)); //thread_i+1 index
}

int last (long my_rank)
{
    return size(my_rank) -1;
}

int size(long my_rank)
{
    if(my_rank == 0)
    {
        int size=0, i;
        for(i =mid_copy; i<array_size_copy; i++ ){
     if(current_data[first(my_rank)] > current_data[size+mid_copy])
         size++;}
    return size++;} //size of array    
    
    else
    {
        int size=0, i;
        for(i =mid_copy; i<array_size_copy; i++ ){
     if(current_data[first(my_rank-1)] > current_data[size+mid_copy])
         size++;}
    return array_size_copy - size++;} //size of array
}  

float* putInTemp(long my_rank) //each thread stores
{
    temp = malloc (array_size_copy * sizeof (float));

    if(my_rank == 0){
       int max = first(my_rank);
       int m = mid_copy;
       int i;
       for(i = 0; i <= max; i++)
       temp[i] = current_data[i]; 
       
          for(i = max+1; i <= last(my_rank); i++)
          temp[i] = current_data[m]; m++;}
          
    if(my_rank == 1){
        int max = mid_copy;
        int m = last(my_rank-1) + mid_copy;
        int i;
        for(i = first(my_rank); i<max; i++)
         temp[i] = current_data[i]; 
         
         for(i =max+1; i<=size(my_rank)+1; i++)
         temp[i] = current_data[m];}
         
         return temp;
}

void* choice(void* args)
{
    long my_rank = (long) args;
    
    first (my_rank); //return lower index
    last (my_rank); //return upper index
    int mid =(first(my_rank)+last(my_rank))/2;
    
    float* new_data = putInTemp(my_rank); //each thread stores
    merge(new_data, first, last, mid);

}

void merge (float* data, int lower, int upper, int mid)
{
    //printf("merge %d %d %d\n", lower, upper, mid);    
  float temp[upper - lower + 1];
  int i = lower;
  int j = mid + 1;
  int k = 0;
  while (i <= mid && j <= upper)
  {
    if (data[i] < data[j])
    {
      temp[k] = data[i];
      i++;
    }
    else
    {
      temp[k] = data[j];
      j++;
    }
    k++;
  }
  while (i <= mid)
  {
    temp[k] = data[i];
    i++; 
    k++;
  }
  while (j <= upper)
  {
    temp[k] = data[j];
    j++; 
    k++;;
  }
  for (k = 0; k < upper - lower + 1; k++)
    data[lower + k] = temp[k];
  
}

 float* get_data (int data_count)
 {
   float* data = malloc (data_count * sizeof (float));
   if (data == NULL)
     err_sys ("malloc error");
   srand(0);
   int i;
   for (i = 0; i < data_count; i++)
   {
     data[i] = ((float)rand()/(float)(RAND_MAX)) * 10000;
     //printf("%g \n", data[i]);
   }
   return data;
 }

int is_sorted (float* data, int size)
{
  int i = 0;
  int l = 0;
   for (l = 0; l < size; l++)
   {
     //printf("%g \n", data[l]);
   }
  while (i < size-1 && data[i] <= data[i+1]){i++;}
    
   
  return i == size - 1;
}
