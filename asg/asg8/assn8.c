#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
 
int main(int argc, char* argv[])
{
    long n_tosses  = strtol(argv[1], NULL, 10);;                    //number of iterations per FOR loop
    //int myid, nprocs;                       //holds process's rank id
    double x,y;                     //x,y value for the random coordinate
    int i;                          //loop counter
    int count=0;                //Count holds all the number of how many good coordinates
     double pi;                      //holds approx value of pi
    long long int local_count = 0;   
  int numthreads = strtol(argv[2], NULL, 10);
        time_t start, stop; time(&start);
        srand((unsigned)time(NULL));
    //MPI_Init(&argc, &argv);                 //Start MPI
    //MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //get rank of node's process
    //MPI_Comm_size(MPI_COMM_WORLD, &nprocs);        //Gets number of nodes availible to process
 
    
        //Start OpenMP code: 16 threads/node
        #pragma omp parallel num_threads(numthreads)
        {
            #pragma omp master
           {

                int myid = omp_get_thread_num(); 
                numthreads = omp_get_num_threads();       
           }
        # pragma omp parallel private(x, y, i) reduction(+:local_count)   
        for (i = 0; i < n_tosses; i ++) {
        x = (double) rand() / (RAND_MAX);
        y = (double) rand() / (RAND_MAX);
        if ((x*x + y*y) <= 1)
            {
            local_count++;//printf("local_count %d\n", local_count);
            }
    }}
    
   // MPI_Barrier(MPI_COMM_WORLD);
    //MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //MPI_Barrier(MPI_COMM_WORLD);
    #pragma omp master
    {   
        printf("count %d, samples %ld \n", count, n_tosses);
        pi = 4 * local_count / n_tosses;
        time(&stop);
       // printf("results with %d processes:\n", nprocs);
        printf("estimated pi = %f\n", pi);
        printf("finished in about = %g seconds\n", difftime(stop, start));
    }
 
    //MPI_Finalize();                     //Close the MPI instance
    return 0;
}
