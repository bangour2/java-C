/*
To Profesor: Dr. Gayler
From Student: Mohammad Bangoura
School: Kennesaw State

The purpose of the assignment is to help reinforce pthreads concepts.  Specifically, the assignment modify the merge sort program to parallelize the merge function.  Execute both versions for 10 different data sizes and 4 different numbers of threads.  Discuss the impact of the parallelization of the merge function on the efficiency.   Please email your work to your instructor by 8:00 am 
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


/*
this function takes 1 arguments of type 
integer
*/
float* get_data (int data_count);


/*
this function takes 1 arguments of type 
char pointer
*/
void err_sys (const char* message);

/*
this function takes 1 arguments of any type 
*/

void* thread_merge_sort (void* args);

/*
this function takes 4 arguments of type 
float pointer and integer
*/

void merge (float* data, int lower, int upper, 

int mid);

/*
this function takes 2 arguments of type 
float pointer and integer
*/
int is_sorted (float* data, int size);


/*
hold 4 data types in the struct
right sisde, left side, entire data
*/
typedef struct
{
  float* data;
  int left;
  int right;
} subarray;

/*
main function takes 2 arguments
interger and array of char pointer 
data type
*/

int main (int argc, char* argv[])
{
  long long array_size = 1000000; //size of 

//array
  
  /*
  initialize pointer data to function
  get_data
  */
  float* data = get_data (array_size);
  
  
  pthread_t array_thread; //handle for new 

//thread
  
  /*
   entire_array holds 3 values
   entire_array[0] = the data itself
   from  0, left_array
   to  1000000 - 1, right_array
  */
  subarray entire_array = {data, 0, array_size - 1};
  
  
  /*
  create a thread
  (handle for thread, null, function to 

compute, offset of thread rank)
  */
  int result = pthread_create (&array_thread, 

NULL, thread_merge_sort, (void*) (&entire_array));
                   
                   
  if (result != 0)
    err_sys ("pthread create error");
    
    /*
    once a thread is done computing,
    its terminated
    */
  result = pthread_join (array_thread, NULL);
  if (result != 0)
    err_sys ("pthread join error");
    
    /*
    check if data is sorted
    */
  if (is_sorted (data, array_size))
    printf ("array is sorted\n");
  else
    printf ("array is not sorted\n");
  return 0;
}

/*
each thread execute this function

*/
void* thread_merge_sort (void* args)
{
  subarray* params = (subarray*)args;
  
  /*

  
  */
  
  /*
   if left_array is less than right-array:
   choose the middle (which is index) to be:
   [left data + right data] /2 

  */
  if (params -> left < params -> right)
{
    pthread_t right_thread; //creating thread on the fly
    int right_created = 0;
    int mid = (params -> left + params -> 

right) / 2;
    
    /*
    if left_array is less than middle index:
    */
    if (params -> left < mid)
    {
        /*
        left_array holds 3 values
        data itself, from left_array to mid
        */
      subarray left_array = {params -> data, 

params -> left, mid};
      
      /*
      recursion of function      
      */
      thread_merge_sort ((void*)(&left_array));
    }
    
    /*
    if middle data is less than right data:

    */
    if (mid < params -> right)
    {
      right_created = 1;
      
      /*
      right_array holds 3 values
      data, from mid+1 index to right_array
      */
      subarray right_array = {params -> data, mid + 1, params -> right};
      
      /*
      create a thread to deal with right side of 

the merge split
      */
      int result = pthread_create 

(&right_thread, NULL, thread_merge_sort,
				   

(void*)(&right_array));
      if (result != 0)
	err_sys ("pthread create error");
     }
     
     /*
     if the thread creation was successful,
     after doing its computation,
     it is terminated
     */
    if (right_created)
    {
      int result = pthread_join (right_thread, 

NULL);
      if (result != 0)
	err_sys ("pthread join error");
    }  
    
    /*
    go to merge function with these 

arguments
    */
    merge (params -> data, params -> left, 

params -> right, mid);
  }
  return NULL;
}

/*
function with 1 argument of type char pointer
*/
void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

void merge (float* data, int lower, int upper, 

int mid)
{
    //??
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
    //alocate pointer data
   float* data = malloc (data_count * sizeof 

(float));
   
   if (data == NULL)
     err_sys ("malloc error");
   
   srand(0); //initialize random number 

//generator
   
   int i;
   
   /*
   go through the loop
   and generate random numbers
   */
   for (i = 0; i < data_count; i++)
     data[i] = ((float)rand()/(float)

(RAND_MAX)) * 10000; //??
   return data; //return any stored value
 }

/*
function with 2 arguments:
all data and the size of data

check if data are arranged in order

*/
int is_sorted (float* data, int size)
{
  int i = 0;
  while (i < size-1 && data[i] <= data[i+1])
    i++;
  return i == size - 1;
}



