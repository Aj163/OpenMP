#include <omp.h>
#include <bits/stdc++.h>
using namespace std;

#define SIZE 100000
int flag = 0;

void fill_rand(int N,double A[]) {
	for(int i=0;i<N;++i)
		A[i] = (rand()%100) *1.0/ (rand()%100 +1);
	printf("Producer populated data\n");
	#pragma omp flush
	flag = 1;

	#pragma omp flush(flag)
}

double Sum_array(int N,double A[]) {

	double sum = 0.0;
	int p_flag;
	while(1) {
		p_flag = 0;
		#pragma omp flush(flag)
		p_flag = flag;

		if(p_flag)
			break;
	}

	#pragma omp flush
	for(int i=0;i<N;++i)
		sum = sum + A[i];
	
	printf("Consumer calculated Array sum\n");
	return sum;
}

double parallel_prod_cons() {

	double A[SIZE];
	double  sum = 0.0;
	omp_set_num_threads(2);
	#pragma omp parallel sections
	{
		#pragma omp section
			fill_rand(SIZE,A);

		#pragma omp section
			sum = Sum_array(SIZE,A);
	}

	return sum;
}

int main() {

	double sum;

	//Parallel Producer-Consumer
	sum = parallel_prod_cons();
	printf("Parallel code gives sum %0.2lf for an array of size %d\n", sum, SIZE);
}