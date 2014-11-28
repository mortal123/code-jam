#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111, MOD = 1e9 + 7;

int next[N], times;
int n, m;
vector<int> secs[N];

int go(int x) {
	if (next[x] == x)
		return x;
	return next[x] = go(next[x]);
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		secs[r].push_back(l);
	}
	
	for(int i = 1; i <= n + 1; i++) {
		next[i] = i;
	}
	
	times = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < (int)secs[i].size(); j++) {
			int l = secs[i][j];
			l = go(l);
			if (l > i)
				continue;
			else {
				next[l] = i + 1;
				times++;
			}
		}
	}
	
	int ans = 1;
	for(int i = 1; i <= times; i++) {
		ans *= 2;
		ans %= MOD;
	}
	
	printf("%d\n", ans);
	return 0;
} 
