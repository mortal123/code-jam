#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 110000, MAXM = 2 * MAXN;
const int inf = 1100000000;

struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], sum, cost[MAXM];
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void addEdge(int a, int b, int c) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum++] = c;
		other[sum] = a, succ[sum] = last[b], last[b] = sum, cost[sum++] = c;
	}
}e;

int n, m;
int ss[MAXN], k, dis[MAXN];
vector<int> ans;

priority_queue<pair<int, int> > q;

int spfa(int s) {
	static int visit[MAXN];
	for(int i = 1; i <= n; i++)
		dis[i] = inf, visit[i] = 0;
	dis[s] = 0;
	q.push(make_pair(0, s));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if (visit[x])
			continue;
		visit[x] = 1;
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (dis[x] + e.cost[i] < dis[y]) {
				dis[y] = dis[x] + e.cost[i];
				q.push(make_pair(-dis[y], y));
			}
		}
	}
	int farest = -1;
	for(int i = 1; i <= k; i++) {
		if (farest == -1 || dis[ss[i]] > dis[farest])
			farest = ss[i];
	}
	return farest;
}

int pre[MAXN], pree[MAXN];

int bfs(int s, int t) {
	queue<int > q;
	q.push(s);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (pre[y] == 0 && dis[y] == dis[x] + e.cost[i] && dis[y] <= dis[t]) {
				pre[y] = x;
				pree[y] = i;
				q.push(y);
			}
		}
	}
	vector<int> tmp;
	while(t != s) {
		tmp.push_back(pree[t] / 2);
		t = pre[t];
	}
	reverse(tmp.begin(), tmp.end());
	for(int i = 0; i < tmp.size(); i++)
		ans.push_back(tmp[i]);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	e.clear();
	for(int i = 1; i <= m; i++) {
		int a, b, t;
		scanf("%d %d %d", &a, &b, &t);
		e.addEdge(a, b, t);
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++) {
		scanf("%d", &ss[i]);
	}
	if (k <= 1) {
		printf("0\n");
		return 0;
	}
	int s = spfa(ss[1]);
	spfa(s);
	//cout << s << endl;
	vector<pair<int, int> > vec;
	for(int i = 1; i <= k; i++) {
		vec.push_back(make_pair(dis[ss[i]], ss[i]));
	}
	sort(vec.begin(), vec.end());
	for(int i = 1; i < vec.size(); i++)
		bfs(vec[i - 1].second, vec[i].second);
	printf("%d\n", ans.size());
	for(int i = 0; i < ans.size(); i++)
		printf("%d ", ans[i] + 1);
	return 0;
}
