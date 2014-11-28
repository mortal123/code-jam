#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1111111;

int factor[N], inv[N];

int power(int a, int b) {
	if (b == 0) {
		return 1 % MOD;
	}
	int temp = power(a, b >> 1);
	if (b & 1) {
		return 1LL * temp * temp % MOD * a % MOD;
	} else {
		return 1LL * temp * temp % MOD;
	}
}

int C(int n, int m) {
	return 1LL * factor[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {	
	int n;
	scanf("%d", &n);
	factor[0] = inv[0] = 1;
	for(int i = 1; i <= n; i++) {
		factor[i] = 1LL * factor[i - 1] * i % MOD;
		inv[i] = power(factor[i], MOD - 2);
	}
	
	int answer = 0;
	for(int i = 1; i + 12 <= n; i++) {
		if ((n - i) % 2 == 0) {
			answer += C((n - i) / 2 - 1, 5);
			answer %= MOD;
		}
	}
	printf("%d\n", answer);
	return 0;
}

