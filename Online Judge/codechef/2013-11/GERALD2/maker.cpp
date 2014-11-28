#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int n = 100000, q = 100000;

void Main() {
	printf("%d %d\n", n, q);
	for(int i = 2; i <= n; i++) {
		printf("%d\n", rand() % (i - 1) + 1);
	}
	for(int i = 1; i <= q; i++) {
		printf("%d\n", rand() % n + 1);
	}
}

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int test = 2;
	printf("%d\n", test);
	for(int i = 1; i <= test; i++)
		Main();
	return 0;
}
