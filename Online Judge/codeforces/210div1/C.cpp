#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 2222;
const int MOD = 1000000007;

int f[N][N]; 
int n, k;
char bufer[N];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &k);
	scanf("%s", bufer + 1);
	f[0][0] = 1;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= k; j++)
			if (f[i][j]) {
				for(int p = i + 1; p <= n; p++) {
					if (bufer[p] != 'a')
						(f[p][j] += (bufer[p] - 'a') * f[i][j] % MOD) %= MOD;
					if (('z' - bufer[p]) * (n - p + 1) * (p - i) + j <= k) {
						(f[p][('z' - bufer[p]) * (n - p + 1) * (p - i) + j] += f[i][j]) %= MOD;
					}
				}
			}
	int ans = 0;
	for(int i = 0; i <= n; i++) {
		(ans += f[i][k]) %= MOD;
	}
	printf("%d\n", ans);
	return 0;
} 
