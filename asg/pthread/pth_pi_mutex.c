const int MAX_THREADS = 1024;

long thread_count;
long long n;
double sum;
pthread_mutex_t mutex;


void* Thread_sum(void* rank);
/* executed by main thread */
void Get_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
   long  thread;  
   pthread_t* thread_handles;
   Get_args(argc, argv);

   thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
   pthread_mutex_init(&mutex, NULL);
   sum = 0.0;

 for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Thread_sum, (void*)thread);  

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

pthread_mutex_destroy(&mutex); // for mutex
   free(thread_handles);
   return 0;
} 

void* Thread_sum(void* rank) {
   long my_rank = (long) rank;
   double factor;
   long long i;
   long long my_n = n/thread_count;
   long long my_first_i = my_n*my_rank;
   long long my_last_i = my_first_i + my_n;
   double my_sum = 0.0;

   if (my_first_i % 2 == 0)
      factor = 1.0;
   else
      factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
      my_sum += factor/(2*i+1);
   }
   pthread_mutex_lock(&mutex);
   sum += my_sum;
   pthread_mutex_unlock(&mutex);

   return NULL;
}  

void Get_args(int argc, char* argv[]) {
   if (argc != 3) printf("argument error");
   thread_count = strtol(argv[1], NULL, 10);  
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
   n = strtoll(argv[2], NULL, 10);
   if (n <= 0) Usage(argv[0]);
}  