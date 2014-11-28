#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;

int n, m;
vector<int> e[N];
int mark[N];
int visit[N];
int total, down[N];

long long ans1, ans2;

int cntMark(int x, int father) {
	visit[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		if (e[x][i] != father)
			down[x] += cntMark(e[x][i], x);
	}
	
	return down[x] += mark[x];
}

int solve(int x, int father) {
	int ret = 0;
	for(int i = 0; i < (int)e[x].size(); i++) {
		if (e[x][i] == father)
			continue;
		ret += solve(e[x][i], x);
	}
	
	if (ret > 1 || total - down[x] + mark[x] && ret || mark[x] && total > 1)
		ans2++;
	
	return !!down[x];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &mark[i]);
	}
	
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	for(int i = 1; i <= n; i++) {
		if (visit[i])
			continue;
		
		total = cntMark(i, 0);
		ans1 += 1LL * total * (total - 1) / 2;
		solve(i, 0);
	}
	
	printf("%lld %d\n", ans1, ans2);
	return 0;
}
