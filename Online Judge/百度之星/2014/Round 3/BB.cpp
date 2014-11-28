#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int M = 15;

int s[N], pos[N][2], father[M][N], value[N];
int n, root, dep[N], tot;
vector<int> e[N];

void dfs(int x, int fa) {
	father[0][x] = fa;
	pos[x][0] = ++tot;
	dep[x] = dep[fa] + 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == fa)
			continue;
		dfs(y, x);
	}
	pos[x][1] = tot;
}

int lowbit(int x) {
	return x & (-x);
}

void ins(int s[N], int pos, int v) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		s[i] += v;
	}
}

int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += s[i];
	}
	return res;
}

int LCA(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	for(int i = M - 1; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b])
			a = father[i][a];
	}
	if (a == b)
		return a;
	for(int i = M - 1; i >= 0; i--) {
		if (father[i][a] != father[i][b]) {
			a = father[i][a];
			b = father[i][b];
		}
	}
	return father[0][a];
}

int jump(int x, int t) {
	for(int i = M - 1; i >= 0; i--) {
		if (t >> i & 1) {
			x = father[i][x];
		}
	}
	return x;
}

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			s[i] = 0;
			e[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		tot = 0;
		root = 1;
		dfs(1, 0);
		for(int i = 1; i < M; i++)
			for(int j = 1; j <= n; j++)
				father[i][j] = father[i - 1][father[i - 1][j]];
		for(int i = 1; i <= n; i++) {
			scanf("%d", &value[i]);
			ins(s, pos[i][0], value[i]);
		}
		static int testCount = 0;
		printf("Case #%d:\n", ++testCount);
		int q;
		scanf("%d", &q);
		for(int i = 1; i <= q; i++) {
			static char buf[10];
			scanf("%s", buf);
			if (buf[0] == 'Q') {
				int x;
				scanf("%d", &x);
				if (x == root) {
					printf("%d\n", ask(n));
				} else if (LCA(x, root) == x) {
					int t = jump(root, dep[root] - dep[x] - 1);
					printf("%d\n", ask(n) - (ask(pos[t][1]) - ask(pos[t][0] - 1)));
				} else {
					printf("%d\n", ask(pos[x][1]) - ask(pos[x][0] - 1));
				}
			} else if (buf[0] == 'C') {
				int x, y;
				scanf("%d %d", &x, &y);
				ins(s, pos[x][0], y - value[x]);
				value[x] = y;
			} else {
				int r;
				scanf("%d", &r);
				root = r;
			}
		}
		
	}
	return 0;
} 
