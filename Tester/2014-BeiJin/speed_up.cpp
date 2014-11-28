#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 111;
const int MOD = 1e9 + 7;

int n;
int size[N];
int f[N][N][3];
int g[N][3], Comb[N][N], pre[N][3];
vector<int> e[N];

// 1 considered and choose
// 0 considered and not choose
// 2 not considered

void add(int &a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	if (a < 0) {
		a += MOD;
	}
}

int norm(int a) {
	if (a >= MOD) {
		a -= MOD;
	}
	if (a < 0) {
		a += MOD;
	}
	return a;
}

void dfs(int x, int from) {
	size[x] = 1;
	vector<int> sons;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y != from) {
			dfs(y, x);
			size[x] += size[y];
			sons.push_back(y);
		}
	}

	for(int i = 1; i <= size[x]; i++) {
		f[x][i][0] = f[x][i][1] = f[x][i][2] = 0;
	}

	size[x] = 1;

	f[x][1][0] = 0;
	f[x][1][1] = 1;
	f[x][1][2] = 1;
	
	for(int it = 0; it < (int)sons.size(); it++) {
		int y = sons[it];

		for(int i = 1; i <= size[x]; i++) {
			for(int j = 1; j <= size[y]; j++) {
				int total = norm(f[y][j][0] + f[y][j][1]);
				add(pre[i + j][0], 1LL * f[x][i][0] * total % MOD);
				add(pre[i + size[y] + 1][0], -1LL * f[x][i][0] * total % MOD);

				add(pre[i + j][0], 1LL * f[x][i][1] * f[y][j][1] % MOD);
				add(pre[i + size[y] + 1][0], -1LL * f[x][i][1] * f[y][j][1] % MOD);
					
				add(pre[i + j][1], 1LL * f[x][i][1] * f[y][j][0] % MOD);
				add(pre[i + size[y] + 1][1], -1LL * f[x][i][1] * f[y][j][0] % MOD);
						
				add(pre[i + j][2], 1LL * f[x][i][2] * total % MOD);
				add(pre[i + size[y] + 1][2], -1LL * f[x][i][2] * total % MOD);

				add(pre[i][0], 1LL * f[x][i][0] * f[y][j][2] % MOD);
				add(pre[i + j][0], -1LL * f[x][i][0] * f[y][j][2] % MOD);

				add(pre[i][1], 1LL * f[x][i][1] * f[y][j][2] % MOD);
				add(pre[i + j][1], -1LL * f[x][i][1] * f[y][j][2] % MOD);

				add(pre[i][2], 1LL * f[x][i][2] * f[y][j][2] % MOD);
				add(pre[i + j][2], -1LL * f[x][i][2] * f[y][j][2] % MOD);
 			}

 			for(int j = 1; j <= size[x] + size[y]; j++) {
 				for(int k = 0; k < 3; k++) {
 					add(pre[j][k], pre[j - 1][k]);
 					add(g[j][k], 1LL * pre[j][k] * Comb[j - 1][i - 1] % MOD * Comb[size[x] + size[y] - j][size[x] - i] % MOD);
 				}
 			}

 			for(int j = 1; j <= size[x] + size[y] + 1; j++) {
 				for(int k = 0; k < 3; k++) {
 					pre[j][k] = 0;
 				}
 			}
		}

		size[x] += size[y];
		for(int i = 1; i <= size[x]; i++) {
			for(int j = 0; j < 3; j++) {
				f[x][i][j] = g[i][j];
				g[i][j] = 0;
			}
		}
	}
}

int main() {
	for(int i = 0; i <= 100; i++) {
		Comb[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			Comb[i][j] = norm(Comb[i - 1][j - 1] + Comb[i - 1][j]);
		}
	}

	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		printf("Case #%d: ", ++testCount);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		int answer = 0;
		for(int i = 1; i <= n; i++) {
			dfs(i, -1);
			for(int j = 1; j <= n; j++) {
				add(answer, f[i][j][1]);
			}
		}
		cout << answer << endl;
	}
	return 0;
}