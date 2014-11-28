#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 222;
const int MOD = 1e9 + 7;

//int TIMES = 0;

int n;
int size[N];
int f[N][N];
int g[N], Comb[N][N], pre[N], stoped[N];
vector<int> e[N];
int answer, fact[N];

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

void doit(int x, int father) {
	for(int i = 1; i <= size[x]; i++) {
		f[x][i] = 0;
	}

	size[x] = 1;

	//f[x][1][0] = 0;
	f[x][1] = 1;
	//f[x][1][2] = 1;
	
	int CNT = 0;

	for(int it = 0; it < (int)e[x].size(); it++) {
		int y = e[x][it];
		if (y == father) {
			continue;
		}

		for(int i = 1; i <= size[x]; i++) {
			int total = 0;
			for(int j = 1; j <= size[y]; j++) {
				add(total, 1LL * f[x][i] * fact[size[y] - 1] % MOD);
				pre[j] = -1LL * f[x][i] * fact[size[y] - 1] % MOD;
			}
			add(g[i], 1LL * total * Comb[i - 1][i - 1] % MOD * Comb[size[x] + size[y] - i][size[x] - i] % MOD);
			for(int j = 1; j <= size[y]; j++) {
				//CNT++;
				add(total, 1LL * f[x][i] * norm(fact[size[y] - 1] - f[y][j]) % MOD);
				add(total, pre[j]);	
				add(g[i + j], 1LL * total * Comb[i + j - 1][i - 1] % MOD * Comb[size[x] + size[y] - (i + j)][size[x] - i] % MOD);		
			}
		}

		size[x] += size[y];
		for(int i = 1; i <= size[x]; i++) {				
			f[x][i] = g[i];
			g[i] = 0;
		}
	}
	//cout << "time cost = " << CNT << endl;
	/*if (CNT > n) {
		TIMES++;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (y == father) {
				continue;
			}
			cout << y << " := " << size[y] << endl;
		}
		cout << size[x] << endl;
		exit(0);
	}
	*/
}

void dfs(int x, int from) {
	size[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y != from) {
			dfs(y, x);
			size[x] += size[y];
		}
	}
	doit(x, from);
}


int recover[2][N][N];

void solve(int x, int from) {
	int ss = 0;
	
	if (from != -1) {
		for(int i = 1; i <= n; i++) {
			recover[0][x][i] = f[x][i];
			recover[1][x][i] = f[from][i];
		}
		ss = size[x];

		size[from] -= size[x];
		size[x] = n;
		doit(from, x);
		doit(x, -1);
	} else {

	}

	for(int i = 1; i <= n; i++) {
		add(answer, f[x][i]);
	}

	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y != from) {
			solve(y, x);
		}
	}

	if (from != -1) {
		size[from] = n;
		size[x] = ss;
		for(int i = 1; i <= n; i++) {
			f[x][i] = recover[0][x][i];
			f[from][i] = recover[1][x][i];
		}
	}
}

int main() {
	fact[0] = 1;
	for(int i = 1; i <= N; i++) {
		fact[i] = 1LL * fact[i - 1] * i % MOD;
	}
	for(int i = 0; i <= N; i++) {
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
		dfs(1, -1);
		//TIMES = 0;
		solve(1, -1);
		cout << answer << endl;
		//cout << TIMES << endl;
	}
	return 0;
}