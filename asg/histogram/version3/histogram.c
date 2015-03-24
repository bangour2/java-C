#include "histogram.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int* bin_counts;
float* bin_maxes;
float* data;
int num_bins;
int data_count;
float min, max;
int num_threads;
int** global_bin_array;
sem_t* global_bin_empty_sem;
sem_t* global_bin_full_sem;
float* global_max_array;
float* global_min_array;
sem_t* global_max_min_empty_sem;
sem_t* global_max_min_full_sem;

/***************************************************************************/

void err_sys (const char* message)
{
  printf ("%s\n", message);
  exit (0);
}

/****************************************************************************/

int* create_bin_counts ()
{
  assert (num_bins > 0);
  int* bin_counts = malloc (num_bins * sizeof (int));
  if (bin_counts == NULL)
    err_sys ("malloc error");
  int i;
  for (i = 0; i < num_bins; i++)
    bin_counts[i] = 0;
  return bin_counts;
}

/**************************************************************************/

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
  int result;
  int done = 0;
  int power = 2;
  do
  {
    if (my_rank % power != 0)
    {
      result = sem_wait (&global_max_min_empty_sem[my_rank - power/2]);
      if (result != 0)
	err_sys ("sem wait error");
      global_max_array[my_rank - power/2] = my_max;
      global_min_array[my_rank - power/2] = my_min;
      result = sem_post (&global_max_min_full_sem[my_rank - power/2]);
      if (result != 0)
	err_sys ("sem post error");
      done = 1;
    }
    else
    {
      result = sem_wait (&global_max_min_full_sem [my_rank]);
      if (result != 0)
	err_sys ("sem wait error");
      if (global_max_array[my_rank] > my_max)
	my_max = global_max_array[my_rank];
      if (global_min_array[my_rank] < my_min)
	my_min = global_min_array[my_rank];
      result = sem_post (&global_max_min_empty_sem [my_rank]);
      if (result != 0)
	err_sys ("sem post error");
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

/*************************************************************************/
void determine_max_min ()
{
  global_max_min_empty_sem = malloc (sizeof (sem_t) * num_threads);
  if (global_max_min_empty_sem == NULL)
    err_sys ("malloc error");
  int result;
  int i;
  for (i = 0; i < num_threads; i++)
  {
    result = sem_init (&global_max_min_empty_sem[i], 0, 1);
    if (result != 0)
      err_sys ("sem init error");
  }
  global_max_min_full_sem = malloc (sizeof (sem_t) * num_threads);
  if (global_max_min_full_sem == NULL)
    err_sys ("malloc error");
  for (i = 0; i < num_threads; i++)
  {
    result = sem_init (&global_max_min_full_sem[i], 0, 0);
    if (result != 0)
      err_sys ("sem init error");
  }
  global_max_array = malloc (num_threads * sizeof(float));
  if (global_max_array == NULL)
    err_sys ("malloc error");
  global_min_array = malloc (num_threads * sizeof(float));
  if (global_min_array == NULL)
    err_sys ("malloc error");
  pthread_t* thread_handles = malloc (num_threads * sizeof (pthread_t));
  if (thread_handles == NULL)
    err_sys ("malloc error");
  for (i = 0; i < num_threads; i++)
  {
    result = pthread_create (&thread_handles[i], NULL, 
		    thread_determine_max_min, ((void*)i));
    if (result != 0)
      err_sys ("pthread create error");
  }
  for (i = 0; i < num_threads; i++)
  {
    result = pthread_join (thread_handles[i], NULL);  
    if (result != 0)
      err_sys ("pthread join error");
  }
  free (thread_handles);
  free (global_max_array);
  free (global_min_array);
  free (global_max_min_empty_sem);
  free (global_max_min_full_sem);
}

/****************************************************************************/

float* determine_bin_maxes (float min, float max, int data_count, int num_bins)
{
  assert (min <= max);
  assert (data_count > 0);
  assert (num_bins > 0);
  float* bin_maxes = malloc (data_count * sizeof (float));
  if (bin_maxes == NULL)
    err_sys ("malloc error");
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

/************************************************************************/

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
  int result;
  int done = 0;
  int power = 2;
  do
  {
    if (my_rank % power != 0)
    {
      result = sem_wait (&global_bin_empty_sem[my_rank - power/2]);
      if (result != 0)
	err_sys ("sem wait error");
      global_bin_array[my_rank - power/2] = my_bins;
      result = sem_post (&global_bin_full_sem[my_rank - power/2]);
      if (result != 0)
	err_sys ("sem post error");
      done = 1;
    }
    else
    {
      result = sem_wait (&global_bin_full_sem [my_rank]);
      if (result != 0)
	err_sys ("sem wait error");
      int i;
      for (i = 0; i < num_bins; i++)
	my_bins[i] += global_bin_array[my_rank][i];
      result = sem_post (&global_bin_empty_sem [my_rank]);
      if (result != 0)
	err_sys ("sem post error");
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

/*************************************************************************/

void determine_bin_counts ()
{
  global_bin_empty_sem = malloc (sizeof (sem_t) * num_threads);
  if (global_bin_empty_sem == NULL)
    err_sys ("malloc error");
  int result;
  int i;
  for (i = 0; i < num_threads; i++)
  {
    result = sem_init (&global_bin_empty_sem[i], 0, 1);
    if (result != 0)
      err_sys ("sem init error");
  }
  global_bin_full_sem = malloc (sizeof (sem_t) * num_threads);
  for (i = 0; i < num_threads; i++)
  {
    result = sem_init (&global_bin_full_sem[i], 0, 0);
    if (result != 0)
      err_sys ("sem init error");
  }
  global_bin_array = malloc (num_threads * sizeof (int*));
  if (global_bin_array == NULL)
    err_sys ("malloc error");
  pthread_t* thread_handles = malloc (num_threads * sizeof (pthread_t));
  if (thread_handles == NULL)
    err_sys ("malloc error");
  for (i = 0; i < num_threads; i++)
  {
    result = pthread_create (&thread_handles[i], NULL, 
		    thread_determine_bin_counts, ((void*)i));
    if (result != 0)
      err_sys ("pthread create error");
  }
  for (i = 0; i < num_threads; i++)
  {
    result = pthread_join (thread_handles[i], NULL);
    if (result != 0)
      err_sys ("pthread join error");
  }
    for (i = 0; i < num_threads; i++)
  {
    result = sem_destroy (&global_bin_empty_sem[i]);
    if (result != 0)
      err_sys ("sem destroy error");
    result = sem_destroy (&global_bin_full_sem[i]);
    if (result != 0)
      err_sys ("sem destroy error");
  }
  free (global_bin_empty_sem);
  free (global_bin_full_sem);
  free (global_bin_array);
  free (thread_handles);
}
/*************************************************************************/
//function struct
histogram* create_histogram (int num_intervals, int data_size, 
			     float* input_data, int threads)
{
  assert (num_intervals > 0);
  assert (threads > 0);
  assert (data_size > 0);
  assert (input_data != NULL);
  histogram* hist = malloc (sizeof(histogram)); //allocation
  if (hist == NULL)
    err_sys ("malloc error");
  hist -> num_bins = num_intervals;
  num_bins = num_intervals;
  data = input_data;
  data_count = data_size;
  num_threads = threads;
  bin_counts = create_bin_counts ();
  determine_max_min ();
  bin_maxes = determine_bin_maxes (min, max, data_count, num_bins); 
  determine_bin_counts ();
  hist -> bin_counts = bin_counts;
  hist -> bin_maxes = bin_maxes;
  return hist;
}

/***************************************************************************/

void display_histogram (const histogram* hist)
{
  assert (hist != NULL);
  float length = hist -> bin_maxes[1] - hist -> bin_maxes[0];
  float left = hist -> bin_maxes[0] - length;
  int i;
  for (i = 0; i < hist -> num_bins; i++)
  {
    printf ("%f - %f: %d\n", left, hist -> bin_maxes[i], hist -> bin_counts[i]);
    left += length;
  }
}

/****************************************************************************/

void destroy_histogram (histogram* hist)
{
  assert (hist != NULL);
  if (hist -> bin_maxes != NULL)
    free (hist -> bin_maxes);
  if (hist -> bin_counts != NULL)
    free (hist -> bin_counts);
  free (hist);
}
