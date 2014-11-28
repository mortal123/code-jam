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

int mergy(set<int> &a, set<int> &b) {
	if (a.size() < b.size())
		swap(a, b);
	int res = (1ll << 31) - 1;
	for(set<int> :: iterator it = b.begin(); it != b.end(); it++) {
		set<int> :: iterator it2 = a.lower_bound(*it);
		if (it2 != a.end())
			res = min(res, *it2 - *it);
		if (it2 != a.begin()) {
			--it2;
			res = min(res, *it - *it2);
		}
		a.insert(*it);
	}
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
		ans[x] = min(ans[x], mergy(s[x], s[y]));
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
