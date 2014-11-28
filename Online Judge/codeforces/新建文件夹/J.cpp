#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 210000;

int n, k, x, pos;

int visit[MAXN], a[MAXN];
vector <int> trans[MAXN];
int q[MAXN];

int Bfs(int x)
{
	for(int i = 1; i <= n; i++)
		visit[i] = 0;
	visit[x] = 1;
	int t = 0, w = 1;
	q[w] = x;
	while(t < w)
	{
		int tmp = q[++t];
		for(int i = 1; i <= k; i++)
		{
			int y = trans[i][tmp - 1];
			if (visit[y])
				continue;
			q[++w] = y;
			visit[y] = 1;
		}
	}
	return visit[1];
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &k);
	for(int i = 1; i <= k; i++)
	{
		trans[i].clear();
		for(int j = 1; j <= n; j++)
		{
			int t;
			scanf("%d", &t);
			trans[i].push_back(t);
		}
	}
	scanf("%d", &x);
	for(int i = 1; i <= n; i++)
		if (a[i] == x)
		{
			x = i;
			break;
		}
	if (Bfs(x))
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
