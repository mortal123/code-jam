#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 50;

int n, m;
int next[MAXN], visit[MAXN];
char map[MAXN][MAXN];
int f[1 << 25], row[MAXN], cnt[1 << 25], num[1 << 25];

inline int lowbit(int &x) {
	return x & (-x);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);	
	for(int i = 0; i < n; i++) {
		scanf("%s", map[i]);
		row[i] = 0;
		for(int j = 0; j < m; j++)
			if (map[i][j] == '*')
				row[i] |= (1 << j);
	}
	int ans = min(n, m);
	int nm = max(n, m);
	for(int i = 1; i < (1 << nm); i++) {
		cnt[i] = cnt[i - lowbit(i)] + 1;
	}
	for(int i = 0, j = 1; i < n; i++, j *= 2) {
		num[j] = i;
	}
	// 0: occupy  1 : free 
	for(int i = 0; i < (1 << n); i++) {
		if (i != 0) {
			int tmp = lowbit(i);
			f[i] = (f[i - tmp] | row[num[tmp]]);
		}
		ans = min(ans, max(n - cnt[i], cnt[f[i]]));
	}
	printf("%d\n", ans);
	return 0;
} 
