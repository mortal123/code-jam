#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 1002;

struct eglist
{
	int other[MAXN * MAXN * 2], succ[MAXN * MAXN * 2], last[MAXN * MAXN * 2], sum;
	void AddEdge(int a, int b)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;
int num[MAXN][MAXN], val[MAXN * MAXN], tot, du[MAXN * MAXN], ans[MAXN * MAXN], tmp[MAXN * MAXN], N, M;
struct node
{
	int x, y, v;
}p[MAXN * MAXN];

int cmp(node a, node b)
{
	return a.v < b.v;
}

void Init()
{
	scanf("%d %d", &N, &M);
	for(int i = 1;i <= N;i++)
		for(int j = 1;j <= M;j++)
		{
			int t;
			scanf("%d", &t);
			p[(i - 1) * M + j] = (node){i, j, t};
		}
	sort(p + 1, p + N * M + 1, cmp);
	for(int i = 1;i <= N * M;i++)
	{
		if (i == 1 || p[i].v != p[i - 1].v)
			tot++, val[tot] = p[i].v;
		num[p[i].x][p[i].y] = tot;
	}
}

void Work()
{
	for(int i = 2;i <= N;i++)
	{
		int j;
		for(j = 1;num[i][j] == num[1][j];j++);
		e.AddEdge(num[i][j], num[1][j]);
	}
	int tlen = 0;
	for(int i = 1;i <= tot;i++)
		if (du[i] > 49)
			ans[i] = ++tlen;
	for(int i = 1;i <= tot;i++)
	if (!ans[i])
	{
		for(int j = e.last[i];j;j = e.succ[j])
			tmp[ans[e.other[j]]] = i;
		int j;
		for(j = 1;tmp[j] == i;j++);
		ans[i] = j;
	}
	printf("Yes\n");
	for(int i = 1;i <= tot;i++)
		printf("%d -> %d\n", val[i], ans[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
} 
