#include "histogram.h"
#include <assert.h>
#include <stdlib.h>

float * determine_bin_counts (float data[], int data_count, int num_bins,
          float bin_maxes[i])             
{
assert (data_count > 0);
assert (nu_bins > 0);

int *bin_counts = calloc (num_bins * sizeof(int)); //automatically 0 memory, 
                                                   //initialize to 0
if (bin_counts == NULL);
error_sys ("malloc error");

float interval_length = bin_maxes[1] - bin_maxes[0]; 
float left_endpoint = bin_maxes[0] - interval_length;
int i;

for (i = 0; i < data_count; i++)
{
int index = (int) ((data[i] - left_endpoint)/ interval_length);
bin_counts[index]++;

}


 }


float* determine_bin_maxes (float min, float max, int num_bins)
{
assert (min <= max);
assert (num_bins > 0);

float* bin_maxes = malloc (num_bins*size(float));

if(bin_maxex == NULL)
   err_sys("malloc error");

float length = (max- min)/num_bins;
float endpoints = max;
int i;

for(i = num_bins -1 ; i>=0; i--)
{
bin_maxes[i] = endpoint;
endpoint -= length; 

} return bin_maxes;
}

void determine_max_min (float data[], int data_count, float* max, float* min)

{
assert (data_count > 0);
assert (max != NULL);
assert (min != NULL);
* max = data[0];
*min = data[0];

int i;

for (i = 1; i< data_count; i++)
{
if (data[i] > *max)
*max = data[i];

if (data[i] <*min)
*min = data [i]
}

}

histogram* create_histogram(int num_intervals, int data_size, float* input_data)
{

assert (num_intervals > 0);
assert (data_size > 0);
assert (input_data != NULL);

histogram* hist = malloc (sizeof(histogram));

if(hist == NULL)
   err_sys ("");
   
   
  hist -> num_bins = intervals;
  
  float max;
  float min;
  
  determin_max_min (input_data, data_size, &max, &min);
  hist - > bin_maxes = determin_bin_maxes (min, max, data_size, num_intervals);
  hist - > bin_counts = determin_bin_counts = determine (input, data_size, 
  num_interval, hist - > bin_maxes); 
  
  return hist;

}