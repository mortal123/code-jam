#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 110000, MAXE = MAXN * 4;

struct eglist
{
	int other[MAXE + 10], succ[MAXE + 10], last[MAXE + 10], sum;
	void clear()
	{
		memset(last, 0, sizeof(last));
		sum = 1;
	}
	void AddEdge(int a, int b)
	{
		//printf("add %d %d\n", a, b);
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;

struct edge
{
	int a, b, c;
	friend int operator <(edge a, edge b)
	{
		return a.c < b.c;
	}
}ed[MAXE + 10], ek[MAXE + 10], ec[MAXE + 10];

int n, m, k, ec_num = 0;
int q[MAXN + 10], fa[MAXN + 10], fat[MAXN + 10];
long long ans, p[MAXN + 10], size[MAXN + 10];

int find(int x)
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

long long Bfs(int S)
{
	int qhead = 0, qtail = 1;
	unsigned long long ret = 0;
	q[qtail] = S; fat[1] = 0;
	while(qhead < qtail) {
		int x = q[++qhead];
		for(int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y != fat[x]) {
				fat[y] = x;;
				q[++qtail] = y;
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		size[i] = 0;
	}
	for(int i = n; i >= 1; i--) {
		int x = q[i];
		size[x] += p[x];
		size[fat[x]] += size[x];
	}
	for(int i = 1; i <= ec_num; i++) {
		int x = ec[i].a, y = ec[i].b;
		if (size[x] < size[y])
			swap(x, y);
		ret += (unsigned long long)size[y] * ec[i].c;
	//	printf("%d %d %d\n", ec[i].c, x, y);
	}
	//for(int i = 1; i <= n; i++)
	//	printf("%lld ", size[i]);
	cout << ret << endl;
	//return ret;
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
	sort(ed + 1, ed + m + 1);
	e.clear();
	for(int i = 1; i <= n; i++) {
		fa[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		int u = find(ed[i].a), v = find(ed[i].b);
		if (u == v)
			continue;
		if (u > v)
			swap(u, v);
		int flag = 0;
		for(int j = 1; j <= k; j++) {
			int x = find(ek[j].a), y = find(ek[j].b);
			if (x == y)
				continue;
			if (x > y)
				swap(x, y);
			if (x == u && v == y) {
				e.AddEdge(ek[j].a, ek[j].b);
				ec[++ec_num] = ek[j];
				ec[ec_num].c = ed[i].c;
				flag = 1;
				break;
			}
		}
		if (!flag)
			e.AddEdge(ed[i].a, ed[i].b);
		fa[u] = v;
	}
	for(int i = 1; i <= n; i++)
		scanf("%lld", &p[i]);
	//printf("%lld\n", Bfs(1));
	Bfs(1);
	return 0;
} 
