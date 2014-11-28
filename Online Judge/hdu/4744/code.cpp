#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 105 << 1, M = N * N * 2;
const int inf = 1000000000;

struct eglist {
	int other[M], succ[M], last[N], cap[M], cost[M], sum;
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void _addEdge(int a, int b, int c, int d) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum] = d, cap[sum++] = c;
	}
	void addEdge(int a, int b, int c, int d) {
		_addEdge(a, b, c, d);
		_addEdge(b, a, 0, -d);
	}
}e;

int n, S, T, tot, totFlow, totCost;
int xPos[N], yPos[N], zPos[N], times[N], dis[N], slack[N], visit[N];

inline int sqr(int x) {
	return x * x;
}

int disCalc(int i, int j) {
	return (int)sqrt(1.0 * sqr(xPos[i] - xPos[j]) + sqr(yPos[i] - yPos[j]) + sqr(zPos[i] - zPos[j]));
}

int modlable() {
	int delta = inf;
	for(int i = 1; i <= T; i++) {
		if (!visit[i] && slack[i] < delta)
			delta = slack[i];
		slack[i] = inf;
	}
	if (delta == inf)
		return 1;
	for(int i = 1; i <= T; i++)
		if (visit[i])
			dis[i] += delta;
	return 0;
}

int dfs(int x, int flow) {
	if (x == T) {
		totFlow += flow;
		totCost += flow * (dis[S] - dis[T]);
		return flow;
	}
	visit[x] = 1;
	int left = flow;
	for(int i = e.last[x]; ~i; i = e.succ[i])
		if (e.cap[i] > 0 && !visit[e.other[i]]) {
			int y = e.other[i];
			if (dis[y] + e.cost[i] == dis[x]) {
				int delta = dfs(y, min(left, e.cap[i]));
				e.cap[i] -= delta;
				e.cap[i ^ 1] += delta;
				left -= delta;
				if (!left)
					return flow;
			} else {
				slack[y] = min(slack[y], dis[y] + e.cost[i] - dis[x]);
			}
		}
	return flow - left;
}

pair<int, int> minCost() {
	totFlow = 0, totCost = 0;
	fill(dis + 1, dis + T + 1, 0);
	do {
		do {
			fill(visit + 1, visit + T + 1, 0);
		} while(dfs(S, inf));
	} while(!modlable());
	return make_pair(totFlow, totCost);
}

int run() {
	scanf("%d", &n);
	if (!n)
		return 0;
	e.clear();
	S = 2 * n + 1, T = 2 * n + 2;
	tot = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", xPos + i, yPos + i, zPos + i, times + i);
		e.addEdge(S, i, times[i], 0);
		e.addEdge(i + n, T, times[i], 0);
		tot += times[i];
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if (i != j)
				e.addEdge(i, j + n, inf, disCalc(i, j));
	pair<int, int> tmp = minCost();
	//printf("%d %d\n", tmp.first, tmp.second);
	if (tmp.first != tot)
		printf("-1\n");
	else
		printf("%d\n", tmp.second);
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for(; run(); );
	return 0;
} 
