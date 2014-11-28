#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, k;

int main() {
	freopen("input.txt", "w", stdout);
	n = 300, k = 300;
	printf("%d %d\n", n, k);
	for(int i = 1; i <= n; i++, printf("\n"))
		for(int j = 0; j <= k; j++) {
			int tmp = rand() % 10000;
			printf("%d ", tmp);
		}
	return 0;
}
