#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110;

int map[MAXN][MAXN];
int n, m;
int color[MAXN], totColor;
int a[MAXN], len;
vector<int> vc[MAXN], tmp;
int visit[MAXN];

void No() {
	printf("NO\n");
	exit(0);
}

void dfs(int x, int c) {
	if (visit[x]) {
		if (visit[x] != c)
			No();
		return;
	}
	visit[x] = c;
	tmp.push_back(x);
	for(int i = 1; i <= n; i++)
		if (map[x][i] == 0) {
			if (i == vc[color[x]][0] || i == vc[color[x]][1] || i == vc[color[x]][2])
				continue;
			dfs(i, -c);
		}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);	
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = map[b][a] = 1;
	}
	if (n % 3 != 0) {
		No();
	}
	for(int i = 1; i <= n; i++) {
		len = 0;
		for(int j = 1; j <= n; j++)
			if (map[i][j] == 0 && i != j) {
				a[++len] = j;
			}
		if (len < 2)
			No();
		int aj, ak, cnt = 0;
		for(int j = 1; j <= len; j++)
			for(int k = j + 1; k <= len; k++) {
				if (map[a[j]][a[k]] == 0) {
					cnt++;
					aj = a[j], ak = a[k];
				}
			}
		if (cnt != 1)
			No();
		if (color[i] || color[aj] || color[ak]) {
			if (color[i] != color[aj] || color[i] != color[ak] || color[aj] != color[ak])
				No();
		} else {
			color[i] = color[aj] = color[ak] = ++totColor;
			vc[totColor].push_back(i);
			vc[totColor].push_back(aj);
			vc[totColor].push_back(ak);
		}
	}
	if (totColor != n / 3)
		No();
	for(int i = 1; i <= n; i++)
		if (visit[i] == 0) {
			tmp.clear();
			dfs(i, 1);
			for(int j = 0; j < tmp.size(); j++)
				for(int k = j + 1; k < tmp.size(); k++) {
					if (color[tmp[j]] == color[tmp[k]])
						No();
					if ((visit[tmp[j]] != visit[tmp[k]]) ^ (map[tmp[j]][tmp[k]]) == 0)
						No();
				}
		}
	printf("YES\n");
	return 0;
}
