#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

#define N (1<<9)

void matrix_multiply(int numThreads, float (*X)[N], float (*Y)[N], float (*Z)[N]) {

    omp_set_num_threads(numThreads);
    #pragma omp parallel for
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            Z[i][j] = 0.0;
            for(int k=0; k<N; k++)
                Z[i][j] += X[i][k] * Y[k][j];
        }

}

int main() {

    auto X = new float[N][N];
    auto Y = new float[N][N];
    auto Z = new float[N][N];

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            X[i][j] = (rand()%N) * 1.0 / (rand()%N +1);
            Y[i][j] = (rand()%N) * 1.0 / (rand()%N +1);
        }
    }

    double w_timer = omp_get_wtime();
    matrix_multiply(1, X, Y, Z);
    w_timer = (double)omp_get_wtime() - w_timer;
    printf("Sequential Execution: %0.2lf ms\n\n", 1000.0*w_timer);

    for(int numThreads=2; numThreads<=10000; numThreads*=1.5) {
        w_timer = omp_get_wtime();
        matrix_multiply(numThreads, X, Y, Z);
        w_timer = (double)omp_get_wtime() - w_timer;
        printf("%5d Threads - Execution Time: %0.2lf ms\n", numThreads, 1000.0*w_timer);
    }

    delete[] X, Y, Z;
}