#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 110000, MAXE = MAXN * 4;

struct eglist
{
	int other[MAXE + 10], succ[MAXE + 10], last[MAXE + 10], cost[MAXE + 10], sum;
	void clear()
	{
		for(int i = 1; i <= sum; i++)
			last[i] = 0;
		sum = 1;
	}
	void AddEdge(int a, int b, int c)
	{
		//printf("add %d %d\n", a, b);
		other[++sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum] = c;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum, cost[sum] = c;
	}
}e, r;

struct edge
{
	int a, b, c;
	friend int operator <(edge a, edge b)
	{
		return a.c < b.c;
	}
}ed[MAXE + 10], ek[MAXE + 10], ec[MAXE + 10];

int n, m, k, ec_num = 0;
int q[MAXN + 10], fa[MAXN + 10], fat[MAXN + 10], color[MAXN + 10], totColor = 0, ffa[MAXN + 10];
long long ans, p[MAXN + 10], size[MAXN + 10], ss[MAXN + 10], mat[30][30];

int find(int fa[], int x)
{
	int p = x;
	while(fa[p] != p)
		p = fa[p];
	while(x != p) {
		int t = fa[x];
		fa[x] = p;
		x = t;
	}
	return p;
}

void dfs(int x, int father, long long &ret) {
	for(int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == father)
			continue;
		dfs(y, x, ret);
		ret += (long long)e.cost[i] * ss[y];
		//printf("%d %lld\n", e.cost[i], ss[y]);
		ss[x] += ss[y];
	}
}

void dfss(int x, int father, int mv, int src)
{
	mat[src][x] = max(mat[src][x], (long long)mv);
	for(int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == father)
			continue;
		dfss(y, x, max(mv, e.cost[i]), src);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= m; i++) {
		scanf("%d %d %d", &ed[i].a, &ed[i].b, &ed[i].c);
	}
	for(int i = 1; i <= k; i++) {
		scanf("%d %d", &ek[i].a, &ek[i].b);
	}
	for(int i = 1; i <= n; i++)
		scanf("%lld", &p[i]);
	sort(ed + 1, ed + m + 1);
	e.clear();
	for(int i = 1; i <= n; i++) {
		fa[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		int u = find(fa, ed[i].a), v = find(fa, ed[i].b);
		if (u == v)
			continue;
		ec[++ec_num] = ed[i]; 
		fa[u] = v;
	}
	m = 0;
	for(int i = 1; i <= k; i++)
		ed[++m] = ek[i];
	for(int i = 1; i <= ec_num; i++)
		ed[++m] = ec[i];
	for(int i = 1; i <= n; i++)
		fa[i] = ffa[i] = i;
	for(int i = 1; i <= m; i++) {
		int u = find(fa, ed[i].a), v = find(fa, ed[i].b);
		if (u == v)
			continue;
		if (i > k)
		{
			int a = find(ffa, ed[i].a), b = find(ffa, ed[i].b);
			ffa[a] = b;
		}
		fa[u] = v;
	}
	for(int i = 1; i <= n; i++)
		ffa[i] = find(ffa, i);
	for(int i = 1; i <= n; i++)
		fa[i] = ffa[i], size[i] = 0;
	for(int i = 1; i <= n; i++) {
		if (!ffa[i])
			continue;
		++totColor; 
		int tmp = ffa[i];
		for(int j = i; j <= n; j++) {
			if (ffa[j] == tmp) {
				color[j] = totColor;
				ffa[j] = 0;
				size[totColor] += p[j];
			}
		}
	}
	for(int i = 1; i <= totColor; i++)
		for(int j = 1; j <= totColor; j++)
			mat[i][j] = 0;
	m = 0;
	e.clear();
	for(int i = 1; i <= ec_num; i++) {
		int u = find(fa, ec[i].a), v = find(fa, ec[i].b);
		if (u == v)
			continue;
		fa[u] = v;
		u = color[u], v = color[v];
		e.AddEdge(u, v, ec[i].c);
		ed[++m].a = u, ed[m].b = v, ed[m].c = 0;
		//mat[u][v] = max(mat[u][v], (long long)ec[i].c); 
		//mat[v][u] = max(mat[v][u], (long long)ec[i].c);
	}
	for(int i = 1; i <= totColor; i++)
		dfss(i, 0, -1, i);
	long long ans = 0;
	for(int i = 0; i < (1 << k); i++) {
		i = (1 << k) - 1;
		long long ret = 0;
		int cnt = 0;
		for(int j = 1; j <= totColor; j++)
			fa[j] = j, ss[j] = size[j];
		e.clear();
		for(int j = 0; j < k; j++)
			if ((1 << j) & i) {
				int u = color[ek[j + 1].a], v = color[ek[j + 1].b];
				int a = find(fa, u), b = find(fa, v);
				if (a == b)
					continue;
				e.AddEdge(u, v, mat[u][v]);
				fa[a] = b; cnt++;
			}
		for(int j = 1; j <= m; j++) {
			int u = ed[j].a, v = ed[j].b;
			int a = find(fa, u), b = find(fa, v);
			if (a == b)
				continue;
			e.AddEdge(u, v, 0);
			fa[a] = b; cnt++;
		}
		if (cnt != totColor - 1) {
			while(1); printf("hehe\n");
		}
		dfs(color[1], 0, ret);
		ans = max(ans, ret);
	}
	printf("%lld\n", ans);
	return 0;
} 
