#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1000;

vector<int> e[N];
int color[N];

pair<int, int> dfs(int x, int fa, int ds) {
	pair<int, int> res;
	res.first = -1000000, res.second = 0;
	if (color[x] == 0) {
		res.first = ds, res.second = x;
	}
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == fa)
			continue;
		res = max(res, dfs(y, x, ds + 1));
	}
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		int n, q;
		scanf("%d %d", &n, &q);
		for(int i = 1; i <= n; i++)
			e[i].clear();
		for(int i = 2; i <= n; i++) {
			int pa;
			scanf("%d", &pa);
			e[pa].push_back(i);
			e[i].push_back(pa);
		}
		for(int i = 1; i <= n; i++) {
			color[i] = 0;
		}
		while(q--) {
			int x;
			scanf("%d", &x);
			color[x] ^= 1;
			pair<int, int> res = dfs(x, 0, 0);
			res = max(res, make_pair(0, x));
			printf("%d\n", res.second);
		}
	}
	return 0;
}
