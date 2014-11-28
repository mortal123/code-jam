#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

const int inf = 100000000;

const int MAXN = 1111, MAXM = 11111;

struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], cost[MAXM], sum;
	void clear() {
		sum = 0;
		memset(last, -1, sizeof(last));
	}
	void addEdge(int a, int b, int c) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum++] = c;
	}
}e;

struct Node {
	int ds, x, state;
	Node() {}
	Node(int ds, int x, int state) : ds(ds), x(x), state(state) {}
	friend inline int operator <(const Node &a, const Node &b) {
		return a.ds > b.ds;
	}
};

vector<int> dis[MAXM];
vector<pair<int, int> > pre[MAXM];
vector<bool> visit[MAXM];
int n, m, r, start, target;
vector<int> route[MAXN], edge[MAXM];
int totCost[MAXN], hash[MAXM], slot, oVal[MAXM];
priority_queue<Node> q;
int ansE, ansS;

int spfa(int s) {
	q.push(Node(0, s, 0));
	dis[s][0] = 0; 
	Node tmp;
	while(!q.empty()) {
		tmp = q.top();
		q.pop();
		int x = e.other[tmp.x], state = tmp.state;
		int en = tmp.x;
		if (visit[en][state])
			continue;
		visit[en][state] = true;
		if (x == target) {
			ansE = en, ansS = state;
			return dis[en][state];
		}
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			int cost = e.cost[i];
			++slot;
			for(int j = 0; j < edge[en].size(); j++) {
				if ((1 << j) & state)
					hash[edge[en][j]] = slot;
			}
			int newState = 0;
			for(int j = 0; j < edge[i].size(); j++) {
				if (route[edge[i][j]].front() == i) {
					newState |= (1 << j);
				} else if (hash[edge[i][j]] == slot) {
					if (route[edge[i][j]].back() == i) {
						cost += totCost[edge[i][j]];
					} else 
						newState |= (1 << j);
				}
			}
			if (dis[en][state] + cost < dis[i][newState]) {
				dis[i][newState] = dis[en][state] + cost;
				pre[i][newState] = make_pair(en, state);
				q.push(Node(dis[en][state] + cost, i, newState));
			}
		}
	}
	return -1;
}

int cnt;

void print(int a, int b, int flag) {
	if (a == m)
		return;
	print(pre[a][b].first, pre[a][b].second, flag);
	if (flag) 
		printf("%d ", a + 1);
	cnt++;
}

int main() {
	freopen("input.txt", "r", stdin);
	e.clear();
	scanf("%d %d %d %d %d", &n, &m, &r, &start, &target);
	start--;
	target--;
	for(int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--; b--;
		e.addEdge(a, b, c);
		oVal[i] = c;
	}
	for(int i = 0; i < r; i++) {
		int tot;
		scanf("%d", &tot);
		if (tot == 1) {
			scanf("%d", &tot);
			e.cost[tot - 1] += oVal[tot - 1];
			continue;
		}
		for(int j = 0; j < tot; j++) {
			int k;
			scanf("%d", &k);
			totCost[i] += oVal[k - 1];
			route[i].push_back(k - 1);
			edge[k - 1].push_back(i);	
		}
	}
	e.addEdge(n, start, 0);
	edge[m].push_back(1);
	for(int i = 0; i <= m; i++) {
		dis[i].resize(1 << edge[i].size(), inf);
		visit[i].resize(1 << edge[i].size(), false);
		pre[i].resize(1 << edge[i].size());
	}
	int ans = spfa(m);
	printf("%d\n", ans);
	if (ans == -1)
		return 0;
	cnt = 0;
	print(ansE, ansS, 0);
	printf("%d\n", cnt);
	print(ansE, ansS, 1);
	return 0;
}
