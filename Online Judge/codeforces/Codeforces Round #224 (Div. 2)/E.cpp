#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstring>

using namespace std;

const int N = 55;
const int MOD = 1000000007;

long long f[N][N][2], C[N][N];
int n, k, nn;

long long dfs(int n, int k, int s) {
	if (f[n][k][s] >= 0)
		return f[n][k][s];
	
	if (k < 0 || n < 0)
		return 0;
		
	if (n == 0) {
		if (k)
			return f[n][k][s] = 0;
		if (s == 1)
			return f[n][k][s] = 1;
		else
			return f[n][k][s] = 0;
	}
	
	if (n == 1) {
		if (k != 0)
			return f[n][k][s] = 0;
		if (s == 0)
			return f[n][k][s] = 1;
		else
			return f[n][k][s] = 0;
	}
	
	f[n][k][s] = 0;
	
	if (s == 0) {
		// 1 must be in the left
		for(int i = 0; i <= n - 2; i++) {
			for(int j = 0; j <= k; j++) {
				f[n][k][s] += C[n - 2][i] * dfs(i + 1, j, 1) % MOD * dfs(n - 2 - i, k - j, 1) % MOD;
				f[n][k][s] %= MOD;
			}
		}
	} else{
		// the linked must be in the left
		for(int i = 0; i <= n - 2; i++) {
			for(int j = 0; j < k; j++) {
				long long tmp1 = (dfs(i + 1, j, 0) + dfs(i + 1, j, 1)) % MOD;
				long long tmp2 = (dfs(n - 2 - i, k - 1 - j, 0) + dfs(n - 2 - i, k - 1 - j, 1)) % MOD;
				long long total = tmp1 * tmp2 - dfs(i + 1, j, 1) * dfs(n - 2 - i, k - 1 - j, 1) % MOD;
				total %= MOD; total += MOD; total %= MOD;
				
				f[n][k][s] += C[n - 2][i] * total % MOD;
			}
		}
	}
	
	if (n != nn)
		(f[n][k][s] *= n) %= MOD;
		
	return f[n][k][s];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &k);
	if (k >= n) {
		printf("0\n");
		return 0;
	}
	
	for(int i = 0; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
	
	nn = n;
	memset(f, -1, sizeof(f));
	printf("%I64d\n", (dfs(n, k, 0) + dfs(n, k, 1)) % MOD);
	//printf("%I64d\n", dfs(n, k, 1));
	return 0;
} 
