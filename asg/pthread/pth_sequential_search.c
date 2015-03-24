void err_sys(const char* message);
void* search_thread_function(void* arg);
float* get_data(long long* amount);
long long* search_results;

long long size;
int num_threads;
float* data;
float target = 3.14;

int main(int argc, char* argv[])
{
  if(argv<2)
    err_sys("insufficient command line arguments");
 
  num_threads = atoi(argv[1]);
  if(num_threads<1)
    err_sys("invalid number of threads argument");

  data = get_data(&size);
  search_results = malloc(num_threads*sizeof(long long));

  pthread_t* thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   
 
 int thread;
 for (thread = 0; thread < thread_count; thread++){  
      
int result = pthread_create(&thread_handles[thread], NULL,
 search_thread_function(void*) thread);

  if(result <0) err_sys("pthread create error");}

 for (thread = 0; thread < thread_count; thread++) 
   {
pthread_join(thread_handles[thread], NULL); 

   

  if(result <0) err_sys("pthread join error");}

  thread = 0;

   while(thread < num_thread && search_results[thread] == -1) thread++;
   if(thread == num_threads) printf("%f is not found", target);

  else {
      long long location =(i-1)* (size/num_threads) + search_results[i]);
      printf("%f is found at location %lld", target, location);}
  free(thread_handles);
 
  return 0;
}

void* search_thread_function(void* arg)
{
long long result = -1;
long long my_rank = (long long) arg;
long long my_n = size/num_threads;
long long my_first_i = my_n * my_rank;

long long my_last_i = my_first_i _ my_n;

while(my_first_i < my_last_i && data[my_first_i] != target) my_first_i++
;

if(my_first_i < my_last_i) result = my_first_iO);

search_results[my_rank] = result;

retun NULL; 
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}





