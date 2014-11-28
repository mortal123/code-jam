#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111111;

int n;
int limit;
vector<pair<int, int> > e[N];
int dist[N], from[N];
vector<int> queue;
int down[N];
bool inPath[N];

int go(int source) {
	queue.clear();
	queue.push_back(source);
	from[source] = dist[source] = 0;
	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].first;
			if (y == from[x]) {
				continue;
			}
			dist[y] = dist[x] + e[x][i].second;
			queue.push_back(y);
			from[y] = x;
		}
	}
	int maxDist = -1, who = 0;
	for(int i = 1; i <= n; i++) {
		if (dist[i] > maxDist) {
			maxDist = dist[i];
			who = i;
		}
	}
	return who;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test-- && scanf("%d %d", &n, &limit) == 2) {
		for(int i = 1; i <= n; i++) {
			e[i].clear();
		}
		for(int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			e[a].push_back(make_pair(b, c));
			e[b].push_back(make_pair(a, c));
		}
		int source = go(1);
		int target = go(source);

		vector<int> path;
		fill(inPath + 1, inPath + n + 1, false);
		{
			int x = target;
			while(1) {
				inPath[x] = true;
				path.push_back(x);
				if (x == source) {
					break;
				}
				x = from[x];
			}
		}
		reverse(path.begin(), path.end());
		int length = path.size();
		fill(down + 1, down + n + 1, 0);
		for(int i = n - 1; i >= 0; i--) {
			int x = queue[i];
			if (!inPath[x] && from[x]) {
				down[from[x]] = max(down[from[x]], down[x] + dist[x] - dist[from[x]]);
			}
		}

		int l = 0, r = 1e8;
		while(l < r) {
			int mid = (l + r) / 2;
			bool flag = true;
			int lp = 0, rp = length - 1;
			for(int i = 0; i < length; i++) {
				int x = path[i];
				if (down[x] > mid) {
					flag = false;
				}
				if (dist[x] <= mid) {
					lp = i;
				}
			}
			for(int i = length - 1; i >= 0; i--) {
				int x = path[i];
				if (dist[target] - dist[x] <= mid) {
					rp = i;
				}
			}
			if (rp > lp && dist[path[rp]] - dist[path[lp]] > limit) {
				flag = false;
			}
			//cout << l << " " << r << endl;
			if (flag) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", l);
	}
	return 0;
}
