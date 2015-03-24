#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "time.h"


int main(int argc, char* argv[]) {

    int nprocs, myID;
     //mpi initialization
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        fprintf(stderr, "MPI initialization error\n");
        return EXIT_FAILURE;}

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myID);

    if (argc != 3)  {

    if (argc != 3)  {
        fprintf(stderr, "#of arguments error");
        MPI_Finalize(); exit(EXIT_FAILURE);}

    long num_samples = 16000000;// strtol(argv[1], NULL, 10);
    long partial_num_samples = num_samples/nprocs;

      //time initialization
      time_t start, stop; time(&start);

    /* do calculation */
    //srand((unsigned int) seed);
    srand(time(NULL));       
    int count = 0, i = 0;
    int local_count = 0;
    double x, y;
    double pi = 0;


   // for (int i = myID; i < num_samples; i += nprocs) {
      for(i=0; i< partial_num_samples; i++){
        x = (double) rand() / (double) (RAND_MAX);           
        y = (double) rand() / (double) (RAND_MAX);
        if ((x*x + y*y) <= 1.0)
            ++local_count; 
    }
    MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myID == 0)      
        pi = 4.0 * (double) count / (double) partial_num_samples;

       time(&stop);      

        if (myID == 0) {
        printf(" %d processes:\n", nprocs);
        printf("number of samples = %ld, processes = %d\n", num_samples, nprocs);

   // for (int i = myID; i < num_samples; i += nprocs) {
      for(i=0; i< partial_num_samples; i++){
        x = (double) rand() / (double) (RAND_MAX);           
        y = (double) rand() / (double) (RAND_MAX);
        if ((x*x + y*y) <= 1.0)
            ++local_count; 
    }
    MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myID == 0)      
        pi = 4.0 * (double) count / (double) partial_num_samples;

       time(&stop);      

        if (myID == 0) {
        printf(" %d processes:\n", nprocs);
        printf("number of samples = %ld, processes = %d\n", num_samples, nprocs);


 printf("estimated pi = %12.10f\n", pi);
        printf("finished in about = %g seconds \n", difftime(stop, start));
       }

    MPI_Finalize();
    return EXIT_SUCCESS;       
}

