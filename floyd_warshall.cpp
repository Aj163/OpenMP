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
#define n 600

int dist[n][n];

void floydWarshallParallel()
{
	//Initialize dist matrix
	#pragma omp parallel for
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if(i!=j)
				dist[i][j] = i*j + (j-i)*(j-i);
			else
				dist[i][j]=0;
		}

	//Floyd-Warshall
	for(int k = 0; k < n; k++)
	{
		#pragma omp parallel for
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
	}
}

void floydWarshallNonParallel()
{
	//Initialize dist matrix
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if(i!=j)
				dist[i][j] = i*j + (j-i)*(j-i);
			else
				dist[i][j]=0;
		}

	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
}

int main()
{
	double w_timer;

	//Parallel version
	w_timer = omp_get_wtime();
	floydWarshallParallel();
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nParallelising the Floyd-Warshall algorithm : "<<w_timer<<"s";

	//Non parallel version
	w_timer = omp_get_wtime();
	floydWarshallNonParallel();
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nWithout parallelising                      : "<<w_timer<<"s\n\n";
}