#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 52, INF = 1 << 30;

int Map[MAXN][MAXN], num[MAXN][MAXN], Ans = -1, N, M, wet[MAXN], vis[MAXN], combine[MAXN], G[MAXN][MAXN], MinCut, S, T;

// way
int cutnode, Father[MAXN], Color[MAXN];

void Init()
{
	scanf("%d %d", &N, &M);
	for(int i = 1;i <= M;i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		Map[a][b] += c;
		Map[b][a] += c;
		num[a][b] = num[b][a] = i;
	}
}

int find(int x)
{
	int t, p = x;;
	while(Father[p] != p)
		p = Father[p];
	while(Father[x] != x)
	{
		t = Father[x];
		Father[x] = p;
		x = t;
	}
	return p;
}

void Search()
{
	int Max, MaxPos;
	memset(wet, 0, sizeof(wet));
	memset(vis, 0, sizeof(vis));
	S = T = -1;
	for(int i = 1;i <= N - 1;i++)
	{
		Max = -INF;
		for(int j = 1;j <= N;j++)
			if (!combine[j] && !vis[j] && wet[j] > Max)
			{
				MaxPos = j;
				Max = wet[j];
			}
		if (T == MaxPos)
			return;
		S = T, T = MaxPos;
		MinCut = Max;
		vis[T] = 1;
		for(int j = 1;j <= N;j++)
			if (!combine[j] && !vis[j])
			{
				wet[j] += G[T][j];
			}
	}
}

int Stoer_Wagner(int cn)
{
	memset(combine, 0, sizeof(combine));
	combine[cn] = 1;
//	Ans = INF;
	for(int i = 1;i <= N - 2;i++)
	{
		Search();
		if (MinCut < Ans)
		{
			Ans = MinCut;
			cutnode = cn;
			for(int j = 1;j <= N;j++)
			{
				if (find(j) == T)
					Color[j] = 1;
				else
					Color[j] = 0;
			}
		}
		if (Ans == 0)
			return 0;
		combine[T] = 1;
		Father[find(T)] = find(S);
		for(int j = 1;j <= N;j++)
			if (!combine[j])
			{
				G[S][j] += G[T][j];
				G[j][S] += G[j][T];
			}
	}
}

int put[MAXN], plen;

void Work()
{
	Ans = INF;
	for(int i = 1;i <= N;i++) // choose a cut node
	{
		// copy
		for(int j = 1;j <= N;j++)
			for(int k = 1;k <= N;k++)
				G[j][k] = Map[j][k];
		for(int j = 1;j <= N;j++)
			Father[j] = j;
		Stoer_Wagner(i);
	}
	printf("%d\n", Ans);
	for(int i = 1;i <= N;i++)
		for(int j = 1;j < i;j++)
			if (i != cutnode && j != cutnode && num[i][j])
			{
				if (Color[i] && !Color[j] || !Color[i] && Color[j])
					put[++plen] = num[i][j];
			}
	sort(put + 1, put + plen + 1);
	printf("%d\n", plen);
	for(int i = 1;i <= plen;i++)
		printf("%d ", put[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
