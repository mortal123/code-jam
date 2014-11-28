#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int N = 4444;
const int INF = 111111111;

int n, m, ob;
int a[N][2], b[N][2];
int dis[N];
int vis[N];

int dist(int x, int y)
{
	if (min(a[x][1], a[y][1]) >= max(a[x][0], a[y][0]))
		return max(b[x][0], b[y][0]) - min(b[x][1], b[y][1]) - 1;
	if (min(b[x][1], b[y][1]) >= max(b[x][0], b[y][0]))
		return max(a[x][0], a[y][0]) - min(a[x][1], a[y][1]) - 1;
	return max(max(a[x][0], a[y][0]) - min(a[x][1], a[y][1]), max(b[x][0], b[y][0]) - min(b[x][1], b[y][1])) - 1;
}

void dij() {
	for(int i = 0; i <= ob; i++) {
		vis[i] = 0;
	}
	for(int i = 0; i <= ob; i++) {
		int pos = -1;
		for(int j = 0; j <= ob; j++) {
			if (vis[j])
				continue;
			if (pos == -1 || dis[pos] > dis[j]) {
				pos = j;
			}
		}
		vis[pos] = 1;
		for(int j = 0; j <= ob; j++) {
			if (!vis[j])
				dis[j] = min(dis[j], dis[pos] + dist(pos, j));
		}
	}
}

int main() {
	freopen("C-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		scanf("%d %d %d", &m, &n, &ob);
		for(int i = 1; i <= ob; i++) {
			int x0, y0, x1, y1;
			scanf("%d %d %d %d", &y0, &x0, &y1, &x1);
			a[i][0] = y0, a[i][1] = y1;
			b[i][0] = x0, b[i][1] = x1;
		}
		a[0][0] = -1, a[0][1] = -1;
		b[0][0] = 0, b[0][1] = n;
		a[++ob][0] = m, a[ob][1] = m;
		b[ob][0] = 0, b[ob][1] = n;
		for(int i = 0; i <= ob; i++) {
			dis[i] = INF;
		}
		dis[0] = 0;
		dij();
		printf("Case #%d: %d\n", ++testCount, dis[ob]);
	}
	return 0;
}
 
