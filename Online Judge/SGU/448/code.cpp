#include <cstdio>
#include <cstdlib>

const int MAXN = 20;

int Fight[MAXN][MAXN];
int N, M;
long long Ans = 0;

int a[10][MAXN], hash[10][MAXN];

void Dfs(int dep, int tot, int now, int wins)
{
	if (dep == 1)
	{
		dep = 1;
	}
	if (now > tot)
	{
		if (wins == 1)
		{
			Ans++;
			return;
		}
		for(int i = 1; i <= wins; i++)
			hash[dep + 1][i] = 0;
		Dfs(dep + 1, wins, 1, 0);
		return;
	}
	if (hash[dep][now])
		Dfs(dep, tot, now + 1, wins);
	else
	{
		int flag = 0;
		for(int i = now + 1; i <= tot; i++)
		if (hash[dep][i] == 0)
		{
			int x = a[dep][now], y = a[dep][i];
			if (Fight[x][y] == -1)
				continue;
			if (Fight[x][y] && y == M)
				continue;
			if (Fight[y][x] && x == M)
				continue;
			hash[dep][now] = hash[dep][i] = 1;
			if (Fight[x][y])
				a[dep + 1][wins + 1] = x;
			else
				a[dep + 1][wins + 1] = y;
			Dfs(dep, tot, now + 1, wins + 1);
			hash[dep][now] = hash[dep][i] = 0;
			if ()
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			scanf("%d", &Fight[i][j]);
	int base = 1;
	while(base < N)
		base *= 2;
	for(int i = 1; i <= N; i++)
		for(int j = N + 1; j <= base; j++)
			Fight[i][j] = 1;
	for(int i = N + 1; i <= base; i++)
		for(int j = N + 1; j <= base; j++)
			Fight[i][j] = -1;
	for(int i = 1; i <= base; i++)
		a[0][i] = i;
	Dfs(0, base, 1, 0);
	printf("%I64d\n", Ans);
	return 0;
}
