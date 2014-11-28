#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	int n = 100000, k = 50;
	printf("%d %d\n", n, k);
	for(int i = 1; i <= k; i++) {
		printf("%d %d %d\n", 1, i + 1, 100);
	}
	return 0;
}

