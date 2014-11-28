#include <cstdio>
#include <cstdlib>

const int MAXN = 4000;

int fa[MAXN];

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
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	int cnt = 1;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		find(u);
		find(v);
		if (fa[u] != fa[v])
			fa[fa[u]] = fa[v], cnt++;
	}
	if (cnt == n)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}

