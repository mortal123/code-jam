#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MAXM = 20;

int father[MAXM][MAXN];
int ans[MAXN], up[MAXN], dep[MAXN], len[MAXN], v[MAXN];
int n, q[MAXN], Q, d[MAXM][MAXN], u[MAXM][MAXN];
int fset[MAXN];

int lca(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	for(int i = MAXM - 1; i >= 0; i--)
		if (dep[a] - (1 << i) >= dep[b])
			a = father[i][a];
	if (a == b)
		return a;
	for(int i = MAXM - 1; i >= 0; i--) 
		if (father[i][a] != father[i][b])
			a = father[i][a], b = father[i][b];
	return father[0][a];
}

int first = 1;

int main() {
	freopen("input.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for(int test = 1; test <= Test; test++) {
		if (!first)
			printf("\n");
		first = 0;
		printf("Case #%d:\n", test);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &v[i]);
		}
		for(int i = 2; i <= n; i++) {
			scanf("%d", &father[0][i]);
			dep[i] = dep[father[0][i]] + 1;
		}
		for(int i = 1; i < MAXM; i++) {
			for(int j = 1; j <= n; j++)
				father[i][j] = father[i - 1][father[i - 1][j]];
		}
		for(int i = 1; i <= n; i++) {
			d[0][i] = u[0][i] = 1;
			if (i != 1 && v[i] < v[father[0][i]])
				u[0][i] = u[0][father[0][i]] + 1;
			if (i != 1 && v[i] > v[father[0][i]])
				d[0][i] = d[0][father[0][i]] + 1;
		}
		for(int i = 1; i < MAXM; i++) {
			for(int j = 1; j <= n; j++) {
				d[i][j] = max(d[i - 1][j], d[i - 1][father[i - 1][j]]);
				u[i][j] = max(u[i - 1][j], u[i - 1][father[i - 1][j]]);
			}
		}
		scanf("%d", &Q);
		for(int i = 1; i <= Q; i++) {
			int a, b, c;
			scanf("%d %d", &a, &b);
			c = lca(a, b);
			int l = 0, r = 0, ans = 1;
			for(int j = MAXM - 1; j >= 0; j--) 
				if (dep[a] - (1 << j) >= dep[c]) {
					int tmp = father[j][a];
					if (dep[tmp] - u[0][tmp] + 1 > dep[c]) {
						ans = max(ans, u[j][a]);
						a = father[j][a];
					} else {
						continue;
					}
				}
			if (dep[a] - u[0][a] + 1 > dep[c])
				a = father[0][a];
			for(int j = MAXM - 1; j >= 0; j--)
				if (dep[b] - (1 << j) >= dep[c]) {
					int tmp = father[j][b];
					if (dep[tmp] - d[0][tmp] + 1 > dep[c]) {
						ans = max(ans, d[j][b]);
						b = father[j][b];
					} else {
						continue;
					}
				}
			if (dep[b] - d[0][b] + 1 > dep[c])
				b = father[0][b];
			ans = max(ans, dep[a] - dep[c] + dep[b] - dep[c] + 1);
			printf("%d\n", ans);
		}
	}
	return 0;
} 
