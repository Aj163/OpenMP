#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

int main() {
	
	int num_iters=100000;
	double pi=0.0, step = 1.0/num_iters;

	omp_set_num_threads(2);
	#pragma omp parallel for reduction (+: pi)
	for(int i=0; i<num_iters; i++) {
		double x = (i + 0.5)*step;
		pi += 4.0/(1 + x*x);
	}

	pi *= step;
	printf("PI: %0.9lf\n", pi);
}