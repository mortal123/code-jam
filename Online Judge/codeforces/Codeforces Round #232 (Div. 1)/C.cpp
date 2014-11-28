#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 333333;

const int MOD = 1000000007;

struct Node {
	long long cons[2], tag[2];
	void clear() {
		for(int i = 0; i < 2; i++)
			cons[i] = tag[i] = 0;
	}
}T[N * 4];

int left[N], right[N];
int n, q, dep[N];
vector<int> sons[N];
int tot = 0;

void dfs(int x) {
	left[x] = ++tot;
	for(int i = 0; i < (int)sons[x].size(); i++) {
		int y = sons[x][i];
		dep[y] = dep[x] + 1;
		dfs(y);
	}
	
	right[x] = tot;
}

void build(int x, int l, int r) {
	T[x].clear();
	if (l == r)
		return;
		
	int mid = (l + r) / 2;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}

void push(int x) {
	int l = x << 1, r = x << 1 | 1;
	for(int i = 0; i < 2; i++) {
		(T[l].tag[i] += T[x].tag[i]) %= MOD;
		(T[l].cons[i] += T[x].tag[i]) %= MOD;
		(T[r].tag[i] += T[x].tag[i]) %= MOD;
		(T[r].cons[i] += T[x].tag[i]) %= MOD;
		
		T[x].tag[i] = 0;
	}
}



void ins(int x, int l, int r, int ql, int qr, int s1, int s2) {
	if (qr < l || ql > r)
		return;
	
	if (ql <= l && r <= qr) {
		(T[x].tag[0] += s1) %= MOD;
		(T[x].cons[0] += s1) %= MOD;
		(T[x].tag[1] += s2) %= MOD;
		(T[x].cons[1] += s2) %= MOD;
		return;
	}
	
	push(x);
	int mid = (l + r) / 2;
	ins(x << 1, l, mid, ql, qr, s1, s2);
	ins(x << 1 | 1, mid + 1, r, ql, qr, s1, s2);
}

int ask(int x, int l, int r, int p, int dp) {
	if (l == r) {
		return ((T[x].cons[0] - 1LL * T[x].cons[1] * dp % MOD) % MOD + MOD) % MOD;
	}
	
	push(x);
	int mid = (l + r) / 2, res;
	if (p <= mid)
		res = ask(x << 1, l, mid, p, dp);
	else
		res = ask(x << 1 | 1, mid + 1, r, p, dp);
	return res;
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		int a;
		scanf("%d", &a);
		sons[a].push_back(i);
	}	
	
	dfs(1);
	build(1, 1, n);
	
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int v, x, k;
			scanf("%d %d %d", &v, &x, &k);
			ins(1, 1, n, left[v], right[v], (1LL * x + 1LL * dep[v] * k) % MOD, k);
		} else {
			int v;
			scanf("%d", &v);
			printf("%d\n", ask(1, 1, n, left[v], dep[v]));
		}
	}
	return 0;
} 
