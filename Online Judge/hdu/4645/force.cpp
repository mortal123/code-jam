#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111, inf = 1000000000;

vector<int> e[N];

int n, m, color[N], w[N];

int dfs(int x, int fa) {
	int ret = w[x];
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (color[y] != color[x])
			continue;
		if (y == fa)
			continue;
		ret = max(ret, dfs(y, x));
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		for(int i = 1; i <= n; i++)
			scanf("%d", &color[i]);
		for(int i = 1; i <= n; i++)
			scanf("%d", &w[i]);
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			int type, a, b;
			scanf("%d %d", &type, &a);
			if (type == 0) {
				printf("%d\n", dfs(a, a));
			} else if (type == 1) {
				color[a] ^= 1;
			} else {
				scanf("%d", &b);
				w[a] = b;
			}
		}
	}	
	return 0;
}
