#include <cstdio>
#include <cstdlib>

const int MAXN = 300;

int n, m;
int mat[MAXN][MAXN], son[MAXN][MAXN];

struct node
{
	int x, y;
}p[MAXN];
int cnt;
char str[MAXN];

int make(int son[MAXN][MAXN])
{
	cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		gets(str + 1);
		for(int j = 1; j <= n; j++)
		{
			if (str[j] == '0' || str[j] == '1')
				son[i][j] = str[j] - '0';
			else
			{
				son[i][j] = -1;
				if (i < j)
					p[cnt].x = i, p[cnt++].y = j;
			}
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k++)
				if (i != j && j != k && k != i)
				{
					if (son[i][j] == -1)
						continue;
					if (son[j][k] == -1)
						continue;
					if (son[i][k] == -1)
						continue;
					if (son[i][k] > son[i][j] + son[j][k])
						return 0;
				}
	//for(int i = 0; i < cnt; i++)
	//	printf("%d %d\n", p[i].x, p[i].y);
	for(int i = 0; i < (1 << cnt); i++)
	{
		for(int j = 0; j < cnt; j++)
			if (i & (1 << j))
				son[p[j].x][p[j].y] = 1, son[p[j].y][p[j].x] = 1;
			else
				son[p[j].x][p[j].y] = 0, son[p[j].y][p[j].x] = 0;
		int flag = 1;
		for(int j = 0; j < cnt; j++)
			for(int k = 1; k <= n; k++)
			{
				int x = p[j].x, y = p[j].y;
				if (k == x || k == y)
					continue;
				if (son[x][y] > son[x][k] + son[k][y])
					flag = 0;
				if (son[x][k] > son[x][y] + son[y][k])
					flag = 0;
				if (son[k][y] > son[k][x] + son[x][y])
					flag = 0;
			}
		if (flag)
			return 1;
	}
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	if (!make(son))
	{
		printf("NO\n");
		return 0;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			mat[i][j] = son[i][j];
	m = n;
	scanf("%d\n", &n);
	if (!make(son))
	{
		printf("NO\n");
		return 0;
	}
	for(int i = m + 1; i <= m + n; i++)
		for(int j = m + 1; j <= m + n; j++)
			mat[i][j] = son[i - m][j - m];
	printf("YES\n");
	for(int i = 1; i <= n + m; i++)
	{
		for(int j = 1; j <= n + m; j++)
		{
			if (i > m && j <= m || i <= m && j > m)
				mat[i][j] = 1;
			printf("%d", mat[i][j]);
		}
		printf("\n");
	}
	return 0;
}
