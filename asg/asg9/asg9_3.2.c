/*
Submitted batch job 4536004
login1.stampede(85)$ cat asg9_3.2.o4536004
TACC: Starting up job 4536004
TACC: Setting up parallel environment for MVAPICH2+mpispawn.
TACC: Starting parallel tasks...

  Monte Carlo method of finding PI

    Number of processors : 16
    Number of darts      : 16000000

    Known value of  PI   : 3.1415926535
    Average value of PI  : 3.1410085781
    Percentage Error     : 0.01859170
    Time elapsed (sec)   : 1.62923121

 
TACC: Shutdown complete. Exiting.
*/                   

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define MASTER             0   /* Process ID of MASTER                      */
#define PI      3.1415926535   /* Known vaue of PI                          */
#define NDARTS  16000000   /* Number of darts thrown                    */
double pseudo_random(double a, double b) {

  double r;  /* Random number */
  r = ((b - a) * ((double) rand()/(double) RAND_MAX)) + a;

  return r;
}

int main (int argc, char *argv[]) {

  int    proc_id,       /* Process ID                           */
         n_procs,       /* Number of processors                 */
         llimit,        /* Lower limit for random numbers       */
         ulimit,        /* Upper limit for random numbers       */
         n_circle,      /* Number of darts that hit the circle  */

        ulimit,        /* Upper limit for random numbers       */
         n_circle,      /* Number of darts that hit the circle  */
         i;      

  double pi_current,    /* PI calculated by each WORKER         */
         pi_sum,        /* Sum of PI values from each WORKER    */
         x,
         y,
         z,
         start_time,
         end_time;

  struct timeval stime;

  llimit   = -1;
  ulimit   = 1;
  n_circle = 0;

  /* INITIALIZE MPI */
  MPI_Init(&argc, &argv);

  /* GET THE PROCESS ID AND NUMBER OF PROCESSORS */               
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

  if (proc_id == MASTER) {
    printf("\n  Monte Carlo method of finding PI\n\n");
    printf("    Number of processors : %d\n", n_procs);
    printf("    Number of darts      : %d\n\n", NDARTS);

    start_time = MPI_Wtime();
}

  for (i = 1; i <= NDARTS; i++) {

    x = pseudo_random(llimit, ulimit);
    y = pseudo_random(llimit, ulimit);

    z = pow(x, 2) + pow(y, 2);

    if (z <= 1.0) {
       n_circle++;}      
} 

  pi_current = 4.0 * (double)n_circle/(double)NDARTS;

 MPI_Reduce(&pi_current, &pi_sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD$


  if (proc_id == MASTER) {

    pi_sum = pi_sum / n_procs;
    end_time = MPI_Wtime();

    printf("    Known value of  PI   : %11.10f\n", PI);
    printf("    Average value of PI  : %11.10f\n", pi_sum);
    printf("    Time elapsed (sec)   : %10.8f\n\n", end_time - start_time);
  }

  /* FINALIZE MPI */          
  MPI_Finalize();

  return 0;              
 }



