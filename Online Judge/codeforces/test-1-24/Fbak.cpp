#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

int l, n, i, j, x, y, x1, x2, y1, y2, xx, yy, n1, n2, tot;
int nmax, Ans, Num[4][5], Dis[13][13], Need[13][13][3];
char hash[13], cant[13];
int MMM;

void Dfs(int i, int Now, int S);

int main()
{
	scanf("%d %d", &l, &n);
	if (l > 39)
	{
		printf("BAD MEMORY\n");
		return 0;
	}
	
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 4; j++)
			tot++, Num[i][j] = tot;
	for (x1 = 1; x1 <= 3; x1++)
		for (y1 = 1; y1 <= 4; y1++)
			for (x2 = 1; x2 <= 3; x2++)
				for (y2 = 1; y2 <= 4; y2++)
				{
					xx = x2 - x1, yy = y2 - y1;
					n1 = Num[x1][y1], n2 = Num[x2][y2];
					Dis[n1][n2] = abs(xx) + abs(yy);
					if (n1 >= n2)
						continue;
					if ((x1 + x2) % 2 == 0 && (y1 + y2) % 2 == 0)
					{
						Need[n1][n2][++Need[n1][n2][0]] = Num[(x1 + x2) / 2][(y1 + y2) / 2];
						Need[n2][n1][++Need[n2][n1][0]] = Num[(x1 + x2) / 2][(y1 + y2) / 2];
					}
					
					if (xx < 0 || yy < 0)
						continue;
					if (xx % 3 == 0 && yy % 3 == 0)
					{
						Need[n1][n2][++Need[n1][n2][0]] = Num[x1][y1 + 1];
						Need[n2][n1][++Need[n2][n1][0]] = Num[x1][y1 + 1];
						Need[n1][n2][++Need[n1][n2][0]] = Num[x1][y1 + 2];
						Need[n2][n1][++Need[n2][n1][0]] = Num[x1][y1 + 2];
					}
				}
				
	for (i = 1; i <= n; i++)
		scanf("%d %d", &x, &y), cant[Num[x][y]] = 1;
	nmax = 12 - n;
	for (i = 1; i <= 12; i++)
		if (cant[i] == 0)
		{
			hash[i] = 1;
			Dfs(2, i, 0);
			hash[i] = 0;
		}
	
	if (Ans == 0)
		printf("BAD MEMORY\n");
	else
		printf("%d\n", Ans);
	return 0;
}

void Dfs(int i, int Now, int S)
{
	int x, y, tag;
	if (S > l || S + (nmax - i + 1) * 5 < l)
		return;
	if (S == l)
	{
		Ans++;
		return;
	}
	
	if (i > nmax)
		return;
	for (x = 1; x <= 12; x++)
	{
		if (hash[x] == 1 || cant[x] == 1)
			continue;
		tag = 1;
		for (y = 1; y <= Need[Now][x][0]; y++)
			if (hash[Need[Now][x][y]] == 0)
				tag = 0;
		if (tag == 0)
			continue;
		hash[x] = 1;
		Dfs(i + 1, x, S + Dis[Now][x]);
		hash[x] = 0;
	}
	
	return;
}
