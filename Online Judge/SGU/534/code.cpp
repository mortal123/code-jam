#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 110000, MAXM = MAXN * 2;
const int inf = 1010000000;
struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], sum, cost[MAXM], change[MAXM];
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void addEdge(int a, int b, int c, int d) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum] = c, change[sum++] = d;
		other[sum] = a, succ[sum] = last[b], last[b] = sum, cost[sum] = c, change[sum++] = d;
	}
}e;

int dis[MAXN], choose[MAXN], f[MAXN], prev[MAXN], pre[MAXN], dep[MAXN];
int n, m;

int bfs(int s) {
	queue<int> q;
	static bool inQueue[MAXN];
	fill(inQueue + 1, inQueue + n + 1, 0);
	q.push(s);
	dis[s] = 0;
	inQueue[s] = 1;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (!inQueue[y]) {
				inQueue[y] = 1;
				q.push(y);
				pre[y] = x;
				prev[y] = i;
				dis[y] = dis[x] + e.cost[i];
			}
		}
	}
	int maxV = -1, maxP;
	for(int i = 1; i <= n; i++)
		if (maxV < dis[i]) {
			maxV = dis[i];
			maxP = i;
		}
	return maxP;
}

vector<int> ans;

int dfs(int x, int fa, int mode) {
	dep[x] = 0;
	f[x] = inf;
	int maxCost = 0;
	for(int i = e.last[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == fa)
			continue;
		dfs(y, x, 2);
		if (dep[y] + e.cost[i] > dep[x]) {
			choose[x] = i;
			dep[x] = dep[y] + e.cost[i];
			f[x] = maxCost = min(f[y], e.change[i]);
		} else if (dep[y] + e.cost[i] == dep[x]) {
			int cost = min(f[y], e.change[i]);
			f[x] += cost;
			if (cost > maxCost) {
				choose[x] = i;
				maxCost = cost;
			}
		}
	}
	if (mode == 1)
		f[x] -= maxCost;
	return f[x];
}

int dfsAns(int x, int fa, int mode) {
	for(int i = e.last[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == fa)
			continue;
		if (dep[x] > dep[y] + e.cost[i])
			continue;
		if (mode == 1 && i == choose[x])
			continue;
		if (e.change[i] <= f[y]) {
			ans.push_back(i / 2 + 1);
		} else {
			dfsAns(y, x, 2);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	e.clear();
	for(int i = 1; i < n; i++) {
		int a, b, t, p;
		scanf("%d %d %d %d", &a, &b, &t, &p);
		e.addEdge(a, b, t, p);
	}
	int s, t;
	t = bfs(s = bfs(1));
	//cerr << s << " " << t << endl;
	for(int mid = t, mid2; ; mid = pre[mid2 = mid]) {
		if (2 * dis[mid] == dis[t]) {
			dfs(mid, 0, 1);
			printf("%d\n", f[mid]);
			dfsAns(mid, 0, 1);
			break;
		} else if (2 * dis[mid] < dis[t]) {
			int L = dfs(mid, mid2, 2), R = dfs(mid2, mid, 2);
			int Mid = e.change[prev[mid2]];
			if (Mid <= L && Mid <= R) {
				printf("%d\n", Mid);
				ans.push_back(prev[mid2] / 2 + 1);
			} else if (L <= Mid && L <= R) {
				printf("%d\n", L);
				dfsAns(mid, mid2, 2);
			} else if (R <= Mid && R <= L) {
				printf("%d\n", R);
				dfsAns(mid2, mid, 2);
			}
			break;
		}
	}
	printf("%d\n", ans.size());
	sort(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		printf("%d ", ans[i]);
	return 0;
} 
