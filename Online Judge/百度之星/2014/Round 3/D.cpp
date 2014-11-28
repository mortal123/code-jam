#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MOD = (int)(1e9 + 7);

const int N = 1111;

int ans = 0;
int n, m;
int f[N][N], sum[N][N], rever[1111111];
char buf[N];

int power(int n) {
	int res = 1;
	for(int i = 1; i <= n; i++) {
		res = 1LL * res * i % MOD;
	}
	return res;
}

int poww(int a, int b) {
	if (b == 1)
		return a % MOD;
	if (b == 0)
		return 1 % MOD;
	int tmp = poww(a, b >> 1);
	if (b & 1) {
		return 1LL * tmp * tmp % MOD * a % MOD;
	} else {
		return 1LL * tmp * tmp % MOD;
	}
}

int C(int n, int m) {
	int res = 1;
	for(int i = n - m + 1; i <= n; i++) {
		res = 1LL * res * i % MOD;
	}
	for(int i = 1; i <= m; i++) {
		res = 1LL * res * rever[i] % MOD;
	}
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	for(int i = 1; i <= 1000000; i++) {
		rever[i] = poww(i, MOD - 2);
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		printf("Case #%d:\n", ++testCount);
		ans = 0;
		scanf("%d %d", &n, &m);
		scanf("%s", buf + 1);
		if (n < m + 1) {
			printf("0\n");
			continue;
		}		
		f[1][1] = 1;
		sum[1][1] = 1;
		++m;
		for(int i = 2; i <= m; i++)
			for(int j = 1; j <= i; j++) {
				if (buf[i - 1] == 'U') {
					// j ~ i - 1
					f[i][j] = (sum[i - 1][i - 1] - sum[i - 1][j - 1]);
					if (f[i][j] < 0)
						f[i][j] += MOD;
				} else {
					// 1 ~ j - 1
					f[i][j] = sum[i - 1][j - 1];
				}
				sum[i][j] = (sum[i][j - 1] + f[i][j]);
				if (sum[i][j] >= MOD)
					sum[i][j] -= MOD;
			}
		for(int i = 1; i <= m; i++) {
			ans += f[m][i];
			if (ans >= MOD)
				ans -= MOD;
		}
		printf("%d\n", 1LL * ans * C(n, m) % MOD * power(n - m) % MOD * (n - m + 1) % MOD);
	}
	return 0;
}
