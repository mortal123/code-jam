#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
const int N = 222222, M = 111;
const int ZERO = 100;

int sum[M][2 * M];
int cnt[M];
int n, a[N], b[2 * M];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		memset(sum, 0, sizeof(sum));
		memset(cnt, 0, sizeof(cnt));
		int ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			for(int j = -100; j <= 100; j++) {
				b[j + ZERO] = 0;
				if (a[i] - j >= 1 && a[i] - j <= 100) {
					b[j + ZERO] = (cnt[a[i] - j] + sum[a[i] - j][j + ZERO]) % MOD;
				}
			}
			for(int j = -100; j <= 100; j++) {
				(sum[a[i]][j + ZERO] += b[j + ZERO]) %= MOD;
				(ans += b[j + ZERO]) %= MOD;
			}
			cnt[a[i]]++;
			(ans += 1) %= MOD;
		}
		(ans += 1) %= MOD;
		int ans2 = 1;
		for(int i = 1; i <= n; i++) {
			ans2 *= 2;
			ans2 %= MOD;
		}
		printf("%d\n", (ans2 - ans + MOD) % MOD);		
	}
}
