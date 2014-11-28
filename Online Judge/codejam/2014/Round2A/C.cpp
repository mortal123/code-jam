#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int N = 4444;

int n, m, ob;
int vis[N][N];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int dfs(int x, int y, int d) {
	if (x < 0 || x >= n)
		return 0;
	if (y < 0 || y >= m)
		return 0;
	if (vis[x][y])
		return 0;
	vis[x][y] = 1;
	if (x == n - 1) {
		return 1;
	}
	for(int i = 1; i >= -1; i--) {
		int dir = (4 + d + i) % 4;
		if (dfs(x + dx[dir], y + dy[dir], dir))
			return 1;
	}
	return 0;
}

int main() {
	freopen("C-small-attempt0.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		scanf("%d %d %d", &m, &n, &ob);
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= ob; i++) {
			int x0, y0, x1, y1;
			scanf("%d %d %d %d", &y0, &x0, &y1, &x1);
			for(int j = x0; j <= x1; j++)
				for(int k = y0; k <= y1; k++) {
					vis[j][k] = 1;
				}
		}
		/*
		for(int i = 0; i < n; i++, printf("\n"))
			for(int j = 0; j < m; j++)
				printf("%d", vis[i][j]);
		*/
		int ans = 0;
		for(int i = 0; i < m; i++) {
			if (!vis[0][i])
				ans += dfs(0, i, 0);
		}
		printf("Case #%d: %d\n", ++testCount, ans);
	}
	return 0;
}
 
