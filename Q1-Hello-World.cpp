#include <bits/stdc++.h>
#include "omp.h" /* OpenMP compiler directives, APIs are declared here */
using namespace std;

int main() {

    /* Parallel region begins here */
    #pragma omp parallel
    {
        printf("Hello World!\n");
    }
}