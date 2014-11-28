#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 111;
const int MOD = 1e9 + 7;

int n;
int size[N][N];
int f[N][N][N][3];
int g[N][3], Comb[N][N], pre[N][3];
vector<int> e[N];
int answer;

// 1 considered and choose
// 0 considered and not choose
// 2 not considered

__inline void add(int &a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	if (a < 0) {
		a += MOD;
	}
}

__inline int norm(int a) {
	if (a >= MOD) {
		a -= MOD;
	}
	if (a < 0) {
		a += MOD;
	}
	return a;
}

void doit(int x, int father, int f[N][N][3], int size[N]) {
	for(int i = 1; i <= size[x]; i++) {
		f[x][i][0] = f[x][i][1] = f[x][i][2] = 0;
	}

	size[x] = 1;

	f[x][1][0] = 0;
	f[x][1][1] = 1;
	f[x][1][2] = 1;
	
	for(int it = 0; it < (int)e[x].size(); it++) {
		int y = e[x][it];
		if (y == father) {
			continue;
		}

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

void dfs(int x, int from, int f[N][N][3], int size[N]) {
	size[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y != from) {
			dfs(y, x, f, size);
			size[x] += size[y];
		}
	}
	doit(x, from, f, size);
}

void solve(int x, int from) {
	if (from != -1) {
		for(int i = 1; i <= n; i++) {
			size[x][i] = size[from][i];	
			for(int j = 1; j <= n; j++)
				for(int k = 0; k < 3; k++) {
					f[x][i][j][k] = f[from][i][j][k];
				}
		}

		size[x][from] -= size[x][x];
		size[x][x] = n;
		doit(from, x, f[x], size[x]);
		doit(x, -1, f[x], size[x]);
	} else {

	}

	for(int i = 1; i <= n; i++) {
		add(answer, f[x][x][i][1]);
	}

	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y != from) {
			solve(y, x);
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
		answer = 0;
		dfs(1, -1, f[1], size[1]);
		solve(1, -1);
		cout << answer << endl;
	}
	return 0;
}