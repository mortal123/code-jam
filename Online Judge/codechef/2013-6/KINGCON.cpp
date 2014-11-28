#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 3100 * 3100;	

struct eglist
{
	int other[MAXN], last[MAXN], succ[MAXN], sum;
	void clear(int size)
	{
		for(int i = 0; i < size; i++)
			last[i] = 0;
		sum = 1;
	}
	void AddEdge(int a, int b)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;

int N, M, K, ans;
int DFN[MAXN], low[MAXN], tot;
int isBlock[MAXN], cnt;

void Tarjan(int x, int le)
{
	DFN[x] = low[x] = ++tot;
	for(int i = e.last[x]; i; i = e.succ[i])
	{
		if ((i ^ 1) == le)
			continue;
		int y = e.other[i];
		if (DFN[y] == -1)
		{
			Tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y] >= DFN[x])
				isBlock[x] = 1;
			if (x == 0)
				cnt++;
		} else
			low[x] = min(low[x], DFN[y]);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for(; T--; )
	{
		scanf("%d %d %d", &N, &M, &K);
		e.clear(N);
		for(int i = 0; i < N; i++)
			DFN[i] = low[i] = -1, isBlock[i] = 0;
		for(int i = 0; i < M; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			e.AddEdge(a, b);
		}
		ans = tot = cnt = 0;
		for(int i = 0; i < N; i++)
			if (DFN[i] == -1)
				Tarjan(i, -1);
		for(int i = 1; i < N; i++)
			ans += isBlock[i];
		ans += (cnt > 1);
		printf("%d\n", ans * K);
	}	
	return 0;
}
