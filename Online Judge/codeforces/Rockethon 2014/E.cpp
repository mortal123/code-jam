#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const long long INF = (1LL << 60);

long long ans = 0, base = 0;

struct Tree {
	vector<int> e[N];
	int n, dep[N], size[N];
	long long f[N];
	long long result;
	pair<long long, int> vl[N][2], vr[N][2];
	int ssl, ssr;
	
	void dfs(int x, int father) {
		size[x] = 1;
		f[1] += dep[x];
		
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (y == father)
				continue;
			dep[y] = dep[x] + 1;
			dfs(y, x);
			size[x] += size[y];
		}
	}
	
	void travel(int x, int father, long long fv) {
		f[x] = fv;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (y == father)
				continue;
			travel(y, x, fv - size[y] + (n - size[y]));
		}
	}
	
	void init(int nn) {
		n = nn;
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		
		fill(f + 1, f + n + 1, 0);
		
		dep[1] = 0;
		dfs(1, 0);
		travel(1, 0, f[1]);
		
		for(int i = 1; i <= n; i++)
			base += f[i];
	}
	
	void go(int x, int father) {
		
		vl[x][0].first = 1LL * dep[x] * ssl * ssr + 1LL * f[x] * ssl;
		vl[x][0].second = -1;
		vr[x][0].first = 1LL * dep[x] * ssl * ssr + 1LL * f[x] * ssr;
		vr[x][0].second = -2;
		
		vl[x][1].first = vr[x][1].first = -INF;
		
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (y == father)
				continue;
			go(y, x);
			if (vl[y][0].first > vl[x][0].first) {
				vl[x][1] = vl[x][0];
				vl[x][0].first = vl[y][0].first;
				vl[x][0].second = y;
			} else if (vl[y][0].first > vl[x][1].first) {
				vl[x][1].first = vl[y][0].first;
				vl[x][1].second = y;
			}
			
			if (vr[y][0].first > vr[x][0].first) {
				vr[x][1] = vr[x][0];
				vr[x][0].first = vr[y][0].first;
				vr[x][0].second = y;
			} else if (vr[y][0].first > vr[x][1].first) {
				vr[x][1].first = vr[y][0].first;
				vr[x][1].second = y;
			}
		}
		
		if (vl[x][0].second != vr[x][0].second) {
			result = max(result, vl[x][0].first + vr[x][0].first - 2LL * dep[x] * ssl * ssr);
		} else {
			result = max(result, vl[x][0].first + vr[x][1].first - 2LL * dep[x] * ssl * ssr);
			result = max(result, vl[x][1].first + vr[x][0].first - 2LL * dep[x] * ssl * ssr);
		}
	}
	
	long long finalCalc(int sl, int sr) {
		ssl = sl, ssr = sr;
		result = 0;
		go(1, 0);
		return result;
	}
	
}trees[3];

void solve(Tree &tl, Tree &mid, Tree &tr) {
	long long res = 0;
	
	long long maxV = 0;
	for(int i = 1; i <= tl.n; i++) {
		maxV = max(maxV, tl.f[i] + tl.n);	
	}
	res += 1LL * maxV * (mid.n + tr.n);
	
	maxV = 0;
	for(int i = 1; i <= tr.n; i++) {
		maxV = max(maxV, tr.f[i] + tr.n);
	}
	
	res += 1LL * maxV * (mid.n + tl.n);
	
	res += mid.finalCalc(tl.n, tr.n);
	ans = max(ans, res + base / 2);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n1, n2, n3;
	scanf("%d %d %d", &n1, &n2, &n3);
	trees[0].init(n1);
	trees[1].init(n2);
	trees[2].init(n3);
	
	solve(trees[0], trees[1], trees[2]);
	solve(trees[1], trees[0], trees[2]);
	solve(trees[0], trees[2], trees[1]);
	
	printf("%I64d\n", ans);
	return 0;
} 
