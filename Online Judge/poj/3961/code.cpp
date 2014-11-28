#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

const int N = 55555;

vector<int> e[N], ee[N];
int n, m, k, sz;
int dfn[N], low[N], times = 0;
vector<int> stk;
int inStk[N], up[N];
int size[N], w[N * 2], nxt[N * 2], visit[N], mark[N];
vector<int> cir;

void solve(int tail, int x, int father) {
	cir.clear();
	while(1) {
		cir.push_back(tail);
		if (tail == x)
			break;
		tail = up[tail];
	}
	reverse(cir.begin(), cir.end());
	
	int tot = (int)cir.size(), totSize = 0;
	for(int i = 0; i < tot; i++) {
		cir.push_back(cir[i]);
		totSize += size[cir[i]];
	}
	tot *= 2;
	for(int i = 0; i < tot; i++) {
		int u = cir[i];
		w[i] = size[u] % sz;
		if (w[i] == 0) {
			w[i] = sz;
		}
	}
	for(int i = 0, j = 0, c = 0; i < tot; i++) {
		while(j < tot && c < sz) {
			c += w[j];
			++j;
		}
		if (c == sz) {
			nxt[i] = j;
		} else {
			nxt[i] = -1;
		}
		c -= w[i];
	}
	int remain = totSize % sz;
	if (remain == 0)
		remain = sz;
	int ptr = tot / 2, vol = 0;
	while(ptr < tot && vol < remain) {
		vol += w[ptr];
		ptr++;
	}
	for(int i = tot / 2; i > 0; i--) {
		int xx = cir[i];
		while(vol > remain) {
			ptr--;
			vol -= w[ptr];
		}
		
		if (ptr <= tot / 2) {
			break;
		}
		
		if (vol == remain) {
			int j = ptr;
			bool fail = false;
			while(1) {
				if (j == i + tot / 2) {
					break;
				}
				if (nxt[j] == -1) {
					fail = true;
					break;	
				}
				if (nxt[j] > i + tot / 2) {
					fail = true;
					break;	
				}
				j = nxt[j];
			}
			if (!fail) {
				for(int p = i + 1; p < ptr; p++) {
					ee[cir[p - 1]].push_back(cir[p]);
					ee[cir[p]].push_back(cir[p - 1]);
				}
				int itr = ptr;
				while(1) {
					if (itr == i + tot / 2)
						break;
					for(int p = itr; p + 1 < nxt[itr]; p++) {
						ee[cir[p]].push_back(cir[p + 1]);
						ee[cir[p + 1]].push_back(cir[p]);
					}
					itr = nxt[itr];
				}
				size[x] = totSize;
				return ;
			}
		}
		
		vol += w[i - 1];
	}
	printf("-1\n");
	exit(0);
}

void tarjan(int x, int father) {
	up[x] = father;
	stk.push_back(x);
	inStk[x] = 1;
	dfn[x] = low[x] = ++times;
	size[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father) {
			continue;
		}
		if (!dfn[y]) {
			tarjan(y, x);
			if (low[y] > dfn[x]) {
				size[x] += size[y];
			}
			low[x] = min(low[x], low[y]);
			if (mark[x] != -1) {
				solve(mark[x], x, father);
				while(stk.back() != x) {
					inStk[stk.back()] = 0;
					stk.pop_back();
				}
				mark[x] = -1;
			}
		} else if (inStk[y]) {
			low[x] = min(low[x], dfn[y]);
			mark[y] = x;
		}
	}
	
	if (low[x] == dfn[x]) {
		if (size[x] % sz != 0) {
			ee[x].push_back(father);
			ee[father].push_back(x);
		}
		stk.pop_back();
		inStk[x] = 0;
	}
}

vector<int> points;

void dfs(int x) {
	points.push_back(x);
	visit[x] = 1;
	for(int i = 0; i < (int)ee[x].size(); i++) {
		int y = ee[x][i];
		if (!visit[y]) {
			dfs(y);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &k);
	sz = n / k;
	for(int i = 1; i <= m; i++) {
		int s, last = -1, x;
		scanf("%d", &s);
		for(int j = 1; j <= s; j++) {
			scanf("%d", &x);
			if (last != -1) {
				e[last].push_back(x);
				e[x].push_back(last);
			}
			last = x;
		}
	}
	for(int i = 1; i <= n; i++) {
		dfn[i] = 0;
		mark[i] = -1;
	}
	for(int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			tarjan(i, 0);
		}
	}
	for(int i = 1; i <= n; i++) {
		visit[i] = 0;
	}
	vector<vector<int> > ans;
	for(int i = 1; i <= n; i++) {
		if (!visit[i]) {
			points.clear();
			dfs(i);
			sort(points.begin(), points.end());
			if ((int)points.size() != sz) {
				printf("-1\n");
				return 0;
			}
			sort(points.begin(), points.end());
			ans.push_back(points);
		}
	}
	for(int i = 0; i < (int)ans.size(); i++) {
		for(int j = 0; j < (int)ans[i].size(); j++) {
			printf("%d%c", ans[i][j], j == sz - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
