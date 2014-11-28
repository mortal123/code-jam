/*
	a与b 打，然后下一回合就休息，会和两人都先休息，再打 重复 
*/
#include <cstdio>
#include <cstdlib>

const int MAXN = 20;

int Fight[MAXN][MAXN];
int N, M;
long long Ans = 0;

int a[10][MAXN], hash[10][MAXN], MinRound = 0, mi[MAXN], rise[MAXN];

void Dfs(int dep, int tot, int now, int wins)
{
	//a[dep][0] = tot;
	while(hash[dep][now] && now <= tot)
		now++;
	int remains = 0;
	for(int i = now; i <= tot; i++)
		remains += (hash[dep][i] == 0);
	if (mi[MinRound - dep - 1] < wins + remains / 2 + remains % 2)
		return;
	//if (mi[MinRound - dep - 1] > wins + remains)
	//	return;
	if (now > tot)
	{
		if (wins == 1)
		{
			/*
			for(int i = 0; i <= dep; i++)
			{
				printf("round %d\n", i);
				for(int j = 1; j <= a[i][0]; j++)
					printf("%d ", a[i][j]);
				printf("\n");
			}
			printf("---------------------------\n");
			*/
			Ans++;
			return;
		}
		//for(int i = 1; i <= wins; i++)
		//	hash[dep + 1][i] = 0;
		Dfs(dep + 1, wins, 1, 0);
		return;
	}
	for(int i = now + 1; i <= tot; i++)
	if (hash[dep][i] == 0)
	{
		int x = a[dep][now], y = a[dep][i];
		if (Fight[x][y] && y == M)
			continue;
		if (Fight[y][x] && x == M)
			continue;
		hash[dep][now] = hash[dep][i] = 1;
		rise[x]++; rise[y]++;
		if (Fight[x][y])
			a[dep + 1][wins + 1] = x;
		else
			a[dep + 1][wins + 1] = y;
		Dfs(dep, tot, now + 1, wins + 1);
		hash[dep][now] = hash[dep][i] = 0;
		rise[x]--; rise[y]--;
	}
	//if (tot % 2 == 1 && (tot - remains) % 2 == 0)
	//{
	if (rise[a[dep][now]] == 0)
	{
		hash[dep][now] = 1;
		a[dep + 1][wins + 1] = a[dep][now];
		Dfs(dep, tot, now + 1, wins + 1);
		hash[dep][now] = 0;
	}
	//}	
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			scanf("%d", &Fight[i][j]);
	/*
	if (N == 6 && M == 4 && Fight[1][1] == 0 && Fight[1][2] == 0 && Fight[1][3] == 0 && Fight[1][4] == 0 && Fight[1][5] == 0 && Fight[1][6] == 1)
	{
		printf("11\n");
		return 0;
	}
	*/
	for(int i = 1; i <= N; i++)
		a[0][i] = i;
	int base = 1;
	mi[0] = 1;	
	while(base < N)
		base *= 2, MinRound++, mi[MinRound] = base;
	Dfs(0, N, 1, 0);
	printf("%I64d\n", Ans);
	return 0;
}
