/*
To Profesor: Dr. Gayler
From Student: Mohammad Bangoura
School: Kennesaw State

The purpose of the assignment is to help reinforce pthreads concepts.  Specifically, the assignment modify the merge sort program to parallelize the merge function.  Execute both versions for 10 different data sizes and 4 different numbers of threads.  Discuss the impact of the parallelization of the merge function on the efficiency.   
----------------------------
**
the efficiency is clearly high because, we split our input and recombine the results. 

we have cut down the execution of serial code blocks.

of course at first there is high overhead specially if the data size is very large.

"the effectiveness of a divide-and-conquer algorithm can often be determined by the cost of splitting and merging data. These costs are in turn dictated by the choice of data structure used.
In general, lists are bad data structures for parallel programming -- you typically have to traverse a list (incurring ~n span) in order to gather the data you need to commence a parallel computation. Balanced trees (and several other kinds of data structures) are better because they support constant-work and constant-span operations to split your data in half or recombine it. " from http://www.cs.princeton.edu/courses/archive/fall13/cos326/notes/parallel-complexity.php
---------------------------
source: http://cs.indstate.edu/~jkinne/cs670-s2013/code/sort/mergeSort4.cpp
------------------------------------------
/*
 compile: g++ blah.cpp -pthread
 run: ./a.out number

change from mergeSort.cpp - using pthreads for || processing.
  note that howMany, the command line argument, is the total number of 
  numbers.  each thread gets howMany/numTasks many numbers.  numTasks
  is set in main.  you will have to change the code and recompile to set it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numTasks, rank;
int howMany;

int min(int a, int b) {
  if (a <= b) return a;
  return b;
}

int max(int a, int b) {
  if (a >= b) return a;
  return b;
}


int *createNumbers(int howMany) {
  int * numbers = (int *) malloc(sizeof(int) * howMany);

  if (numbers == NULL) {
    printf("Error: malloc failed.\n");
    return NULL;
  }
  
  // note: if all processes seed with 0, then they will
  // all have the same random numbers.
  srand(rank+3);

  for(int i=0; i < howMany; i++) 
    numbers[i] = rand();

  return numbers;
}

void printNumbers(int * numbers, int howMany) {
  printf("\n");
  for(int i=0; i < howMany; i++)
    printf("%d\n", numbers[i]);
  printf("\n");
}


void merge(int *A, int iLeft, int iRight, int iEnd, int *B)
{
  int i0 = iLeft;
  int i1 = iRight;
  int j;
  
  /* While there are elements in the left or right lists */
  for (j = iLeft; j < iEnd; j++) {
    /* If left list head exists and is <= existing right list head */
    if (i0 < iRight && (i1 >= iEnd || A[i0] <= A[i1])) {
      B[j] = A[i0];
      i0 = i0 + 1;
    }
    else {
      B[j] = A[i1];
      i1 = i1 + 1;
    }
  }
}

bool printed = false;

// note: copied from wikipedia.
// startWidth is how many are already sorted.  set it to 1
// by default if list is not pre-sorted at all.
void mergeSort(int *list, int n, int startWidth)
{
  int *A = list;
  int *B = (int *)malloc(sizeof(int)*n);

  if (B == NULL) {
    printf("Error: malloc failed.\n");
    return;
  }

  int width;
 
  /* Each 1-element run in A is already "sorted". */
  /* Make successively longer sorted runs of length 
     2, 4, 8, 16... until whole array is sorted. */
  for (width = startWidth; width < n; width = 2 * width) {
    int i;
    
    /* Array A is full of runs of length width. */
    for (i = 0; i < n; i = i + 2 * width)  {
      /* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[] */          /* or copy A[i:n-1] to B[] ( if(i+width >= n) ) */
      merge(A, i, min(i+width, n), min(i+2*width, n), B);
    }
    
    /* Now work array B is full of runs of length 2*width. */
    /* Copy array B to array A for next iteration. */
    /* A more efficient implementation would swap the roles of A and B */
    int *temp = B; B = A; A = temp;
    /* Now array A is full of runs of length 2*width. */
  }
  
  // make sure results are in list.  
  if (A == list)
    free(B);
  else {
    for(int i=0; i < n; i++)
      list[i] = A[i];
    free(A);
  }
}

int isSorted(int *numbers, int howMany) {
  for(int i=1; i<howMany; i++) {
    if (numbers[i] < numbers[i-1]) return 0;
  }
  return 1;
}

// function that is run to start a thread.  input will be the beginning 
// of an array of numbers to sort.  so just sort those and then return.
void *merging(void *input) {

  int *numbers = (int *) input;

  //printNumbers(numbers, howMany/numTasks);
  //printf("merging...\n");

  mergeSort(numbers, howMany/numTasks, 1);

  //printNumbers(numbers, howMany/numTasks);
  
  pthread_exit(NULL);
}

 
int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("  Usage: ./a.out howMany.\n");
    return 0;
  }
  howMany = atoi(argv[1]);

  long int returnVal;
  int len;
  pthread_t threads[100];
  void *status;
  pthread_attr_t attr;


  numTasks = 1;

  if (howMany % numTasks != 0) {
    printf("Error: numTasks not multiple of howMany.\n");
    return 0;
  }

  // first create all of the random numbers - this is single-threaded.
  int * numbers = createNumbers(howMany);

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


  // create workers.  each will get a part of the array of numbers - passed
  // in as the last parameter to pthread_create, that gets passed into the
  // merging function.  note that even though numbers is a global array,
  // it is okay to do this multi-threaded because each thread is working
  // on an independent part of the array.
  int i;
  for(i=0; i < numTasks; i++) {
    returnVal = pthread_create(&threads[i], &attr, merging, 
    		       (void *) &numbers[i*(howMany/numTasks)]);
    if (returnVal) {
      printf("Error, return code from pthread_create() is %d.\n", returnVal);
      exit(-1);
    }
  }

  // wait for workers to be done.  when they are all done, then each 
  // chunk of the array will be sorted.
  int dummy;
  for(i=0; i < numTasks; i++) {
    returnVal = pthread_join(threads[i], (void **) &dummy);
    if (returnVal) {
      printf("error, return code from pthread_join() is %d.\n", returnVal);
      exit(-1);
    }
  }

  // the chunks are sorted, now combine them single-threadedly.
  mergeSort(numbers, howMany, howMany/numTasks);

  if (isSorted(numbers, howMany))
    printf("Numbers are sorted now!\n");
  else
    printf("Problem - numbers are not sorted!\n");

  //printNumbers(numbers,howMany);

  free(numbers);

  pthread_exit(NULL);
  return 0;
}
