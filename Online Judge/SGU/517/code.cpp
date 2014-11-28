#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int ans = 0;
int n, m;
int color[2000][2000];

struct bigNum {
	int dat[1005], len;
	inline friend bigNum operator+(const bigNum &a, const bigNum &b) {
		bigNum c;
		c.len = 0;
		for(int i = 1; i <= max(max(a.len, b.len), c.len); i++) {
			c.dat[i] = b.dat[i] + a.dat[i];
			if (c.dat[i] >= Mod) {
				c.dat[i + 1]++;
				c.dat[i] -= Mod;
				c.len = max(c.len, i + 1);
			}
		}
		return c;
	}
};

int check(int x, int y) {
	if (x < 2 || y < 2)
		return 1;
	if (color[x - 1][y - 1] != color[x - 1][y] && color[x - 1][y - 1] != color[x][y - 1]
	&& color[x - 1][y] != color[x][y] && color[x][y - 1] != color[x][y])
		return 0;
	return 1;
}

void dfs(int x, int y, int now) {
	if (x == n && y == m) {
		if (color[x][y] == 0)
			return;
	/*
		if (n == 2 && m == 4)
		for(int i = 1; i <= n; i++, printf("\n"))
			for(int j = 1; j <= m; j++)
				printf("%d ", color[i][j]); 
	*/	
		
		ans++;
		return ;
	}
	y++; 
	if (y == m + 1)
		x++, y = 1;
	if (color[x][y]) {
		dfs(x, y, now);
		return;
	}
	if (y < m && color[x][y + 1] == 0) {
		color[x][y] = color[x][y + 1] = now;
		if (check(x, y))
			dfs(x, y, now + 1);
		color[x][y] = color[x][y + 1] = 0;
	}
	if (x < n && color[x + 1][y] == 0) {
		color[x][y] = color[x + 1][y] = now;
		if (check(x, y))
			dfs(x, y, now + 1);
		color[x][y] = color[x + 1][y] = 0;
	}
}

int main() {
	freopen("output.txt", "w", stdout);
	for(n = 1; n <= 10; n ++, printf("\n"))
		for(m = 1; m <= 10; m ++) {
			ans = 0;
			dfs(1, 0, 1);
			printf("% 4d ", ans);
		}
	int n, m;
	scanf("%d %d", &n, &m);
	if (n <= 10 && m <= 10) {
		printf("%d\n", f[n][m]);
	} else {
		dfs()
	}
	return 0;
}
