#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 111111, M = 20;

int jump[M][N];
int dep[N], size[N], n, m;
long long down[N], up[N];
vector<int> e[N];

void dfsDown(int x) {
	down[x] = 0;
	size[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == jump[0][x])
			continue;
		dep[y] = dep[x] + 1;
		jump[0][y] = x;
		dfsDown(y);
		size[x] += size[y];
		down[x] += down[y];
	}
	down[x] += size[x] - 1;
}

void dfsUp(int x, long long v) {
	up[x] = v;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == jump[0][x])
			continue;
		dfsUp(y, v + down[x] - down[y] - size[y] + n - size[y]);
	}
}

int solve(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	for(int i = M - 1; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b]) {
			a = jump[i][a];
		}
	}
	if (a == b)
		return a;
	for(int i = M - 1; i >= 0; i--) {
		if (jump[i][a] != jump[i][b]) {
			a = jump[i][a];
			b = jump[i][b];
		}
	}
	return jump[0][a];
}

int jumpUp(int a, int d) {
	for(int i = M - 1; i >= 0; i--) {
		if (d >> i & 1) {
			a = jump[i][a];
		}
	}
	return a;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfsDown(1);
	for(int i = 1; i < M; i++)
		for(int j = 1; j <= n; j++)
			jump[i][j] = jump[i - 1][jump[i - 1][j]];
	dfsUp(1, 0);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d", &a, &b);
		c = solve(a, b);
		int ds = dep[a] + dep[b] - 2 * dep[c];
		if (dep[a] < dep[b])
			swap(a, b);
		if (ds == 1) {
			printf("%I64d\n", up[b] + down[b] - size[a]);
			continue;
		}
		long long res = 0;
		if (ds % 2 == 0) {
			int md = jumpUp(a, ds / 2), mdd = jumpUp(a, ds / 2 - 1);
			res = down[b] + up[b] + down[a] + up[a];
			res -= down[mdd] + 1LL * size[mdd] * (dep[mdd] + dep[b] - 2 * dep[c]);
			res -= up[mdd] + 1LL * (dep[a] - dep[mdd]) * (n - size[mdd]);
		} else {
			int md = jumpUp(a, (ds + 1) / 2), mdd = jumpUp(a, ds / 2);
			res = down[b] + up[b] + down[a] + up[a];
			res -= down[mdd] + 1LL * size[mdd] * (dep[mdd] + dep[b] - 2 * dep[c]);
			res -= up[mdd] + 1LL * (dep[a] - dep[mdd]) * (n - size[mdd]);
		}
		printf("%I64d\n", res);
	}
	return 0;
} 
