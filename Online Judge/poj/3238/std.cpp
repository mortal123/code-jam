#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
 
#pragma comment(linker, "/STACK:4777216")
 
using namespace std;
 
#define foreach(e,x) for(vector<pair<int, int> >::iterator e=(x).begin(); e!=(x).end(); ++e)
 
const int N = 100000 + 10;
const int MOD = 19880830;
const int INF = 1000000000 + 10;
 
int n, m, s, t, q;
int ret[N], cnt[N];
int distS[N], distT[N], distO[N];
int waysS[N], waysT[N], waysO[N];
int onPath[N], layer[N], inQue[N];
int value[N << 1], ways[N << 1];
vector<int> path;
vector<int> lays[N];
vector<pair<int, int> > adj[N];
 
void dij(int s, int *dist, int *ways)
{
	static int in[N];
	for(int i = 0; i < n; ++ i) {
		in[i] = false;
		ways[i] = 0;
		dist[i] = INF;
	}
	ways[s] = 1;
	dist[s] = 0;
	priority_queue<pair<int, int> > que;
	que.push(make_pair(0, s));
	for( ; que.size(); ) {
		int u = que.top().second;
		que.pop();
		if (in[u]) continue;
		in[u] = true;
		foreach(it, adj[u]) {
			int v = it->first;
			if (dist[v] > dist[u] + it->second) {
				dist[v] = dist[u] + it->second;
				ways[v] = ways[u];
				que.push(make_pair(-dist[v], v));
			} else if (dist[v] == dist[u] + it->second) {
				(ways[v] += ways[u]) %= MOD;
			}
		}
	}
}
 
void dfs(int u, int depth, int on)
{
	layer[u] = depth;
	lays[depth].push_back(u);
	if (on) {
		path.push_back(u);
		onPath[u] = true;
		foreach(it, adj[u]) {
			int v = it->first;
			if (distS[v] != distS[u] + it->second || layer[v] != -1) continue;
			if (distT[v] + it->second == distT[u]) {
				dfs(v, depth + 1, true);
				break;
			}
		}
	}
	foreach(it, adj[u]) {
		int v = it->first;
		if (distS[v] != distS[u] + it->second || layer[v] != -1) continue;
		dfs(v, depth, false);
	}
}
 
void update(int id, int x, int y)
{
	if (value[id] > x || value[id] < 0) {
		value[id] = x;
		ways[id] = y;
	} else if (value[id] == x) {
		(ways[id] += y) %= MOD;
	}
}
 
inline int getId(const int &l, const int &r)
{
	return l + r | l != r;
}
 
void modify(int l, int r, int a, int b, int x, int y)
{
	if (a > b) return;
	if (r < a || b < l) return;
	if (y == 0) return;
	int id = getId(l, r);
	if (a <= l && r <= b) {
		update(id, x, y);
		return;
	}
	int mid = (l + r) >> 1;
	if (value[id] >= 0) {
		update(getId(l, mid), value[id], ways[id]);
		update(getId(mid + 1, r), value[id], ways[id]);
		value[id] = -1;
	}
	modify(l, mid, a, b, x, y);
	modify(mid + 1, r, a, b, x, y);
}
 
pair<int, int> getValue(int l, int r, int p)
{
	int id = getId(l, r);
	if (l == r) return make_pair(value[id], ways[id]);
	int mid = (l + r) >> 1;
	if (value[id] >= 0) {
		update(getId(l, mid), value[id], ways[id]);
		update(getId(mid + 1, r), value[id], ways[id]);
		value[id] = -1;
	}
	if (p <= mid)
		return getValue(l, mid, p);
	return getValue(mid + 1, r, p);
}
 
void solve()
{
	-- s, -- t;
	for(int i = 0; i < n; ++ i) {
		adj[i].clear();
		ret[i] = cnt[i] = 0;
	}
	int u, v, w;
	for(int i = 0; i < m; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		-- u, -- v;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
	}
 
	dij(t, distT, waysT);
 
	if (distT[s] == INF) { //if s and t is not connected
		for(int i = 0; i < q; ++ i) {
			scanf("%d", &w);
			printf("%d%c", 0, i + 1 == q ? '\n' : ' ');
		}
		return;
	}
 
	dij(s, distS, waysS);
 
	for(int i = 0; i < n; ++ i) {//build a SPT
		layer[i] = -1;
		lays[i].clear();
		onPath[i] = false;
	}
	path.clear();
	dfs(s, 0, 1);
 
	for(int i = 0; i < (int)path.size(); ++ i) { //get distO[u]
		priority_queue<pair<int, int> > que;
		for(int j = 0; j < (int)lays[i].size(); ++ j) {
			int u = lays[i][j];
			distO[u] = INF;
			waysO[u] = 0;
			inQue[u] = false;
			if (onPath[u]) continue;
			foreach(e, adj[u]) {
				int v = e->first;
				if (layer[v] >= layer[u]) continue;
				if (distO[u] > distS[v] + e->second) {
					distO[u] = distS[v] + e->second;
					waysO[u] = waysS[v];
				} else if (distO[u] == distS[v] + e->second) {
					(waysO[u] += waysS[v]) %= MOD;
				}
			}
			que.push(make_pair(-distO[u], u));
		}
		for( ; que.size(); ) {
			int u = que.top().second;
			que.pop();
			if (inQue[u]) continue;
			inQue[u] = true;
			foreach(e, adj[u]) {
				int v = e->first;
				if (onPath[v]) continue;
				if (layer[v] != i) continue;
				if (distO[v] > distO[u] + e->second) {
					distO[v] = distO[u] + e->second;
					waysO[v] = waysO[u];
					que.push(make_pair(-distO[v], v));
				} else if (distO[v] == distO[u] + e->second) {
					(waysO[v] += waysO[u]) %= MOD;
				}
			}
		}
	}
 
	for(int i = 0; i < n; ++ i) {
		if (onPath[i]) continue;
		if (distS[i] + distT[i] == distS[t]) {
			ret[i] = distS[t];
			cnt[i] = (waysS[t] - (long long)waysS[i] * waysT[i] % MOD + MOD) % MOD;
		} else {
			ret[i] = distS[t];
			cnt[i] = waysS[t];
		}
	}
 
	memset(value, -1, sizeof value);
	for(int u = 0; u < n; ++ u) {
		if (distS[u] >= INF) continue;
		foreach(it, adj[u]) {
			int v = it->first;
			if (layer[v] >= layer[u]) continue;
			int l = layer[v], r = layer[u] - 1;
			modify(0, path.size() - 1, l + 1, r, distS[v] + distT[u] + it->second, (long long)waysS[v] * waysT[u] % MOD);
			if (! onPath[v]) {
				modify(0, path.size() - 1, l, l, distO[v] + distT[u] + it->second, (long long)waysO[v] * waysT[u] % MOD);
			}
		}
	}
	for(int i = 0; i < (int)path.size(); ++ i) {
		pair<int, int> tmp = getValue(0, path.size() - 1, i);
		if (tmp.first >= 0) {
			ret[path[i]] = tmp.first;
			cnt[path[i]] = tmp.second;
		}
	}
 	cout << endl;
 	for(int i = 0; i < n; ++i) {
 		cout << ret[i] << " " << cnt[i] << endl;
 	}
	for(int i = 0; i < q; ++ i) {
		long long x, answer = 0, tmp = 1;
		cin >> x;
		for(int j = 0; j < n; ++ j) {
			(answer += tmp * ret[j]) %= MOD;
			tmp = tmp * x % MOD;
			(answer += tmp * cnt[j]) %= MOD;
			tmp = tmp * x % MOD;
		}
		printf("%d%c", (int)answer, i + 1 == q ? '\n' : ' ');
	}
}
 
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	int test = 0;
	for( ; cin >> n >> m >> s >> t >> q && (n || m || s || t || q); ) {
		cout << "Case " << ++ test << ": ";
		solve();
		cout << endl;
	}
	return 0;
}
