#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2222222;
const int MOD = (int)(1e9 + 9);
int k;
int fac[N], rev[N], facr[N];

int C(int n, int m) {
	if (m > n)
		return 0;
	return 1LL * fac[n] * facr[m] % MOD * facr[n - m] % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> k;
	int n = 1 << k;
	rev[1] = 1;
	for(int i = 2; i <= n; i++) {
		int t = MOD / i, k = MOD % i;
		rev[i] = 1LL * i * t % MOD * t % MOD * rev[k] % MOD * rev[k] % MOD;
	}
	
	fac[0] = facr[0] = 1;
	for(int i = 1; i <= n; i++) {
		fac[i] = 1LL * fac[i - 1] * i % MOD;
		facr[i] = 1LL * facr[i - 1] * rev[i] % MOD;
	}
	
	for(int i = 1; i <= n; i++) {
		cout << 1LL * n * C(i - 1, n / 2 - 1) % MOD * fac[n / 2] % MOD * fac[n / 2 - 1] % MOD << endl;
	}
	return 0;
}
