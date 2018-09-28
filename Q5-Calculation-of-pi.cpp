#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

int main() {

	omp_set_num_threads(4);
	
	int num_iters=100000;
	double partial_sums[4], pi=0.0, step = 1.0/num_iters;

	for(int i=0; i<4; i++)
		partial_sums[i] = 0.0;

	#pragma omp parallel for
	for(int i=0; i<num_iters; i++) {
		int ID = omp_get_thread_num();
		double x = (i + 0.5)*step;
		partial_sums[ID] += 4.0/(1 + x*x);
	}

	for(int i=0; i<4; i++)
		pi += partial_sums[i];

	pi *= step;
	printf("PI: %0.9lf\n", pi);
}