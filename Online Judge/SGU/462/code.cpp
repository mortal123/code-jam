#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 100000;

map<int, int> T;
int cnt = 0;

struct Edge
{
	Edge() {}
	Edge(int _a, int _b, int _r, int _p) : a(_a), b(_b), r(_r), p(_p) {}
	int a, b, r, p;
	int adjust(int t)
	{
		if (T[t])
			t = T[t];
		else
		{
			T[t] = ++cnt;
			t = cnt;
		}
		return t;
	}
	void input()
	{
		scanf("%d %d %d %d", &a, &b, &r, &p);
		a = adjust(a);
		b = adjust(b);
	}
	friend int operator <(Edge a, Edge b)
	{
		if (a.r != b.r)
			return a.r < b.r;
		return a.p < b.p;
	}
};

Edge e[MAXN];

long long ans = 0;
int n, fa[MAXN], order[MAXN];

int cmp(int a, int b)
{
	return e[a] < e[b];
}

int find(int x)
{
	int p = x;
	while(fa[p] != p)
		p = fa[p];
	while(x != p)
	{
		int t = fa[x];
		fa[x] = p;
		x = t;
	}
	return p;
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	T.clear();
	for(int i = 1; i <= n; i++)
		e[i].input();
	for(int i = 1; i <= 2 * n; i++)
		fa[i] = i, order[i] = i;
	sort(order + 1, order + n + 1, cmp);
	for(int i = n; i >= 1; i--)
	{
		int j = order[i];
		int a = find(e[j].a), b = find(e[j].b);
		if (a == b)
			continue;
		ans += e[j].p;
		fa[a] = b;
	}
	printf("%I64d\n", ans);
	for(int i = 1; i <= n; i++)
		printf("%d%c", order[i], (i == n) ? '\n' : ' ');
	return 0;
}

