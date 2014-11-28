#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int n = 100000, q = 100000;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	printf("%d\n", n);
	for(int i = 2; i <= n; i++) {
		printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand() % 10 - 5);
	}
	printf("%d\n", q);
	for(int i = 1; i <= q; i++) {
		if (rand() % 2) {
			printf("A\n");
		} else {
			printf("C %d\n", rand() % n + 1);
		}
	}
	return 0;
}
