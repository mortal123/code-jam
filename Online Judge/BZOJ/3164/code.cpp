#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAXN = 210000;
const int inf = int(1e9);
struct eglist {
	int other[MAXN], succ[MAXN], last[MAXN], sum;
	void AddEdge(int a, int b) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
	}
	void clear(int n) {
		for(int i = 0; i <= n; i++)
			last[i] = 0;
		sum = 0;
	}
}e;

int hash[MAXN], f[MAXN], dgr[MAXN];
int n;

void dfs(int x, int first) {
	if (dgr[x] == 0) {
		f[x] = 1;
		return ;
	}
	if (first) {
		f[x] = inf;
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			dfs(y, first ^ 1);
			f[x] = min(f[x], f[y]);
		}
	} else {
		f[x] = 0;
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			dfs(y, first ^ 1);
			f[x] += f[y];
		} 
	}
}

void find(int x, int first) {
	if (dgr[x] == 0) {
		hash[x]++;
		return;
	}
	
	for (int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (first) {
			if (f[x] == f[y])
				find(y, first ^ 1);
		} else {
			find(y, first ^ 1);
		}
	}
}

void Solve(int root, int first) {
	dfs(root, first);
	find(root, first);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	e.clear(n);
	for (int i = 1; i <= n; i++) {
		hash[i] = 0;
		dgr[i] = 0;
	}
	for (int i = 2; i <= n; i++) {
		int x;
		scanf("%d", &x);
		e.AddEdge(x, i);
		dgr[x]++;
	}
	
	Solve(1, 0);
	Solve(1, 1);
	int MinNum = inf, cnt = 0, xr = 0;
	for (int i = 1; i <= n; i++) {
		if (hash[i] == 2) {
			MinNum = min(MinNum, i);
			cnt++;
			xr ^= i;
		}
	}
	assert(MinNum != inf);
	printf("%d %d %d\n", MinNum, cnt, xr);
	return 0;
}
