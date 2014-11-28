#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 100005;
const int inf = 1000000000;

int fa[MAXN], Min[MAXN], n, m;

int find(int x) {
	int p = x;
	while(fa[p] != p)
		p = fa[p];
	while(x != p) {
		int t = fa[x];
		fa[x] = p;
		x = t;
	}
	return p;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(scanf("%d %d", &n, &m) == 2) {
		for(int i = 1; i <= n; i++)
			fa[i] = i;
		for(int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (find(a) != find(b)) {
				fa[find(a)] = find(b);
			}
		}
		for(int i = 1; i <= n; i++)
			find(i);
		for(int i = 1; i <= n; i++)
			Min[i] = inf;
		for(int i = 1; i <= n; i++) {
			int C;
			scanf("%d", &C);
			if (C < 0)
				continue;
			Min[fa[i]] = min(Min[fa[i]], C);
		}
		int flag = 1;
		for(int i = 1; i <= n; i++) {
			if (fa[i] == i && Min[i] == inf)
				flag = 0;
		}
		if (!flag) {
			printf("-1\n");
			continue;
		}
		long long ans = 0;
		long long mm = inf, cnt = 0;
		for(int i = 1; i <= n; i++)
			if (fa[i] == i)
				ans += Min[i], mm = min(mm, (long long)Min[i]), cnt++;
		if (cnt == 1) {
			cout << 0 << endl;
		} else {
			cout << ans + mm * (cnt - 2) << endl;
		}
	}
	return 0;
}
