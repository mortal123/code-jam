#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5555;

vector<int> e[N];
int n, cnt[N], limit;
long long ans = 0;
int path[N];

void dfs(int dep, int x) {
	path[dep] = x;
	if (dep && dep % 2 == 0 && x < limit) {
		cnt[path[dep / 2 + 1]]++;
	}
	
	int total = 0;
	
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (dep && y == path[dep - 1])
			continue;
		dfs(dep + 1, y);
		ans += 1LL * total * cnt[y];
		total += cnt[y];
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}	
	for(int i = n; i >= 1; i--) {
		limit = i;
		for(int j = 1; j <= n; j++)
			cnt[j] = 0;
		dfs(0, i);
	}
	printf("%lld\n", ans);
	return 0;
}
