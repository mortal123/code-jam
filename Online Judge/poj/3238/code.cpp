#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int MOD = 19880830;
const int N = 111111;
const int INF = 1000000005;

struct Value {
	int dist, ways;
	Value(int dist = 0, int ways = 0) : dist(dist), ways(ways) {}
	void add(const Value &o) {
		if (o.dist < dist) {
			dist = o.dist;
			ways = o.ways;
		} else if (o.dist == dist) {
			if ((ways += o.ways) >= MOD)
				ways -= MOD;
		}
	}
};

int base;
int n, m, source, target, qNumber;
vector<pair<int, int> > e[N];
priority_queue<pair<int, int> > q;
Value fromT[N], fromS[N], fromO[N];
int father[N], dep[N];
vector<int> path, po[N];
bool visit[N];
int ans[N][2];
map<int, int> cnt;
Value cur[N];


int getAns(int base) {
	int cyc = 1, result = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 2; j++) {
			result += 1LL * cyc * ans[i][j] % MOD;
			result %= MOD;
			cyc = 1LL * cyc * base % MOD;
		}
	return result;
}

void bfs(int s, vector<int> &points, int rdep) {
	points.clear();
	points.push_back(s);
	visit[s] = true;
	for(int head = 0; head < (int)points.size(); head++) {
		int x = points[head];
		dep[x] = rdep;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (!visit[y] && fromT[x].dist + e[x][i].second == fromT[y].dist) {
				points.push_back(y);
				visit[y] = true;
			}
		}
	}
}

void calcMinDist(int s, Value from[]) {
	for(; !q.empty(); q.pop());
	for(int i = 1; i <= n; i++) {
		from[i] = Value(INF, 0);
		visit[i] = false;
	}
	father[s] = 0;
	from[s] = Value(0, 1);
	q.push(make_pair(0, s));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if (visit[x]) {
			continue;
		}
		visit[x] = true;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (from[x].dist + e[x][i].second < from[y].dist) {
				from[y].dist = from[x].dist + e[x][i].second;
				from[y].ways = from[x].ways;
				q.push(make_pair(-from[y].dist, y));
				father[y] = x;
			} else if (from[x].dist + e[x][i].second == from[y].dist) {
				if ((from[y].ways += from[x].ways) >= MOD) {
					from[y].ways -= MOD;
				}
			}
		}
	}
}

void buildTree() {
	calcMinDist(target, fromT);
	path.clear();
	if (fromT[source].dist == INF) {
		return;
	}
	
	for(int i = 1; i <= n; i++) {
		visit[i] = false;
	}
	int x = source;
	while(x) {
		path.push_back(x);
		x = father[x];
	}	
	reverse(path.begin(), path.end());
	for(int i = (int)path.size() - 1; i >= 0; i--) {
		bfs(path[i], po[i], i);
	}
}

void calcODist(int d) {
	for(; !q.empty(); q.pop());
	for(int i = 1; i < (int)po[d].size(); i++) {
		int x = po[d][i];
		visit[x] = false;
		for(int j = 0; j < (int)e[x].size(); j++) {
			int y = e[x][j].first;
			if (dep[y] < d) {
				fromO[x].add(Value(fromT[y].dist + e[x][j].second, fromT[y].ways));
			}
		}
		if (fromO[x].dist != INF) {
			q.push(make_pair(-fromO[x].dist, x));
		}
	}
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if (visit[x])
			continue;
		visit[x] = 1;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (dep[y] != dep[x] || y == po[d][0])
				continue;
			if (fromO[x].dist + e[x][i].second < fromO[y].dist) {
				fromO[y].dist = fromO[x].dist + e[x][i].second;
				fromO[y].ways = fromO[x].ways;
				q.push(make_pair(-fromO[y].dist, y));
			} else if (fromO[x].dist + e[x][i].second == fromO[y].dist) {
				if ((fromO[y].ways += fromO[x].ways) >= MOD) {
					fromO[y].ways -= MOD;
				} 
			}
		}
	}
}

inline void del(int x) {
	(cnt[cur[x].dist] += MOD - cur[x].ways) %= MOD;
}

inline void push(int x) {
	(cnt[cur[x].dist] += cur[x].ways) %= MOD;
}

inline void fresh(int x, const Value &tmp) {
	if (tmp.dist <= cur[x].dist) {
		del(x);
		if (cur[x].dist > tmp.dist) {
			cur[x] = tmp;
		} else {
			(cur[x].ways += tmp.ways) %= MOD;
		}
		push(x);
	}
}

void solve() {
	for(int i = 1; i <= n; i++) {
		ans[i][0] = ans[i][1] = 0;
	}
	buildTree();
	if (fromT[source].dist == INF)
		return ;
	calcMinDist(source, fromS);
	for(int i = 1; i <= n; i++) {
		ans[i][0] = fromS[target].dist;
		ans[i][1] = fromS[target].ways;
		if (fromS[i].dist + fromT[i].dist == fromS[target].dist) {
			ans[i][1] += MOD - 1LL * fromS[i].ways * fromT[i].ways  % MOD;
			ans[i][1] %= MOD;
		}
		fromO[i] = Value(INF, 0);
	}
	for(int i = 0; i < (int)path.size(); i++) {
		ans[path[i]][0] = ans[path[i]][1] = 0;
	}
	for(int i = 0; i < (int)path.size(); i++) {
		int x = path[i];
		calcODist(i);
	}
	
	cnt.clear();
	for(int i = 1; i <= n; i++) {
		if (dep[i] > 0) {
			cur[i] = Value(INF, 0);
			push(i);
		}
	}
	for(int i = 1; i < (int)path.size(); i++) {
		// remove 
		for(int j = 0; j < (int)po[i].size(); j++) {
			int x = po[i][j];
			del(x);
		}
		// fresh1
		for(int j = 1; j < (int)po[i].size(); j++) {
			int x = po[i][j];
			for(int k = 0; k < (int)e[x].size(); k++) {
				int y = e[x][k].first;
				if (dep[y] > i) {
					fresh(y, Value(fromO[x].dist + e[x][k].second + fromS[y].dist, 
									1LL * fromO[x].ways * fromS[y].ways % MOD));
				}
			}
		}
		// fresh2
		for(int j = 0; j < (int)po[i - 1].size(); j++) {
			int x = po[i - 1][j];
			for(int k = 0; k < (int)e[x].size(); k++) {
				int y = e[x][k].first;
				if (dep[y] > i) {
					if (fromO[x].dist == fromT[x].dist) {
						fresh(y, Value(fromT[x].dist + e[x][k].second + fromS[y].dist,
										1LL * (MOD + fromT[x].ways - fromO[x].ways) % MOD * fromS[y].ways % MOD));
					} else {
						fresh(y, Value(fromT[x].dist + e[x][k].second + fromS[y].dist,
										1LL * fromT[x].ways * fromS[y].ways % MOD));
					}
				}
			}
		}
		while(cnt.begin() != cnt.end() && cnt.begin()->second == 0) {
			cnt.erase(cnt.begin());
		}
		if (cnt.begin() != cnt.end()) {
			ans[path[i]][0] = cnt.begin()->first;
			ans[path[i]][1] = cnt.begin()->second;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(scanf("%d %d %d %d %d", &n, &m, &source, &target, &qNumber) == 5) {
		if (n == 0 && m == 0 && source == 0 && target == 0 && qNumber == 0)
			break;
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		for(int i = 1; i <= m; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			e[a].push_back(make_pair(b, c));
			e[b].push_back(make_pair(a, c));
		}
		static int testCount = 0;
		printf("Case %d: ", ++testCount);
		solve();
		/*for(int i = 1; i <= n; i++) {
			printf("%d %d\n", ans[i][0], ans[i][1]);
		}
		for(int i =0; i < (int)path.size(); i++) {
			printf("%d\n", path[i]);
		}*/
		for(int i = 1; i <= qNumber; i++) {
			scanf("%d", &base);
			printf("%d%c", getAns(base), i == qNumber ? '\n' : ' ');
		}
		puts("");
	}
	return 0;
}

