#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1111111;
const int MOD = 1000000007;

int n;
int a[N];
long long h[N], pn[N], f[N];

long long ask(long long a[], int pos) {
	long long res = 0;
	for(int i = pos; i; i -= (i & (-i))) {
		res += a[i];
		res %= MOD;
	}
	return (res + MOD) % MOD;
}

void inc(long long a[], int pos, int v) {
	for(int i = pos; i <= n; i += (i & (-i))) {
		a[i] += v;
		a[i] = (a[i] % MOD + MOD) % MOD;
	}
}

int main() {
	
	long long base = 0;
	long long ans = 0;
	
	scanf("%d", &n);
	pn[0] = 1;
	for(int i = 1; i <= n; i++) {
		pn[i] = pn[i - 1] * i % MOD;
	}
	
	f[0] = f[1] = 0;
	for(int i = 2; i <= n; i++) {
		f[i] = (1LL * (i - 1) * i / 2) % MOD * pn[i - 1] % MOD;
		f[i] += 1LL * i * f[i - 1] % MOD;
		f[i] %= MOD;
	}
	
	for(int i = 1; i <= n; i++) {
		inc(h, i, 1);
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		long long left = ask(h, a[i] - 1);
		ans += pn[n - i] * left % MOD * base % MOD;
		ans %= MOD;
		ans += left * f[n - i] % MOD;
		ans %= MOD;
		ans += pn[n - i] * ((left * (left - 1) / 2) % MOD) % MOD;
		ans %= MOD;
		
		inc(h, a[i], -1);
		
		base += left;
		base %= MOD;
	}
	
	ans += base;
	ans %= MOD;
	
	printf("%I64d\n", ans);
	
	return 0;
} 
