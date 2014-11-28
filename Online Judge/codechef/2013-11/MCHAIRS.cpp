#include <cstdio>
#include <cstdlib>

const int MOD = int(1e9+7);

long long pow(int a, int b) {
	if (b == 0)
		return 1;
	if (b & 1)
		return pow(a, b - 1) * a % MOD;
	long long tmp = pow(a, b / 2);
	return tmp * tmp % MOD;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", (int)(pow(2, n) - 1 + MOD) % MOD);
	}
}
