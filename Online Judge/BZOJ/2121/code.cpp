#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200;

int flag[MAXN][MAXN][32][32];
int OK[MAXN][MAXN], len[32], N, M;
char str[MAXN][MAXN];

void Init()
{
	gets(str[0] + 1);
	scanf("%d\n", &M);
	for(int i = 1;i <= M;i++)
		gets(str[i] + 1);
	N = strlen(str[0] + 1);
	for(int i = 1;i <= M;i++)
		len[i] = strlen(str[i] + 1);
}

int Dfs(int l, int r, int a, int b)
{
	if (flag[l][r][a][b])
		return flag[l][r][a][b] > 0;
	if (l > r && b == len[a])
		return flag[l][r][a][b] = 1;
	if (l > r || b == len[a] || r - l + 1 < len[a] - b)
	{
		flag[l][r][a][b] = -1;
		return 0;
	}
	if (str[0][l] == str[a][b + 1])
		if (Dfs(l + 1, r, a, b + 1))
		{
			flag[l][r][a][b] = 1;
			return 1;
		}
	for(int i = l;i <= r;i++)
		if (OK[l][i])
			if (Dfs(i + 1, r, a, b))
			{
				flag[l][r][a][b] = 1;
				return 1;
			}
	flag[l][r][a][b] = -1;
	return 0;
}

int calc[MAXN];

void Work()
{
	for(int i = 1;i <= M;i++)
	{
		for(int j = 1;j <= N;j++)
			if (j + len[i] - 1 <= N)
			{
				int flag = 1;
				for(int k = j;k <= j + len[i] - 1;k++)
					if (str[0][k] != str[i][k + 1 - j])
						flag = 0;
				if (flag)
					OK[j][j + len[i] - 1] = 1;
			}
	}
	for(int k = 1;k <= N;k++)
		for(int i = 1;i + k - 1 <= N;i++)
		if (!OK[i][i + k - 1])
		{
			for(int j = 1;j <= M && !OK[i][i + k - 1];j++)
				if (str[j][len[j]] == str[0][i + k - 1])
					OK[i][i + k - 1] = Dfs(i, i + k - 1, j, 0);
		}
	for(int i = 0;i <= N;i++)
		calc[i] = i;
	for(int i = 1;i <= N;i++)
	{
		calc[i] = min(calc[i], calc[i - 1] + 1);
		for(int j = 1;j <= i;j++)
			if (OK[j][i])
				calc[i] = min(calc[i], calc[j - 1]);
	}
	printf("%d\n", calc[N]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
