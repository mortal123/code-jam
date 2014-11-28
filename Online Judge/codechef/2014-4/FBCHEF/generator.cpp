#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100000;

int main() {
	srand(0);
	freopen("input.txt", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		printf("%d\n", rand());
	}
	for(int i = 2; i <= n; i++) {
		printf("%d %d\n", rand() % (i - 1) + 1, i);
	}
	int q = n;
	printf("%d\n", q);
	for(int i = 1; i <= q; i++) {
		if (rand() % 5 < 4) {
			printf("1 %d %d\n", rand() % n + 1, rand());
		} else {
			printf("2 %d\n", rand() % n + 1);
		}
	}
	return 0;
} 
