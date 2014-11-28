#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	int n = 100000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % 10000);
	}
	puts("");
	int q = 100000;
	printf("%d\n", q);
	for(int i = 1; i <= q; i++) {
		int type = rand() % 2;
		
		printf("%d %d %d", type + 1, rand() % n + 1, rand() % n + 1);
		if (type == 1) {
			printf(" %d", rand() % n);
		}
		puts("");
	}
}
