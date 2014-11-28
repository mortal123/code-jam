#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;


int main() {
	ios::sync_with_stdio(false);
	int test;
	cin >> test;
	while(test--) {
		double x;
		long long k;
		cin >> x >> k;
		double step = x, start = x / 2;
		long long number = 1;
		for(; ; step /= 2, start /= 2, number *= 2) {
			if (k <= number) {
				printf("%.8f\n", start + (k - 1) * step);
				break;
			} else {
				k -= number;
			}
		}
	}
	return 0;
}