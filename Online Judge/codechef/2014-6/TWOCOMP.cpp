#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 111111, LOG = 18, M = 2222222; 
const int INF = 111111111;

int father[N][LOG], dep[N], dis[N];
int n, m1, m2, source, target;
vector<int> edge[N];

struct eglist
{
	int other[M + 10], succ[M + 10], last[M + 10], cap[M + 10], sum;
	void clear() {
		memset(last, 0, sizeof(last));
		sum = 1;
	} 
	void addEdge(int a, int b, int c) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum, cap[sum] = c;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum, cap[sum] = 0;
	}
}e;

void bfs(int source) {
	vector<int> queue;
	queue.push_back(source);
	father[source][0] = 0;
	dep[source] = 0;
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int i = 0; i < (int)edge[x].size(); i++) {
			int y = edge[x][i];
			if (y == father[x][0]) {
				continue;
			}
			queue.push_back(y);
			dep[y] = dep[x] + 1;
			father[y][0] = x;
		}
	}
	for(int i = 1; i < LOG; i++)
		for(int j = 1; j <= n; j++) {
			father[j][i] = father[father[j][i - 1]][i - 1];
		}
}

int getLCA(int a, int b) {
	if (dep[a] < dep[b]) {
		swap(a, b);
	}
	for(int i = LOG - 1; i >= 0; i--) {
		if (dep[a] - (1 << i) >= dep[b])
			a = father[a][i];
	}
	if (a == b)
		return a;
	for(int i = LOG - 1; i >= 0; i--) {
		if (father[a][i] != father[b][i]) {
			a = father[a][i];
			b = father[b][i];
		}
	}
	return father[a][0];
}

int jump(int a, int b) {
	for(int i = LOG - 1; i >= 0; i--) {
		if (b >> i & 1) {
			a = father[a][i];
		}
	}
	return a;
}

inline bool isUpper(int a, int b) {
	if (dep[a] > dep[b])
		return 0;
	return jump(b, dep[b] - dep[a]) == a;
}

int onLine(int a, int b, int c, int d) {
	if (!isUpper(d, a))
		return 0;
	if (isUpper(a, b) || isUpper(a, c))
		return 1;
	return 0;
}

int bfs() {
	static int visit[N], q[N];
	for(int i = 1; i <= target; i++) {
		visit[i] = 0;
	}
	int head = 0, tail = 0;
	q[++tail] = target;
	visit[target] = 1;
	dis[target] = 0;
	while(head < tail && !visit[source]) {
		int x = q[++head];
		for(int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (e.cap[i ^ 1] && !visit[y]) {
				dis[y] = dis[x] + 1;
				visit[y] = 1;
				q[++tail] = y;
			}
		}
	}
	return visit[source];
}

int dinic(int x, int flow) {
	if (x == target) {
		return flow;
	}
	int delta = flow;
	for(int i = e.last[x]; i && delta; i = e.succ[i]) {
		int y = e.other[i];
		if (dis[y] + 1 == dis[x] && e.cap[i]) {
			int tmp = dinic(y, min(delta, e.cap[i]));
			e.cap[i] -= tmp;
			e.cap[i ^ 1] += tmp;
			delta -= tmp;
		}
	}
	return flow - delta;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &n, &m1, &m2);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	source = m1 + m2 + 1;
	target = m1 + m2 + 2;
	bfs(1);
	e.clear();
	vector<pair<int, int> > paths;
	int ans = 0;
	for(int i = 1; i <= m1; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		paths.push_back(make_pair(a, b));
		e.addEdge(source, i, c);
		ans += c;
	}
	for(int i = 1; i <= m2; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		for(int j = 0; j < m1; j++) {
			int c = paths[j].first, d = paths[j].second;
			int lab = getLCA(a, b), lcd = getLCA(c, d);
			if (onLine(lab, c, d, lcd) || onLine(lcd, a, b, lab)) {
				e.addEdge(j + 1, i + m1, INF);
			}
		}
		e.addEdge(i + m1, target, c);
		ans += c;
	}
	while(bfs()) {
		ans -= dinic(source, INF);
	}
	printf("%d\n", ans);
	return 0;
}
