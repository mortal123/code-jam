#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n = 100000, m = 500000, q = 500000;

int main() {
	freopen("input.txt", "w", stdout);
	printf("%d %d %d\n", n, m, q);
	for(int i = 2; i <= n; i++) {
		printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand());
	}
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand());
	}
	printf("\n");
	for(int i = 1; i <= m - n + 1; i++) {
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand());
	}
	for(int i = 1; i <= q; i++) {
		printf("%d %d %d\n", rand() % n + 1, rand(), rand() % 2 + 1);
	}
	return 0;
}
