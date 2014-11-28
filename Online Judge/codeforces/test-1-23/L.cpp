#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1600;

int n, m;
int sum_stab[MAXN][MAXN], v[MAXN][MAXN], ll[MAXN][MAXN], ur[MAXN][MAXN], hash[MAXN][MAXN];
struct node
{
	int x, y;
}q[MAXN * MAXN];
char str[MAXN][MAXN];

int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};

void Bfs(int sx, int sy)
{
	memset(hash, 0, sizeof(hash));
	memset(v, 0, sizeof(v));
	int t, w;
	t = 0, w = 0;
	q[++w].x = sx, q[w].y = sy;
	hash[sx][sy] = 1;
	v[sx][sy] = 1;
	while(t < w)
	{
		node tmp = q[++t];
		for(int i = 0; i < 8; i++)
		{
			if ((tmp.x < 1 || tmp.x > n || tmp.y < 1 || tmp.y > m) && i > 3)
				continue;
			int x = tmp.x + dx[i];
			int y = tmp.y + dy[i];
			if (x < 0 || x > n + 1 || y < 0 || y > m + 1 || hash[x][y] || str[x][y] != '#')
				continue;
			q[++w].x = x; q[w].y = y;
			hash[x][y] = 1;
			v[x][y] = 1;
		}
	}
}

int ans, ansx, ansy;

int calc(int a[MAXN][MAXN], int x1, int y1, int size)
{
	int x2 = x1 + size - 1;
	int y2 = y1 + size - 1;
	if (x2 > n + 1)
		x2 = n + 1;
	if (y2 > m + 1)
		y2 = m + 1;
	return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}

int main()
{
	freopen("labyrinth.in", "r", stdin); freopen("labyrinth.out", "w", stdout);
	scanf("%d %d\n", &n, &m);
	swap(n, m);
	ans = max(n, m) + 1;
	for(int i = 1; i <= n; i++)
		gets(str[i] + 1);
	str[n + 1][0] = '#';
	str[0][m + 1] = '#';
	for(int i = 1; i <= n; i++)
		str[i][0] = str[i][m + 1] = '#';
	for(int i = 1; i <= m; i++)
		str[0][i] = str[n + 1][i] = '#';
	for(int i = 0; i <= n + 1; i++)
		for(int j = 0; j <= m + 1; j++)
		{
			sum_stab[i][j] = (str[i][j] == '#') + sum_stab[i - 1][j] + sum_stab[i][j - 1] - sum_stab[i - 1][j - 1];
		}
	Bfs(n + 1, 0);
	/*for(int i = 1; i <= n; i++, printf("\n"))
		for(int j = 1; j <= m; j++)
			printf("%d", v[i][j]);*/
	for(int i = 0; i <= n + 1; i++)
		for(int j = 0; j <= m + 1; j++)
		{
			ll[i][j] = v[i][j] + ll[i - 1][j] + ll[i][j - 1] - ll[i - 1][j - 1];
		}
	Bfs(0, m + 1);
	/*printf("\n\n");
	for(int i = 1; i <= n; i++, printf("\n"))
		for(int j = 1; j <= m; j++)
			printf("%d", v[i][j]);
	printf("\n\n");*/
	for(int i = 0; i <= n + 1; i++)
		for(int j = 0; j <= m + 1; j++)
		{
			ur[i][j] = v[i][j] + ur[i - 1][j] + ur[i][j - 1] - ur[i - 1][j - 1];
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			if (i == 1 && j == 1 || i == n && j == m || str[i][j] == '#')
				continue;
			int l = 1, r = min(n - i + 1, m - j + 1), mid;
			while(l < r)
			{
				mid = (l + r) / 2 + 1;
				if (calc(sum_stab, i, j, mid))
					r = mid - 1;
				else
					l = mid;
			}
			r = l, l = 1;
			if (i + r - 1 == n && j + r - 1 == m)
				r--;
			while(l < r)
			{
				mid = (l + r) / 2;
				if ((calc(ll, i - 1, j - 1, mid + 2) - calc(ll, i, j, mid)) 
					&& (calc(ur, i - 1, j - 1, mid + 2) - calc(ur, i, j, mid)))
					r = mid;
				else
					l = mid + 1;
			}
			if ((calc(ll, i - 1, j - 1, l + 2) - calc(ll, i, j, l)) 
					&& (calc(ur, i - 1, j - 1, l + 2) - calc(ur, i, j, l)))
			{
				if (l < ans)
				{
					ans = l; ansx = i, ansy = j;
				}
			}
			//int tmp1 = calc(ll, i - 1, j - 1, l + 1) - calc(ll, i, j, l);
			//int tmp2 = calc(ur, i - 1, j - 1, mid + 1) - calc(ur, i, j, mid);
			//int res = 0;
		}
	if (ans > max(n, m))
		printf("Impossible\n");
	else
		printf("%d %d %d\n", ans, ansy, ansx);
	return 0;
}
