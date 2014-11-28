#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 200;
int a[MAXN][MAXN], n, m;
int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
int hash[MAXN];
int ans = 0;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			if (a[i][j] == -1 || hash[a[i][j]])
				continue;
			for(int k = 0; k < 8; k++)
			{
				int x = i + dx[k];
				int y = j + dy[k];
				if (x < 1 || x > n || y < 1 || y > m || a[x][y] != a[i][j])
					continue;
				if (hash[a[i][j]] == 0)
				ans++;
				hash[a[i][j]] = 1;
			}
		}
	printf("%d\n", ans);
	return 0;
}
