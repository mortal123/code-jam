#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1000000009;
const int N = 111, M = 111111, BOUND = 100000;

int numbers[M];
int n, q;
int f[N][N], g[N][N];
int rev[M], mem[N], cnt[N], fac[M];

int power(int a, int b) {
	if (b == 0)
		return 1;
	int tmp = power(a, b >> 1);
	if (b & 1) {
		return 1LL * tmp * tmp % MOD * a % MOD;
	} else  {
		return 1LL * tmp * tmp % MOD;
	}
}

int C(int n, int m) {
	return 1LL * fac[n] * rev[m] % MOD * rev[n - m] % MOD;
}

int main() {
	fac[0] = rev[0] = 1;
	for(int i = 1; i <= BOUND; i++) {
		fac[i] = 1LL * fac[i - 1] * i % MOD;
		rev[i] = 1LL * rev[i - 1] * power(i, MOD - 2) % MOD;
	} 
	int test;
	//read(test);
	scanf("%d", &test);
	for(; test--; ) {
		//read(n); read(q);	
		scanf("%d %d", &n, &q);
		for(int i = 0; i < n; i++) {
			scanf("%d", &numbers[i]);
		}
		for(int i = 1; i <= q; i++) {
			int x;
			//read(x);
			scanf("%d", &x);
			fill(cnt, cnt + x, 0);
			for(int j = 0; j < n; j++) {
				int c = (numbers[j] % x + x) % x;
				cnt[c]++;
			}
			for(int j = 0; j <= x; j++)
				for(int k = 0; k <= x; k++)
					f[j][k] = g[j][k] = 0;
			for(int j = 0; j < x; j++) {
				for(int k = 0; k <= cnt[j]; k++) {
					(g[j][k * j % x] += C(cnt[j], k)) %= MOD;
				}
			}
			f[0][0] = 1;
			for(int j = 0; j < x; j++)
				for(int k = 0; k < x; k++) if (f[j][k]) {
					for(int c = 0; c < x; c++) {
						(f[j + 1][(k + c) % x] += 1LL * f[j][k] * g[j][c] % MOD) %= MOD;
					}
				}
			printf("%d\n", f[x][0]);
		}
	}
	return 0;
}
