#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int D = 19;

const int N = 555555;
int f[D][N], u[N], k[N];
int n, m, check[N], pp;
int *ff;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n = 500000;
	u[1] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = i + i; j <= n; j += i) {
			k[j] = max(k[j], k[i] + 1);
			u[j] -= u[i];
		}
	}
	for(int p = 0; p < D; p++) {
		for(int i = 1; i <= n; i++)
			if (u[i]) {
				for(int j = i, cnt = 1; j <= n; j += i, cnt++) {
					f[p][j] += u[i] * (k[cnt] > p);
				}
			}
		for(int i = 1; i <= n; i++)
			f[p][i] += f[p][i - 1];
	}
	int q ;
	scanf("%d", &q);
	while(q--) {
		scanf("%d %d %d", &n, &m, &pp);
		if (pp >= 19) {
			printf("%I64d\n", 1LL * n * m);
			continue;
		}
		ff = f[pp];
		int st = 1;
		long long ans = 0;
		while(st <= n && st <= m) {
			int nxt = min(n / (n / st), m / (m / st));
			ans += 1LL * (n / st) * (m / st) * (ff[nxt] - ff[st - 1]);
			st = nxt + 1;
		}
		printf("%I64d\n", 1LL * n * m - ans);
	}
	return 0;
} 
