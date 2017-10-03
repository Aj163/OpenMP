#include <bits/stdc++.h>
#include "omp.h"

/*
	int omp_get_thread_num();
	int omp_get_num_threads();
	omp_set_num_threads();
	double omp_get_wtime();
	#pragma omp barrier - wait for all
	#pragma omp critical - one at a time
*/

using namespace std;

void countSortNonParallel(int arr[], int n, int expo);
void radixSortNonParallel(int arr[], int n);

void countSortParallel(int arr[], int n, int expo);
void radixSortParallel(int arr[], int n);

int main()
{
	double w_timer;
	int n = 1000000;
	int arr[n];

	//Non parallel version
	w_timer = omp_get_wtime();
	radixSortNonParallel(arr, n);
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nWithout parallelising Radix sort       : "<<w_timer<<"s";

	//Parallel version
	w_timer = omp_get_wtime();
	radixSortParallel(arr, n);
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nParallelising the Radix sort algorithm : "<<w_timer<<"s\n\n";

	
}

void countSortParallel(int arr[], int n, int expo)
{
	// A function to do counting sort of arr[] according to
	// the digit represented by exp.

	int output[n]; // output array
	int i, ctr_odd=0, ctr_even=0, count[2];

	// Store count of occurrences in count[]
	#pragma omp parallel for reduction ( + : ctr_even, ctr_odd)
	for(i = 0; i < n; i++)
	{
		if((arr[i] & expo) == 0)
			ctr_even++;
		else
			ctr_odd++;
	}

	// Store count of occurrences in count[]
	count[0] = ctr_even;
	count[1] = ctr_odd;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	count[1] += count[0];

	// Build the output array
	for(i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] & expo)/expo] - 1] = arr[i];
		count[(arr[i] & expo)/expo]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	#pragma omp parallel for
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}
 

void radixSortParallel(int arr[], int n)
{
	// The main function to that sorts arr[] of size n using 
	// Radix Sort

	//init
	//#pragma omp parallel for
	for(int i=0; i<1000000; i++)
		arr[i] = 1000000-i;

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 2^i
	// where i is current digit number in binary
	// Total number of bits is 31
	for(int expo = 0; expo<5; expo++)
		countSortParallel(arr, n, (1<<expo));
}

void countSortNonParallel(int arr[], int n, int expo)
{
	// A function to do counting sort of arr[] according to
	// the digit represented by exp.

	int output[n]; // output array
	int i, ctr_odd=0, ctr_even=0, count[2];
	
	// Store count of occurrences in count[]
	for(i = 0; i < n; i++)
	{
		if((arr[i] & expo) == 0)
			ctr_even++;
		else
			ctr_odd++;
	}

	// Store count of occurrences in count[]
	count[0] = ctr_even;
	count[1] = ctr_odd;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	count[1] += count[0];

	// Build the output array
	for(i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] & expo)/expo] - 1] = arr[i];
		count[(arr[i] & expo)/expo]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}
 

void radixSortNonParallel(int arr[], int n)
{
	// The main function to that sorts arr[] of size n using 
	// Radix Sort

	//init
	for(int i=0; i<1000000; i++)
		arr[i] = 1000000-i;

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 2^i
	// where i is current digit number in binary
	// Total number of bits is 31
	for(int expo = 0; expo<5; expo++)
		countSortNonParallel(arr, n, (1<<expo));
}