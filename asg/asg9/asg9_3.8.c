/*
the output was large
 sbatch asg9_3.8_batch
-----------------------------------------------------------------
              Welcome to the Stampede Supercomputer              
-----------------------------------------------------------------

--> Verifying valid submit host (login1)...OK
--> Verifying valid jobname...OK
--> Enforcing max jobs per user...OK
--> Verifying availability of your home dir (/home1/03271/tg825700)...OK
--> Verifying availability of your work dir (/work/03271/tg825700)...OK
--> Verifying availability of your scratch dir (/scratch/03271/tg825700)...OK
--> Verifying valid ssh keys...OK
--> Verifying access to desired queue (development)...OK
--> Verifying job request is within current queue limits...OK
--> Checking available allocation (TG-ASC140030)...OK
Submitted batch job 4536735

*/

//I found the source code online
/*http://www.math.ecnu.edu.cn/~jypan/Teaching/ParaComp/Codes_Pacheco/code/primes/mpi_merge_sort1.c*/



/*
 * File:     mpi_merge_sort.c
 * Purpose:  Implement parallel merge sort on a distributed list
 *           of randomly generated ints
 * Input:
 *    n:     number of elements per process
 * Output:
 *    A:     elements of distributed list after sorting
 *
 * Compile:  mpicc -g -Wall -o mpi_merge_sort mpi_merge_sort.c
 * Run:
 *    mpiexec -n <p> ./mpi_merge_sort
 *       - p: the number of processes
 *
 * Notes:
 * 1.  Uses tree-structured communication to gather the distributed
 *     lists onto process 0.
 * 2.  No attempt is made to be efficient with storage.
 * 3.  Assumes p is a power of 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

/* Largest possible int is RMAX-1 */
const int RMAX = 20;

/* Local functions */
void Generate_list(int A[], int local_n, int my_rank, int p);
int  Compare(const void* a_p, const void* b_p);
void Print_list(int A[], int n);
void Merge(int A[], int B[], int C[], int size);

/* Functions involving communication */
int  Get_n(int my_rank, MPI_Comm comm);
void Merge_sort(int A[], int local_n, int my_rank, 
         int p, MPI_Comm comm);
void Print_global_list(int A[], int local_n, int my_rank,
         int p, MPI_Comm comm);

int p, copy_n;
/*-------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   int my_rank;
   int* A;
   int local_n;
   MPI_Comm comm;

   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   local_n = Get_n(my_rank, comm);

   A = malloc(local_n*sizeof(int));
   Generate_list(A, local_n, my_rank, p);

   Print_global_list(A, local_n, my_rank, p, comm);

   Merge_sort(A, local_n, my_rank, p, comm);

   if (my_rank == 0)
      Print_list(A, p*local_n);

   free(A);

   MPI_Finalize();

   return 0;
}  /* main */


/*-------------------------------------------------------------------
 * Function: Get_n
 * Purpose:  Get the value of local_n from stdin
 * In args:  my_rank, comm
 * Ret val:  local_n
 */
int Get_n(int my_rank, MPI_Comm comm) {
   int n;

   if (my_rank == 0) {
      printf("What's n?\n");
      scanf("%d", &n);
      n = 16000000;
   } 
   MPI_Bcast(&n, 1, MPI_INT, 0, comm);

   return n/p;
}  /* Get_n */


/*-------------------------------------------------------------------
 * Function:   Generate_list
 * Purpose:    Fill local list with random ints and sort
 * Input Args: local_n, my_rank
 * Output Arg: A
 */
void Generate_list(int A[], int local_n, int my_rank, int p) {
   int i;

    srandom(my_rank+1);
    for (i = 0; i < local_n; i++)
       A[i] = random() % RMAX;
    qsort(A, local_n, sizeof(int), Compare);

    /* Fill remainder of array with 0's */
    for (i = local_n; i < p*local_n; i++)
       A[i] = 0;

}  /* Generate_list */


/*-------------------------------------------------------------------
 * Function:   Print_global_list
 * Purpose:    Print the contents of a distributed list
 * Input args:  
 *    A: the local list
 *    local_n: the number of elements in each local list
 *    my_rank, p, comm: the usual
 */
void Print_global_list(int A[], int local_n, int my_rank, int p, 
      MPI_Comm comm) {
   int* global_A = NULL;

   if (my_rank == 0) {
      global_A = malloc(p*local_n*sizeof(int));
      MPI_Gather(A, local_n, MPI_INT, global_A, local_n, MPI_INT, 0,
            comm);
      Print_list(global_A, p*local_n);
      free(global_A);
   } else {
      MPI_Gather(A, local_n, MPI_INT, global_A, local_n, MPI_INT, 0,
            comm);
   }

}  /* Print_global_list */


/*-------------------------------------------------------------------
 * Function:    Compare
 * Purpose:     Compare 2 ints, return -1, 0, or 1, respectively, when
 *              the first int is less than, equal, or greater than
 *              the second.  Used by qsort.
 */
int Compare(const void* a_p, const void* b_p) {
   int a = *((int*)a_p);
   int b = *((int*)b_p);

   if (a < b)
      return -1;
   else if (a == b)
      return 0;
   else /* a > b */
      return 1;
}  /* Compare */

/*-------------------------------------------------------------------
 * Function:  Print_list
 * Purpose:   Print a list of ints to stdout
 * In args:
 *    A:  the list
 *    n:  the number of elements in the list
 */
void Print_list(int A[], int n) {
   int i;
   for (i = 0; i < n; i++)
      printf("%d ", A[i]);
   printf("\n");

}  /* Print_list */


/*-------------------------------------------------------------------
 * Function:  Merge_sort
 * Purpose:   Parallel merge sort:  starts with a distributed 
 *            collection of sorted lists, ends with a global
 *            sorted list on process 0.  Uses tree-structured
 *            communication.
 * In args:   local_n:  number of elements contributed by each process
 *            my_rank, p, comm:  the usual
 *
 * In/out arg:  A: each process's local sorted list on input
 *                 global sorted list on process 0 on output
 *                 
 * Note that each process has allocated storage for p*local_n
 * ints in A.
 */
void Merge_sort(int A[], int local_n, int my_rank, 
         int p, MPI_Comm comm) {
}  /* Merge_sort */


/*-------------------------------------------------------------------
 * Function:  Merge
 * Purpose:   Merge two sorted lists, A, B.  Return result in A.
 *            C is used for scratch.  Both A and B have size elements.
 * In args:    B:  second input array
 *             size:  number of elements in A and B
 * In/out arg: A:  first input array, output array
 * Scratch:    C:  temporary storage for merged lists
 */
void Merge(int A[], int B[], int C[], int size) {
   int ai, bi, ci;

   ai = bi = ci = 0;
   while (ai < size && bi < size)
     if (A[ai] <= B[bi]) {
         C[ci] = A[ai];
         ci++; ai++;
      } else {
         C[ci] = B[bi];
         ci++; bi++;
      }

   if (ai >= size)
      for (; ci < 2*size; ci++, bi++)
         C[ci] = B[bi];
   else
      for (; ci < 2*size; ci++, ai++)
         C[ci] = A[ai];

   memcpy(A, C, 2*size*sizeof(int));

} /* Merge */

//i found the source here
/*source 
http://www.math.ecnu.edu.cn/~jypan/Teaching/ParaComp/Codes_Pacheco/code/primes/mpi_merge_sort1.c*/
