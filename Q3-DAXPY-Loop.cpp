#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

#define N (1<<25)

void DAXPY(int numThreads, float *X, float *Y, float *Z, float a) {

    omp_set_num_threads(numThreads);
    #pragma omp parallel for
    for(int i=0; i<N; i++)
        Z[i] = a*X[i] + Y[i];
}

int main() {

    float *X, *Y, a, *Z;

    X = new float[N];
    Y = new float[N];
    Z = new float[N];

    for(int i=0; i<N; i++) {
        X[i] = (rand()%N) * 1.0 / (rand()%N +1);
        Y[i] = (rand()%N) * 1.0 / (rand()%N +1);
    }

    a = (rand()%N) * 1.0 / (rand()%N +1);

    double w_timer = omp_get_wtime();
    DAXPY(1, X, Y, Z, a);
    w_timer = (double)omp_get_wtime() - w_timer;
    printf("Sequential Execution: %0.2lf ms\n\n", 1000.0*w_timer);

    for(int numThreads=2; numThreads<=10000; numThreads*=1.5) {
        w_timer = omp_get_wtime();
        DAXPY(numThreads, X, Y, Z, a);
        w_timer = (double)omp_get_wtime() - w_timer;
        printf("%5d Threads - Execution Time: %0.2lf ms\n", numThreads, 1000.0*w_timer);
    }

    delete[] X, Y, Z;
}