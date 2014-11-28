#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MOD = 9999991;
const int N = 1111;

int f[N][N], u[N], v[N], combine[N][N];
int n, m, x, y, k;

void getFunction(int n, int x, int k, int u[N]) {
	for(int i = 0; i <= k; i++)
		for(int j = 0; j <= n; j++)
			f[i][j] = 0;
	f[0][x] = 1;
	for(int i = 0; i < k; i++)
		for(int j = 1; j <= n; j++)
			if (f[i][j]) {
				for(int k = -2; k <= 2; k++)
					if (k != 0) {
						int final = k + j;
						if (final >= 1 && final <= n) {
							f[i + 1][final] += f[i][j];
							if (f[i + 1][final] >= MOD)
								f[i + 1][final] -= MOD;
						}
					}
			}
	for(int i = 0; i <= k; i++) {
		u[i] = 0;
		for(int j = 1; j <= n; j++) {
			u[i] += f[i][j];
			if (u[i] >= MOD)
				u[i] -= MOD;
		}
	}
}

int main() {
	for(int i = 0; i <= 1000; i++) {
		combine[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			combine[i][j] = (combine[i - 1][j] + combine[i - 1][j - 1]) % MOD;
		}
	}
	int test;
	scanf("%d", &test);
	for(int testCount = 1; testCount <= test; testCount++) {
		printf("Case #%d:\n", testCount);
		scanf("%d %d %d %d %d", &n, &m, &k, &x, &y);
		getFunction(n, x, k, u);
		getFunction(m, y, k, v);
		int ans = 0;
		for(int i = 0; i <= k; i++) {
			ans += (1LL * u[i] * v[k - i] % MOD * combine[k][i] % MOD);
			if (ans >= MOD)
				ans -= MOD;
		}
		printf("%d\n", ans);
	}
}
