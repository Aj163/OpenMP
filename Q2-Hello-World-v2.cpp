#include <bits/stdc++.h>
#include "omp.h" /* OpenMP compiler directives, APIs are declared here */
using namespace std;

void printHello(int threadID) {
	printf("Thread %d : Hello World!\n", threadID);
}

int main() {

    /* Parallel region begins here */
    #pragma omp parallel
    {
    	int ID = omp_get_thread_num();
    	printHello(ID);
    }
}