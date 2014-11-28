#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

void run(int n, int m) {
	printf("%d %d %d %d %d\n", n, m, 1, n, 5);
	for(int i = 2; i <= n; i++) {
		printf("%d %d %d\n", rand() % i + 1, i, rand() % 20 + 1);
	}
	for(int i = n; i <= m; i++) {
		int a = rand() % n + 1, b = rand() % n + 1, c = rand() % 20 + 1;
		printf("%d %d %d\n", a, b, c);
	}
	for(int i = 1; i <= 5; i++) {
		printf("%d ", 1000000000 - i);
	}
	puts("");
}

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	for(int i = 1; i <= 20; i++) {
		run(5, 10);
	}
	return 0;
}

