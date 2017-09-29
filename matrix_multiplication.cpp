#include <bits/stdc++.h>
#include "omp.h"

/*
	int omp_get_thread_num();
	int omp_get_num_threads();
	omp_set_num_threads();
	double omp_get_wtime();
	#pragma omp barrier - wait for all
	#pragma omp barrier - one at a time
*/

using namespace std;
#define N 600

void parallel_mult(int A[N][N], int B[N][N], int res[N][N])
{
	#pragma omp parallel
	{
		//Initializing matrix A
		#pragma omp for
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				A[i][j] = i*N+j;

		//Initializing matrix B
		#pragma omp for
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				B[i][j] = j*N+i;

		//Calculating resultant matrix
		#pragma omp for
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
			{
				res[i][j] = 0;
				for(int k=0; k<N; k++)
					res[i][j] += A[i][k]*B[k][j];
			}
		
	}
}

void non_parallel_mult(int A[N][N], int B[N][N], int res[N][N])
{
	//Initializing matrix A
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			A[i][j] = i*N+j;

	//Initializing matrix B
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			B[i][j] = j*N+i;

	//Calculating resultant matrix
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
		{
			res[i][j]=0;
			for(int k=0; k<N; k++)
				res[i][j] += A[i][k]*B[k][j];
		}
	
}

int main()
{
	int A[N][N], B[N][N], res[N][N];
	double w_timer;

	//Parallel version
	w_timer = omp_get_wtime();
	parallel_mult(A, B, res);
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nParallelising the multiplication algorithm : "<<w_timer<<"s";

	//Non parallel version
	w_timer = omp_get_wtime();
	non_parallel_mult(A, B, res);
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nWithout parallelising                      : "<<w_timer<<"s\n\n";
}