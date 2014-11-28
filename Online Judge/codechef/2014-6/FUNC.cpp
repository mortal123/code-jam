#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 111111;
const int MOD = 1000000007;
const double eps = 1e-8;

long long sum[N];
int n, q;
int a[N];
long long poww[1000001][61];

int main() {
	freopen("input.txt", "r", stdin);
	for(int i = 1; i <= 1000000; i++) {
		poww[i][0] = 1;
		for(int j = 1; j <= 60; j++) {
			if (poww[i][j - 1] > (long long)(1e18) / i) {
				poww[i][j] = (long long)(1e18) + 1;
			} else {
				poww[i][j] = poww[i][j - 1] * i;
			}
		
		}
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &q);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum[i] = sum[i - 1] + a[i];
			sum[i] %= MOD;
		}
		for(int i = 1; i <= q; i++) {
			long long x, last;
			int ans = 0;
			scanf("%lld", &x);
			for(int j = 1; j <= n; j++)	{
				if (j == 1) {
					ans += 1LL * a[j] * (x % MOD) % MOD;
					ans %= MOD;
					last = x;
				} else if (j == 2) {
					long long xx = (long long)(sqrt(x) + eps);
					ans += 1LL * a[j] * (xx % MOD) % MOD;
					ans %= MOD;
					last = xx;
				} else {
					long long l = 1, r = min(1000000LL, last), mid;
					while(l < r) {
						mid = (l + r + 1) / 2;
						if (poww[mid][j] <= x) {
							l = mid;
						} else {
							r = mid - 1;
						}
					}
					ans += 1LL * a[j] * (l % MOD) % MOD;
					ans %= MOD;
					last = l;
				}
				if (last == 1) {
					ans += (sum[n] - sum[j]) % MOD;
					ans %= MOD;
					break;
				}
			}
			printf("%d%c", (ans + MOD) % MOD, i == q ? '\n' : ' ');
		}
	}
}
