#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2222;
const int INF = 2222 * 2222;

bool exist[N][N];
int up[N][N], dn[N][N], f[N][N];
vector<int> e[N], ee[N];
int n, m;
int dfn[N], low[N], stack[N], top, tick, color[N], totColor, inStack[N];
int value[N], size[N];
vector<int> upp[N], dnn[N];

void tarjan(int x, int from) {
	dfn[x] = low[x] = ++tick;
	stack[++top] = x;
	inStack[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == from) {
			continue;
		}
		if (!dfn[y]) {
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
		} else if (inStack[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]) {
		++totColor;
		while(1) {
			int y = stack[top--];
			inStack[y] = 0;
			color[y] = totColor;
			value[totColor]++;
			if (y == x) {
				break;
			}
		}
	}
}

void solve(int x, int from) {
	size[x] = value[x];
	for(int i = 0; i < (int)ee[x].size(); i++) {
		int y = ee[x][i];
		if (y == from) {
			continue;
		}
		solve(y, x);
		size[x] += size[y];
	}
	for(int i = 0; i <= size[x]; i++) {
		up[x][i] = dn[x][i] = -INF;
	}
	
	for(int i = 0; i <= size[x]; i++)
		for(int j = 0; j + i <= size[x]; j++) {
			f[i][j] = -INF;
		}
	f[0][0] = value[x] * value[x];
	size[x] = 0;
	for(int i = 0; i < (int)ee[x].size(); i++) {
		int y = ee[x][i];
		if (y == from) {
			continue;
		}
		for(int j = size[x]; j >= 0; j--)
			for(int k = size[x] - j; k >= 0; k--) {
				if (f[j][k] < 0) {
					continue;
				}
				for(int t = 0; t < (int)upp[y].size(); t++) {
					int p = upp[y][t];
					f[j + p][k] = max(f[j + p][k], f[j][k] + up[y][p] + k * p + p * value[x]);
				}
				for(int t = 0; t < (int)dnn[y].size(); t++) {
					int p = dnn[y][t];
					f[j][k + p] = max(f[j][k + p], f[j][k] + dn[y][p] + j * p + p * value[x]);
				}
			}
		size[x] += size[y];
	}
	for(int i = 0; i <= size[x]; i++)
		for(int j = 0; i + j <= size[x]; j++) {
			up[x][i + value[x]] = max(up[x][i + value[x]], f[i][j]);
			dn[x][i + value[x]] = max(dn[x][i + value[x]], f[j][i]);
		}
	size[x] += value[x];
	for(int i = 1; i <= size[x]; i++) {
		if (up[x][i] >= 0) {
			upp[x].push_back(i);
		}
		if (dn[x][i] >= 0) {
			dnn[x].push_back(i);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}	
	tarjan(1, 0);
	for(int x = 1; x <= n; x++) {
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (color[x] == color[y]) {
				continue;
			}
			if (exist[color[x]][color[y]]) {
				continue;
			}
			exist[color[x]][color[y]] = 1;
			ee[color[x]].push_back(color[y]);
		}
	}/*
	for(int i = 1; i <= totColor; i++)
		for(int j = 0; j < (int)ee[i].size(); j++) {
			printf("%d %d\n", i, ee[i][j]);
		}*/
	solve(1, -1);
	int answer = 0;
	for(int i = 0; i <= n; i++) {
		answer = max(answer, up[1][i]);
		answer = max(answer, dn[1][i]);
	}
	printf("%d\n", answer);
	//printf("%d\n", up[5][2]);
	return 0;
}

