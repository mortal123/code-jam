#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n;

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
		}
		printf("%lld\n", 1LL * (n - 1) * n / 2);
	}
	return 0;
} 
