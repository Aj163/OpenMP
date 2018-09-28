#include <bits/stdc++.h>
#include "omp.h"
using namespace std;

#define MAX 10000

double dis(int a, int b, int c, int d) {

	double ans = (a-c)*1ll*(a-c) + (b-d)*1ll*(b-d);
	return sqrt(ans);
}

int main() {
	
	srand(time(0));

	int tot=1000000, cnt=0;

	#pragma omp parallel for reduction (+: cnt)
	for(int i=0; i<tot; i++) {
		int x = rand()%MAX;
		int y = rand()%MAX;

		// Check if (x, y) lies in the circle
		if(dis(x, y, MAX/2, MAX/2) <= MAX/2) {
			cnt++;
		}
	}

	printf("PI: %0.5lf\n", cnt*4.0/tot);
}