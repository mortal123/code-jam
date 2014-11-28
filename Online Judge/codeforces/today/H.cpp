#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cstring>
#include <vector>
#include <queue>
#pragma comment(linker, "/STACK:36777216")
using namespace std;

const int MAXN = 110000, MAXM = MAXN * 2;
int n;

struct eglist {
	int other[MAXM], succ[MAXM], cost[MAXM], sum, last[MAXM];
	void clear() {
		sum = 0;
		memset(last, -1, sizeof(last));
	}
	void addEdge(int a, int b, int c) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum++] = c;
		other[sum] = a, succ[sum] = last[b], last[b] = sum, cost[sum++] = c;
	}
}e;

int size[MAXN];
int cur[MAXM], cost[MAXM];
int ans[MAXM];
priority_queue<long long> q;
map<long long, int> Del, cover;

void dfs(int x, int fa) {
	size[x] = 1;
	for(int i = e.last[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == fa)
			continue;
		dfs(y, x);
		q.push((long long)size[y] * e.cost[i]);
		cur[i / 2] = size[y];
		cost[i / 2] = e.cost[i];
		size[x] += size[y];
	}
}

long long getTop() {
	while(Del[q.top()]) {
		Del[q.top()]--;
		q.pop();
	}
	return q.top();
}

void Delete(int x, long long v) {
	if (v == 0)
		v = 0;
	ans[x] += cover[v];
	Del[v]++;
}

void Insert(int x, long long v) {
	if (v == 0)
		v = 0;
	ans[x] -= cover[v];
	q.push(v);
}

void change(int x) {
	Delete(x, (long long)cur[x] * cost[x]);
	
	cur[x] = n - cur[x];
	Insert(x, (long long)cur[x] * cost[x]);
}

void dfs2(int x, int fa) {
	cover[getTop()]++;
	for(int i = e.last[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == fa)
			continue;
		change(i / 2);
		dfs2(y, x);
		change(i / 2);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	e.clear();
	for(int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		e.addEdge(a, b, c);
	}
	dfs(1, -1);
	dfs2(1, -1);
	for(int i = 0; i < n - 1; i++) {
		ans[i] += cover[(long long)cur[i] * cost[i]];
	}
	int res = 0;
	for(int i = 0; i < n - 1; i++)
		res = max(ans[i], res);
	printf("%d\n", res);
	return 0;
}
