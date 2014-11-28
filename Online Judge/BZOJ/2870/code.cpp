#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

long long Ans = -1;
int dv[MAXN], N, visit[MAXN], size[MAXN], fa[MAXN], q[MAXN];
struct edge
{
	int other[MAXN], last[MAXN], sum, succ[MAXN];
	void AddEdge(int a, int b)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;

int MaxLen;

void Init()
{
	scanf("%d", &N);
	for(int i = 1;i <= N;i++)
		scanf("%d", &dv[i]), Ans = max(Ans, (long long)dv[i]);
	for(int i = 1;i < N;i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		e.AddEdge(a, b);
	}
}

int Find(int rx)
{
	int t = 0, w = 1;
	q[w] = rx;
	fa[rx] = 0;
	while(t < w)
	{
		int x = q[++t];
		for(int i = e.last[x];i;i = e.succ[i])
		{
			int y = e.other[i];
			if (y == fa[x] || visit[y])
				continue;
			q[++w] = y;
			fa[y] = x;
		}
	}
	for(int i = w;i >= 1;i--)
		size[q[i]] = 0;
	int res, rv = MAXN + 10;
	for(int i = w;i >= 1;i--)
	{
		int x = q[i];
		size[x]++;
		size[fa[x]] += size[x];
		int now = w - size[x];
		for(int j = e.last[x];j;j = e.succ[j])
		{
			int y = e.other[j];
			if (y == fa[x] || visit[y])
				continue;
			now = max(now, size[y]);
		}
		if (now < rv)
			rv = now, res = x;
	}
	MaxLen = w + 10;
	return res;
}

int c1[MAXN], c2[MAXN], dep[MAXN], mv[MAXN], len1, len2;

void Bfs(int rf, int rx)
{
	len2 = 2;
	int t = 0,w = 1;
	q[w] = rx;
	dep[rx] = 2;
	mv[rx] = min(dv[rf], dv[rx]);
	fa[rx] = rf;
	while(t < w)
	{
		int x = q[++t];
		//Ans = max(Ans, (long long)mv[x] * dep[x]);
		for(int i = e.last[x];i;i = e.succ[i])
		{
			int y = e.other[i];
			if (y == fa[x] || visit[y])
				continue;
			q[++w] = y;
			fa[y] = x;
			dep[y] = dep[x] + 1;
			mv[y] = min(mv[x], dv[y]);
			len2 = max(len2, dep[y]);
		}
	}
	for(int i = 1;i <= len2;i++)
		c2[i] = 0;
	for(int i = 1;i <= w;i++)
	{
		int x = q[i];
		c2[dep[x]] = max(c2[dep[x]], mv[x]);	
	}
	c1[1] = c2[1] = dv[rf];
	for(int j = 1, i = 1;i <= len2;i++)
	{
		while(j <= len1 && c1[j] >= c2[i])
			j++;
		Ans = max(Ans, (long long)(j + i - 2) * c2[i]);
	}
	for(int j = 1, i = 1;i <= len1;i++)
	{
		while(j <= len2 && c2[j] >= c1[i])
			j++;
		Ans = max(Ans, (long long)(j + i - 2) * c1[i]);
	}
	for(int i = 1;i <= len2;i++)
		c1[i] = max(c1[i], c2[i]);
	len1 = max(len1, len2);
}

void Work(int x)
{
	x = Find(x);
	visit[x] = 1;
	for(int i = 1;i <= MaxLen;i++)
		c1[i] = 0;
	len1 = 1;
	for(int i = e.last[x];i;i = e.succ[i])
	{
		int y = e.other[i];
		if (visit[y])
			continue;
		Bfs(x, y);
	}
	for(int i = e.last[x];i;i = e.succ[i])
	{
		int y = e.other[i];
		if (visit[y])
			continue;
		Work(y);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work(1);
	printf("%lld", Ans);
	return 0;
}
