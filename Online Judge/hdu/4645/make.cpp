#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;



int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	int n = 5;
	printf("%d\n", n);
	for(int i = 2; i <= n; i++) {
		printf("%d %d\n", i, rand() % (i - 1) + 1);
	}
	for(int i = 1; i <= n; i++)
		printf("%d ", rand() % 2);
	printf("\n");
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % 12 - 6);
	}
	printf("\n");
	int m = 5;
	printf("%d\n", m);
	for(int i = 1; i <= m; i++) {
		int type = rand() % 3;
		printf("%d %d", type, rand() % n + 1);
		if (type < 2) {
			printf("\n");
		} else {
			printf(" %d\n", rand() % 12 - 6);
		}
	}
	return 0;
}
