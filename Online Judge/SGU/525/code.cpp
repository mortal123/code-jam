#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <bitset>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 1100, MAXM = 21000;

int n, m;
struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], sum;
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void addEdge(int a, int b) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum++; 
	}
}e, g;

int DFN[MAXN], low[MAXN], color[MAXN], totColor, Index, stack[MAXN], inStack[MAXN];
int size[MAXN], top;
int map[MAXN][MAXN];

void dfs(int x, int fa) {
	DFN[x] = low[x] = ++Index;
	stack[++top] = x;
	inStack[x] = 1;
	
	for(int i = e.last[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (y == fa)
			continue;
		if (!DFN[y]) {
			dfs(y, x);
			low[x] = min(low[x], low[y]);
		} else if (inStack[y]) {
			low[x] = min(low[x], DFN[y]);
		}
	}
	
	if (DFN[x] == low[x]) {
		do {
			color[stack[top]] = totColor;
			size[totColor]++;
			inStack[stack[top]] = 0;
		} while(stack[top--] != x);
		++totColor;
	}
}

int dgr[MAXN];

void flood(int s, int x) {
	if (map[s][x])
		return ;
	map[s][x] = 1;
	for(int i = g.last[x]; ~i; i = g.succ[i]) {
		int y = g.other[i];
		flood(s, y);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	e.clear();
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		e.addEdge(a, b);
	}
	fill(DFN, DFN + n, -1);
	fill(low, low + n, -1);
	for(int i = 0; i < n; i++)
		if (DFN[i] == -1) {
			dfs(i, 0);
		}
	g.clear();
	for(int i = 0; i < n; i++)
		for(int j = e.last[i]; ~j; j = e.succ[j]) {
			int y = e.other[j];
			if (color[y] != color[i]) {
				g.addEdge(color[i], color[y]);
			}
		}
	for(int i = 0; i < totColor; i++)
		flood(i, i);
	int w = 1;
	vector<int> ans;
	for(int x = 0; x < n; x++)
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (color[x] == color[y]) {
				if (size[color[x]] > w) {
					ans.clear();
					w = size[color[x]];
				}
				if (size[color[x]] == w) {
					ans.push_back(i + 1);
					w = size[color[x]];
				}
			} else {
				int now = 0;
				for(int j = 0; j < totColor; j++) {
					if (map[color[x]][j] && map[j][color[y]]) {
						now += size[j];
					}
				}
				if (now > w) {
					ans.clear();
					w = now;
				} 
				if (now == w) {
					ans.push_back(i + 1);
				}
			}
		}
	printf("%d\n", w);
	printf("%d\n", ans.size());
	sort(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
} 
