#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int n = 80, q = 80;

void Main() {
	printf("%d\n", n);
	for(int i = 2; i <= n; i++) {
		printf("%d %d\n", i - 1, rand() % (i - 1));
	}
	printf("%d\n", q);
	for(int i = 1; i <= q; i++) {
		if (rand() % 3 == 0) {
			printf("O ");
		} else {
			printf("q ");
		}
		printf("%d\n", rand() % n);
	}
}

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int test = 1;
	printf("%d\n", test);
	for(int i = 1; i <= test; i++)
		Main();
	return 0;
}
