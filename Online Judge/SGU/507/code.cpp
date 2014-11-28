#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
using namespace std;

const int MAXN = 60000;

int size[MAXN], val[MAXN], ans[MAXN];
int fa[MAXN];
int n, m;
set<int> s[MAXN];
vector<int> vec[MAXN], ls[MAXN];
int be[MAXN];

int Insert(int a, int b) {
	set<int> :: iterator it;
	int res = (1ll << 31) - 1;
	it = s[a].lower_bound(b);
	if (it != s[a].end())
		res = min(res, *it - b);
	if (it != s[a].begin()) {
		--it;
		res = min(res, b - *it);
	}
	s[a].insert(b);
	return res;
}

void dfs(int x) {
	if (!vec[x].size()) {
		be[x] = x;
		s[x].insert(val[x]);
		return;
	}
	be[x] = 0;
	for(int i = 0; i < vec[x].size(); i++) {
		int y = vec[x][i];
		dfs(y);
		ans[x] = min(ans[x], ans[y]);
		if (be[x] == 0) {
			be[x] = be[y];
		} else {
			int a = be[x], b = be[y];
			if (s[a].size() > s[b].size()) {
				for(set<int> :: iterator it = s[b].begin(); it != s[b].end(); ++it) {
					ans[x] = min(ans[x], Insert(a, *it));
				}
			} else {
				swap(a, b);
				for(set<int> :: iterator it = s[b].begin(); it != s[b].end(); ++it) {
					ans[x] = min(ans[x], Insert(a, *it));
				}
				be[x] = be[y];
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 2; i <= n; i++) {
		scanf("%d", &fa[i]);
		vec[fa[i]].push_back(i);
	}
	for(int i = n - m + 1; i <= n; i++)
		scanf("%d", &val[i]);
	for(int i = 1; i <= n; i++)
		ans[i] = (1ll << 31) - 1;
	dfs(1);
	for(int i = 1; i <= n - m; i++) {
		printf("%d%c", ans[i], i == n - m ? '\n' : ' ');
		assert(ans[i] >= 0);
	}
	return 0;	
}
