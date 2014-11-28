#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 1e5 + 10;
const int INF = 1111111111;

typedef pair<int, int> PII;

vector<pair<int, int> > e[N];
int market[N], visit[N], del[N];
PII minDist[N];
int n, answer[N], father[N], size[N];

vector<PII> dists;
vector<int> q;

int find(int r) {
	q.clear();
	q.push_back(r);
	father[r] = 0;
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (del[y] || y == father[x]) {
				continue;
			}
			father[y] = x;
			q.push_back(y);
		}
	}
	int total = (int)q.size(), minVal = INF, choose = -1;
	for(int i = total - 1; i >= 0; i--) {
		int x = q[i], cur = 0;
		size[x] = 1;
		for(int j = 0; j < (int)e[x].size(); j++) {
			int y = e[x][j].first;
			if (del[y] || y == father[x]) {
				continue;
			}
			size[x] += size[y];
			cur = max(cur, size[y]);
		}
		cur = max(cur, total - size[x]);
		if (cur < minVal) {
			minVal = cur;
			choose = x;
		}
	}
	return choose;
}
	
void solve(int r, int delta, int opt) {
	q.clear();
	dists.clear();
	
	static int ds[N];
	q.push_back(r);
	dists.push_back(make_pair(minDist[r].first - delta, minDist[r].second));
	father[r] = 0;
	ds[r] = 0;
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (del[y] || y == father[x]) {
				continue;
			}
			father[y] = x;
			q.push_back(y);
			ds[y] = ds[x] + e[x][i].second;
			dists.push_back(make_pair(minDist[y].first - ds[y] - delta, minDist[y].second));
		}
	}
	sort(dists.begin(), dists.end());
	for(int i = 0; i < (int)q.size(); i++) {
		int x = q[i];
		int numbers = dists.end() - upper_bound(dists.begin(), dists.end(), make_pair(ds[x], x));
		answer[x] += opt * numbers;
	}
}

void divide(int r) {
	r = find(r);
	solve(r, 0, 1);
	del[r] = 1;
	for(int i = 0; i < (int)e[r].size(); i++) {
		int y = e[r][i].first;
		if (!del[y]) {
			solve(y, 2 * e[r][i].second, -1);
		}
	}
	for(int i = 0; i < (int)e[r].size(); i++) {
		int y = e[r][i].first;
		if (!del[y]) {
			divide(y);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			e[a].push_back(make_pair(b, w));
			e[b].push_back(make_pair(a, w));
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &market[i]);
		}
		
		fill(visit + 1, visit + n + 1, 0);
		priority_queue<pair<PII, int>, vector<pair<PII, int> >, greater<pair<PII, int> > > q;
		for(int i = 1; i <= n; i++) {
			if (market[i]) {
				minDist[i] = make_pair(0, i);
				q.push(make_pair(minDist[i], i));
			} else {
				minDist[i] = make_pair(INF, 0);
			}
		}
		while(!q.empty()) {
			pair<PII, int> temp = q.top();
			q.pop();
			int x = temp.second;
			if (visit[x]) {
				continue;
			}
			visit[x] = 1;
			for(int i = 0; i < (int)e[x].size(); i++) {
				int y = e[x][i].first;
				PII value = minDist[x];
				value.first += e[x][i].second;
				if (value < minDist[y]) {
					minDist[y] = value;
					q.push(make_pair(value, y));
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			answer[i] = 0;
			del[i] = 0;
		}
		divide(1);
		int result = 0;
		for(int i = 1; i <= n; i++) {
			result = max(result, answer[i]);
		}
		printf("%d\n", result);
		/*for(int i = 1; i <= n; i++) {
			printf("%d %d\n", minDist[i].first, minDist[i].second);
		}*/
	}
} 
