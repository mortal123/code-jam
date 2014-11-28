#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 205;
const int inf = 100000000;

int a[N], b[N], c[N][N], vx[N], vy[N], w[N][N], dx[N], dy[N];
int ans, m, n, slack[N], lk[N], next[N];

bool hungary(int x) {
	vx[x] = 1;
	for(int i = 1; i <= n; i++) {
		if (vy[i])
			continue;
		int delta = dx[x] + dy[i] - w[x][i];
		if (delta == 0) {
			vy[i] = 1;
			if (b[i]) {
				lk[x] = i;
				next[x] = 0;
				return true;
			}
			for(int j = 1; j <= m; j++) {
				if (vx[j])
					continue;
				if (c[j][i] && hungary(j)) {
					lk[x] = i;
					next[x] = j;
					return true;
				}
			}
		} else {
			slack[i] = min(slack[i], delta);
		}
	}
	return false;
}

void travel(int x) {
	int flow = a[x];
	for(int i = x; i; i = next[i]) {
		if (next[i])
			flow = min(flow, c[next[i]][lk[i]]);
		else 
			flow = min(flow, b[lk[i]]);
	}
	a[x] -= flow;
	for(int i = x; i; i = next[i]) {
		if (next[i])
			c[next[i]][lk[i]] -= flow;
		else
			b[lk[i]] -= flow;
		c[i][lk[i]] += flow;
	}
}

int Main() {
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);	
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++) {
			scanf("%d", &w[i][j]);
			w[i][j] *= -1;
			c[i][j] = 0;
	}
	memset(dy, 0, sizeof(dy));
	for(int i = 1; i <= m; i++) {
		dx[i] = -inf;
		for(int j = 1; j <= n; j++)
			dx[i] = max(dx[i], w[i][j]);
	}
	for(int i = 1; i <= m; i++) {
		while(1) {
			for(int j = 1; j <= n; j++)
				slack[j] = inf;
			while (a[i]) {
				fill(vx + 1, vx + m + 1, 0);
				fill(vy + 1, vy + n + 1, 0);
				if (hungary(i))
					travel(i);
				else
					break;
			}
			if (!a[i])
				break;
			int delta = inf;
			for(int j = 1; j <= n; j++)
				if (!vy[j])
					delta = min(delta, slack[j]);
			for(int j = 1; j <= m; j++)
				if (vx[j])
					dx[j] -= delta;
			for(int j = 1; j <= n; j++)
				if (vy[j])
					dy[j] += delta;
		}
	}
	long long ans = 0;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++) {
			ans += (long long)c[i][j] * w[i][j];
		}
	cout << -ans << endl;
	return 0;
} 

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int testCount;
	scanf("%d", &testCount);
	while(testCount--) {
		Main();
	}
	return 0;
}
