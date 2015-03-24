#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <pthread.h>
#include <semaphore.h>

int* bin_counts;
float* bin_maxes;
float* data;
int num_bins;
int data_count;
float min, max;
int num_threads;
pthread_t* thread_handles;
int** global_bin_array;

sem_t* global_bin_empty_sem;

sem_t* global_bin_full_sem;

float* global_max_array;

float* global_min_array;

sem_t* global_max_min_empty_sem;

sem_t* global_max_min_full_sem;

void err_sys (const char* message);

float* get_data (int* data_count);

void determine_max_min ();

float* determine_bin_maxes (float min, float max, int  data_count, 
			    int num_bins);

void display_bin_counts (int* bin_counts, float* bin_maxes, int num_bins);

void* thread_determine_bin_counts (void* rank);

int* create_bin_counts ();

void* thread_determine_max_min (void* rank);

int main (int argc, char* argv[])
{
  if (argc < 3)
    err_sys ("invalid number of command line arguments");
  num_bins = atoi (argv[1]);
  if (num_bins <= 0)
    err_sys ("invalid data_count command line argument");
  num_threads = atoi (argv[2]);
  if (num_threads <= 0)
    err_sys ("invalid number of threads command line argument");
  data = get_data (&data_count); 
  thread_handles = malloc (num_threads * sizeof (pthread_t));
  int i;
  global_max_min_empty_sem = malloc (sizeof (sem_t) * num_threads);
  for (i = 0; i < num_threads; i++)
    sem_init (&global_max_min_empty_sem[i], 0, 1);
  global_max_min_full_sem = malloc (sizeof (sem_t) * num_threads);
  for (i = 0; i < num_threads; i++)
    sem_init (&global_max_min_full_sem[i], 0, 0);
  global_max_array = malloc (num_threads * sizeof(float));
  global_min_array = malloc (num_threads * sizeof(float));
  determine_max_min ();
  bin_maxes = determine_bin_maxes (min, max, data_count, num_bins);
  bin_counts = create_bin_counts();
  global_bin_empty_sem = malloc (sizeof (sem_t) * num_threads);
  for (i = 0; i < num_threads; i++)
    sem_init (&global_bin_empty_sem[i], 0, 1);
  global_bin_full_sem = malloc (sizeof (sem_t) * num_threads);
  for (i = 0; i < num_threads; i++)
    sem_init (&global_bin_full_sem[i], 0, 0);
  global_bin_array = malloc (num_threads * sizeof (int*));  
  for (i = 0; i < num_threads; i++)
    pthread_create (&thread_handles[i], NULL, 
		    thread_determine_bin_counts, ((void*)i));
  for (i = 0; i < num_threads; i++)
    pthread_join (thread_handles[i], NULL);
  display_bin_counts (bin_counts, bin_maxes, num_bins);
  int sum = 0;
  for (i = 0; i < num_bins; i++)
    sum += bin_counts[i];
  for (i = 0; i < num_threads; i++)
  {
    sem_destroy (&global_bin_empty_sem[i]);
    sem_destroy (&global_bin_full_sem[i]);
  }
  free (data);
  free (global_bin_empty_sem);
  free (global_bin_full_sem);
  free (bin_counts);
  free (global_bin_array);
  free (thread_handles);
  free (bin_maxes);
  free (global_max_array);
  free (global_min_array);
  free (global_max_min_empty_sem);
  free (global_max_min_full_sem);
printf ("min: %f max: %f\n", min, max);
  return 0;
}

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

 float* get_data (int* data_count)
 {
   *data_count = 100000;
   float* data = malloc (*data_count * sizeof (float));
   srand(0);
   int i;
   for (i = 0; i < *data_count; i++)
     data[i] = ((float)rand()/(float)(RAND_MAX)) * 10000;
   return data;
 }

void determine_max_min ()
{
  int i;
  for (i = 0; i < num_threads; i++)
    pthread_create (&thread_handles[i], NULL, 
		    thread_determine_max_min, ((void*)i));
  for (i = 0; i < num_threads; i++)
    pthread_join (thread_handles[i], NULL);  
}

float* determine_bin_maxes (float min, float max, int data_count, int num_bins)
{
  float* bin_maxes = malloc (data_count * sizeof (float));
  float length = (max - min) / num_bins;
  float endpoint = max;
  int i;
  for (i = num_bins - 1; i >= 0; i--)
  {
    bin_maxes [i] = endpoint;
    endpoint -= length;
  }
  return bin_maxes;
}    

void display_bin_counts (int* bin_counts, float* bin_maxes, int num_bins)
{
  float length = bin_maxes[1] - bin_maxes[0];
  float left = bin_maxes[0] - length;
  int i;
  for (i = 0; i < num_bins; i++)
  {
    printf ("%f - %f: %d\n", left, bin_maxes[i], bin_counts[i]);
    left += length;
  }
}

void* thread_determine_bin_counts (void* rank)
{
  int my_rank = (int)rank;
  int my_num_data = data_count / num_threads;
  int my_first = my_num_data * my_rank;
  int my_last = my_first + my_num_data;
  int* my_bins = create_bin_counts();
  float interval_length = bin_maxes[1] - bin_maxes[0];
  float left_endpoint = bin_maxes[0] - interval_length;
  int i = 0;
  for (i = my_first; i < my_last; i++)
  {
    int index = (int)((data[i] - left_endpoint) / interval_length);
    my_bins[index]++;
  }
  
  int done = 0;
  int power = 2;
  do
  {
    if (my_rank % power != 0)
    {
      sem_wait (&global_bin_empty_sem[my_rank - power/2]);
      global_bin_array[my_rank - power/2] = my_bins;
      sem_post (&global_bin_full_sem[my_rank - power/2]);
      done = 1;
    }
    else
    {
      sem_wait (&global_bin_full_sem [my_rank]);
      int i;
      for (i = 0; i < num_bins; i++)
	my_bins[i] += global_bin_array[my_rank][i];
      sem_post (&global_bin_empty_sem [my_rank]);
      free (global_bin_array[my_rank]);
      if (power >= num_threads)
	done = 1;
      else
	power *= 2;
    }
  }
  while (!done);
  if (my_rank == 0)
  {
    int i;
    for (i = 0; i < num_bins; i++)
      bin_counts[i] = my_bins[i];
  }
  return NULL;
}

int* create_bin_counts ()
{
  int* bin_counts = malloc (num_bins * sizeof (int));
  int i;
  for (i = 0; i < num_bins; i++)
    bin_counts[i] = 0;
  return bin_counts;
}

void* thread_determine_max_min (void* rank)
{
  int my_rank = (int)rank;
  int my_num_data = data_count / num_threads;
  int my_first = my_num_data * my_rank;
  int my_last = my_first + my_num_data;
  float my_min = data[my_first];
  float my_max = data[my_first];;
  int i;
  for (i = my_first + 1; i < my_last; i++)
  {
    if (data[i] < my_min)
      my_min = data[i];
    if (data[i] > my_max)
      my_max = data[i];
  }

  int done = 0;
  int power = 2;
  do
  {
    if (my_rank % power != 0)
    {
      sem_wait (&global_max_min_empty_sem[my_rank - power/2]);
      global_max_array[my_rank - power/2] = my_max;
      global_min_array[my_rank - power/2] = my_min;
      sem_post (&global_max_min_full_sem[my_rank - power/2]);
      done = 1;
    }
    else
    {
      sem_wait (&global_max_min_full_sem [my_rank]);
      if (global_max_array[my_rank] > my_max)
	my_max = global_max_array[my_rank];
      if (global_min_array[my_rank] < my_min)
	my_min = global_min_array[my_rank];
      sem_post (&global_max_min_empty_sem [my_rank]);
      if (power >= num_threads)
	done = 1;
      else
	power *= 2;
    }
  }
  while (!done);
  if (my_rank == 0)
  {
    max = my_max;
    min = my_min;
  }
  return NULL;
}
