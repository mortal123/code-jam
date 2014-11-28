#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 111, M = 20;
const long long INF = (1LL << 60);

long long cost[1 << M];
int n, m, b;

struct Node {
	int code, v, need;
}p[N];

inline int cmp(const Node &a, const Node &b) {
	return a.need < b.need;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &m, &b);
	for(int i = 0; i < (1 << m); i++) {
		cost[i] = INF;
	}
	for(int i = 1; i <= n; i++) {
		int c, s = 0;
		scanf("%d %d %d", &p[i].v, &p[i].need, &c);
		for(int j = 1; j <= c; j++) {
			int x;
			scanf("%d", &x);
			x--;
			s |= (1 << x);
		}
		p[i].code = s;
	}
	sort(p + 1, p + n + 1, cmp);
	cost[0] = 0;
	long long ans = INF;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (1 << m); j++) {
			cost[j | p[i].code] = min(cost[j | p[i].code], cost[j] + p[i].v);
		}
		if (cost[(1 << m) - 1] < INF)
			ans = min(ans, cost[(1 << m) - 1] + 1LL * b * p[i].need);
	}
	if (ans == INF) {
		printf("-1\n");
	} else {
		printf("%I64d\n", ans);
	}
	return 0;
} 
