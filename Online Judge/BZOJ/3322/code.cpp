#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, pair<int, int> > > edges;

const int N = 111111, MAX_DEP = 20;;
const long long INF = (1LL << 60);

int n, m, q;
int trade[N];
long long upper[N];
int set[N], father[N][MAX_DEP];
long long fv[N][MAX_DEP];
vector<pair<int, long long> > e[N];
int dep[N], order[N];

void bfs(int s) {
	vector<int> q;
	
	q.push_back(s);
	father[s][0] = 0;
	dep[s] = 0;
	
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (y == father[x][0])
				continue;
			dep[y] = dep[x] + 1;
			fv[y][0] = e[x][i].second;
			father[y][0] = x;
			q.push_back(y);
		}
	}
}

long long solve(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	
	long long res = INF;
	
	for(int i = MAX_DEP - 1; i >= 0; i--)
		if (dep[a] - (1 << i) >= dep[b]) {
			res = min(res, fv[a][i]);
			a = father[a][i];
		}
	
	if (a == b)
		return res;
	
	for(int i = MAX_DEP - 1; i >= 0; i--) 
		if (father[a][i] != father[b][i]) {
			res = min(res, min(fv[a][i], fv[b][i]));
			a = father[a][i];
			b = father[b][i];
		}
	return min(res, min(fv[a][0], fv[b][0]));
}

int find(int x) {
	int c = x;
	while(set[c] != c)
		c = set[c];
	
	while(x != c) {
		int t = set[x];
		set[x] = c;
		x = t;
	}
	return c;
}

int mergy(int a, int b) {
	set[find(a)] = find(b);
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &order[i]);
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &trade[i]);
	}
	
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.push_back(make_pair(w, make_pair(u, v)));
	}
	
	sort(edges.begin(), edges.end());
	
	for(int i = 1; i <= n + 1; i++)
		set[i] = i;
	
	for(int i = 1; i <= q; i++) {
		int x;
		scanf("%d", &x);
		mergy(x, n + 1);
		e[n + 1].push_back(make_pair(x, INF));
		e[x].push_back(make_pair(n + 1, INF));
	}
	
	for(int i = (int)edges.size() - 1; i >= 0; i--) {
		int u = edges[i].second.first, v = edges[i].second.second;
		
		if (find(u) != find(v)) {
			mergy(u, v);
			e[u].push_back(make_pair(v, edges[i].first));
			e[v].push_back(make_pair(u, edges[i].first));
		}
	}
	
	if (q == 0) {
		e[n + 1].push_back(make_pair(1, INF));
		e[1].push_back(make_pair(n + 1, INF));
	}
	
	bfs(1);
	
	for(int i = 1; i < MAX_DEP; i++)
		for(int j = 1; j <= n + 1; j++) {
			father[j][i] = father[father[j][i - 1]][i - 1];
			fv[j][i] = min(fv[j][i - 1], fv[father[j][i - 1]][i - 1]);
		}
	
	long long cur = 0;
	
	for(int i = n; i >= 1; i--) {
		int x = order[i];
		upper[x] = cur;
		
		if (trade[x] < 0)
			cur -= trade[x];
		
		if (i > 1)
			cur = min(cur, solve(order[i], order[i - 1]));
	}
	
	cur = 0;
	
	for(int i = 1; i <= n; i++) {
		int x = order[i];
		if (trade[x] < 0) {
			printf("%lld\n", min(1LL * -trade[x], cur));
			cur -= min(1LL * -trade[x], cur);
		} else {
			//printf("%d\n", min(next - cur, trade[x]));
			cur = min(cur + trade[x], 1LL * upper[x]);
		}
	}
	return 0;
} 
