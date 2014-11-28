#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110000;

vector<int> e[MAXN];
vector<int> anss[2];
vector<pair<int, int> > ee[MAXN];

int n, m, visit[MAXN], a[MAXN], del[MAXN], conj[MAXN];

int go(int x, int from) {
	if (e[x][0] == from)
		return e[x][1];
	return e[x][0];
}

void dfs(int x, int color) {
	if (del[x])
		return;
	visit[x] = color;
	anss[color].push_back(x);
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (visit[y] == -1)
			dfs(y, color ^ 1);
	}
} 

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	for(int i = 1; i <= n; i++) {
		if (e[i].size() == 4) {
			for(int j = 0; j < 4; j++) {
				int y = e[i][j];
				int x = i;
				int from = x, length = 0;
				while(e[y].size() == 2) {
					int bak = y;
					y = go(y, from);
					from = bak;
					length++;
				}
				ee[x].push_back(make_pair(y, length));
			}
			sort(ee[i].begin(), ee[i].end());
		}
	}
	
	fill(visit + 1, visit + n + 1, 0);
	for(int i = 1; i <= n; i++) {
		if (e[i].size() == 2 || visit[i])
			continue;
			
		int x = i, len = 0, y = ee[i][0].first, cirLength = 0;
		while(1) {
			int w = 0, l;
			if (y == ee[x][2].first)
				w = 2;
			l = ee[x][w].second + ee[x][w + 1].second;
			cirLength += ee[x][w].second + 1;
			a[++len] = l % 2;
			conj[len] = y;
			
			if (y == i)
				break;
				
			if (x == ee[y][0].first) {
				x = y; y = ee[y][2].first;
			} else {
				x = y; y = ee[y][0].first;
			}
		}
		
		int cntOdd = 0;
		for(int j = 1; j <= len; j++)
			cntOdd += a[j];
		if (cntOdd == len) {
			for(int j = 1; j <= len; j += 2) {
				del[conj[j]] = 1;
			}
		} else if (cntOdd == 0) {
			if (cirLength % 2 == 1) {
				del[i] = 1;
			}
		} else {
			int j = 1;
			while(a[j] == 1)
				j = j % len + 1;
			bool flag = false;
			for(int k = j; ; k = (k % len) + 1) {
				if (a[k] == 1 && flag == false) {
					del[conj[k]] = 1;
					flag = true;
				} else {
					flag = false;
				}
				if (k % len + 1 == j)
					break;
			}
		}
		
		for(int j = 1; j <= len; j++)
			visit[conj[j]] = 1;
	}
	
	fill(visit + 1, visit + n + 1, -1);
	for(int i = 1; i <= n; i++)
		if (visit[i] == -1) {
			dfs(i, 0);
		}
	sort(anss[0].begin(), anss[0].end());
	sort(anss[1].begin(), anss[1].end());
	for(int i = 0; i < 2; i++) {
		printf("%d", anss[i].size());
		for(int j = 0; j < anss[i].size(); j++)
			printf(" %d", anss[i][j]);
		printf("\n");
	}
	return 0;
}
