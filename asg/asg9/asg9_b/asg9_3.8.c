#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char** argv) {

int data = 10000;
int n = 256; //strtol(argv[1], NULL, 10);
int array[n];

int c;
srand(time(NULL));
int world_rank;
int world_size;   

int* sorted = malloc (n* sizeof(int));
int* local_list = NULL;
int* tmp_array = NULL;

//mpi intialization
MPI_INIT(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
int keys = n/world_size;

printf("size %d rank %d \n", world_size, world_rank);

if(world_rank == 0) //master
{                 
 MPI_Bcast(array, n, MPI_INT, 0, MPI_COMM_WORLD);
}              
else
{
  local_list = malloc (keys * sizeof(int));

  printf("unsorted numbers \n");
  for(c = 0; c < keys; c++){               
    local_list[c] = rand() % data;         
    printf("my_values %d, my_rank %d \n", local_list[c], world_rank);}
    printf("\n\n");printf("\n");

  tmp_array = malloc(keys * sizeof(int));
  mergeSort(local_list, tmp_array, 0, (keys - 1));

  MPI_Gather(local_list, keys, MPI_INT, sorted, keys, MPI_INT, world_rank, MPI_$
//MPI_Barrier(MPI_COMM_WORLD);
}

if(world_rank == 0)
{
  printf("sorted \n");                     
  for(c=0; c< keys; c++)                   
    printf("my_values %d my_rank %d \n", sorted[c], world_rank);      
    printf("\n\n");printf("\n");
}

//clean up
free(tmp_array);
MPI_Finalize();
}
/********** Merge Function **********/
void merge(int *a, int *b, int l, int m, int r) {
int h, i, j, k;
h = l;
i = l;
j = m + 1;
while((h <= m) && (j <= r)) {
if(a[h] <= a[j]) {
b[i] = a[h];
h++;
}
else {
b[i] = a[j];
j++;
}
i++;
}
if(m < h) {
for(k = j; k <= r; k++) {
b[i] = a[k];
i++;
}
}
else {
for(k = h; k <= m; k++) {
b[i] = a[k];
i++;
}
}
for(k = l; k <= r; k++) {
a[k] = b[k];
}
}
/********** Recursive Merge Function **********/
void mergeSort(int *a, int *b, int l, int r) {
int m;
if(l < r) {
m = (l + r)/2;
mergeSort(a, b, l, m);
mergeSort(a, b, (m + 1), r);
merge(a, b, l, m, r);
}
}