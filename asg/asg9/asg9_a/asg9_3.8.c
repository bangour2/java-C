#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);
void Print_list(int world_rank, int keys, int* sorted,
int n, int* global_list, int* global_list_tmp, int* local_list);

void Print_global_list(int world_rank, int* gloabal_list, int  n);


int main(int argc, char** argv) {

int data = 10000;

int c;
srand(time(NULL)); //random generator
int world_rank;
int world_size;

int* local_list = NULL;
int* tmp_array = NULL;
int* sorted = NULL;
int* global_list = NULL;
int* global_list_tmp = NULL;
int n = 42, keys;

 int array[n];
 sorted = malloc (n* sizeof(int));
 global_list =malloc(n*sizeof(int));

//mpi intialization
MPI_INIT(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


if(world_rank == 0) //master process
{
 // printf("What's n?\n");
      //scanf("%d", &n);
 MPI_Bcast(array, n, MPI_INT, 0, MPI_COMM_WORLD); //broadcast n to all processes
}
 keys = n/world_size; //each process gets
  local_list = malloc (keys * sizeof(int));

  sleep(1/25);MPI_Barrier(MPI_COMM_WORLD);
  printf("unsorted numbers \n");
  for(c = 0; c < keys; c++){
    local_list[c] = rand() % data; //random number
    printf("my_values %d, my_rank %d \n", local_list[c], world_rank);}
    printf("\n\n");printf("\n");

  tmp_array = malloc(keys * sizeof(int));
  mergeSort(local_list, tmp_array, 0, (keys - 1));

  //master process gets local_list
  MPI_Gather(local_list, keys, MPI_INT, sorted, keys, MPI_INT, 0, MPI_COMM_WORLD);

  Print_list(world_rank, keys, sorted, n, global_list, global_list_tmp, local_list);
 // Print_global_list(world_rank, global_list, n);

//clean up
free(tmp_array);
free(sorted);
free(local_list);
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
}}  

/********** Merge Function **********/
void mergeSort(int *a, int *b, int l, int r) {
int m;
if(l < r) {
m = (l + r)/2;
mergeSort(a, b, l, m);
mergeSort(a, b, (m + 1), r);
merge(a, b, l, m, r);    
}}               

void Print_list(int world_rank, int keys, int* sorted,
 int n, int* global_list, int* global_list_tmp, int*  local_list){

 int c;                     
 if(world_rank == 0)
 {    
   int z =1;
   for(c=0; c< keys; c++)
     printf("my_values %d my_rank %d \n", sorted[c], world_rank);
   printf("\n\n");printf("\n");

 for(c =0; c< n; c++){
  global_list_tmp = malloc(n*sizeof(int));
  global_list[c] = local_list[c];             
  if(c==z && z%keys ==0) {merge(global_list, global_list_tmp, 0, (z/2), z);z=z+keys;}}

}}            

void Print_global_list(int world_rank, int* global_list, int  n){
  int c;                
 int c;                 
  if(world_rank ==0){
   for(c=0; c< n; c++)
     printf("%d \n", global_list[c]);}                
}
 




