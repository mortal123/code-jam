#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <iostream>
using namespace std;

const int N = 111111;

vector<pair<int, long long> > e[N];
int n, m;
long long ans = 0;
long long mark[N], tt;
int dep[N];

map<long long, int> cnt;

long long dfs(int x) {
	long long res = 0;
	
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i].first;
		if (dep[y] == 0) {
			dep[y] = dep[x] + 1;
			tt = dfs(y);
			cnt[tt]++;
			res ^= tt;
		} else if (dep[y] < dep[x] - 1) {
			res ^= e[x][i].second;
			mark[y] ^= e[x][i].second;
			cnt[e[x][i].second]++;
		}
	}
	
	res ^= mark[x];
	return res;
}

int main() {
	srand(time(0));
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		long long tmp = 1LL * rand() * rand();
		e[a].push_back(make_pair(b, tmp));
		e[b].push_back(make_pair(a, tmp));
	}	
	
	dep[1] = 1;
	dfs(1);
	
	for(int i = 1; i <= n; i++) {
		if (dep[i] == 0) {
			while(1);
		}
	}
	
	for(map<long long, int> :: iterator it = cnt.begin(); it != cnt.end(); ++it) {
		if (it->first == 0) {
			ans += 1LL * (m - it->second) * it->second;
		}
		ans += 1LL * (it->second - 1) * it->second / 2;
		//printf("%d %d\n", it->first, it->second);
	}
	
	cout << ans << endl;
	return 0;
}
