#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1000;

vector<int> e[N];
int color[N], fa[N];

int ok(int x, int tar, double &res) {
	res = 0;
	bool flag = false;
	while(x) {
		if (x == tar)
			flag = true;
		if (fa[x] && color[x] != color[fa[x]])
			res++;
		x = fa[x];
	}
	return flag;
}

void dfs(int x, int f) {
	fa[x] = f;
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f)
			continue;
		dfs(y, x);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		int n, q;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			e[i].clear();
		for(int i = 2; i <= n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a++; b++;
			e[a].push_back(b);
			e[b].push_back(a);
		}
		dfs(1, 0);
		for(int i = 1; i <= n; i++) {
			color[i] = i;
		}
		int totColor = n;
		scanf("%d", &q);
		while(q--) {
			char type[10];
			int x;
			scanf("%s %d", type, &x);
			++x;
			if (type[0] == 'O') {
				++totColor;
				while(x) {
					color[x] = totColor;
					x = fa[x];
				}
			} else {
				double ans = 0;
				int size = 0;
				for(int i = 1; i <= n; i++) {
					double tmp = 0;
					if (ok(i, x, tmp))
						size++, ans += tmp;
				}
				printf("%.10f\n", ans / size);
			}
		}
	}
	return 0;
}
