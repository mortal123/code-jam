#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const long long INF = 11111111111LL;

long long tag[N << 2];
pair<long long, int> tree[N << 2];

int father[N];
vector<int> e[N];
int n, w[N];
int pos[N][2], dp[N][2], all = 0, rpos[N], local[N];
int h[N];

void dfs(int x) {
	dp[x][0] = ++all;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father[x])
			continue;
		dfs(y);
	}
	dp[x][1] = all;
}

int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i ^= (i & (-i))) {
		res += h[i];
	}
	return res;
}

__inline void ins(int pos, int v) {
	for(int i = pos; i <= n; i += (i & (-i))) {
		h[i] += v;
	}
}

__inline void update(int x) {
	tree[x] = min(tree[x << 1], tree[x << 1 | 1]);
}

__inline void push(int x) {
	if (tag[x] == 0)
		return ;
	tag[x << 1] += tag[x];
	tree[x << 1].first += tag[x];
	tag[x << 1 | 1] += tag[x];
	tree[x << 1 | 1].first += tag[x];
	tag[x] = 0;
}

void build(int x, int l, int r) {
	tag[x] = 0;
	if (l == r) {
		tree[x] = make_pair(w[rpos[l]], rpos[l]);
		return ;
	}
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	update(x);
}

void modify(int x, int l, int r, int ql, int qr, long long add) {
	if (r < ql || qr < l) 
		return ;
	if (ql <= l && r <= qr) {
		tag[x] += add;;
		tree[x].first += add;
		return ;
	}
	push(x);
	int mid = (l + r) >> 1;
	modify(x << 1, l, mid, ql, qr, add);
	modify(x << 1 | 1, mid + 1, r, ql, qr, add);
	update(x);
}

void spread(int a, int b, int sign) {
	//printf("spread %d %d\n", a, b);
	int l = local[a], r = local[a];
	while(b && l <= r) {
		pair<int, int> tmp;
		modify(1, 1, n, l, r, sign * b);
		b >>= 1;
		l = pos[rpos[l]][0], r = pos[rpos[r]][1];
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	vector<int> q;
	q.push_back(1);
	father[1] = 0;
	rpos[1] = local[1] = 1;
	for(int head = 0, tot = 1; head < (int)q.size(); head++) {
		int x = q[head];
		pos[x][0] = tot + 1;
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (y == father[x])
				continue;
			q.push_back(y);
			father[y] = x;
			rpos[++tot] = y;
			local[y] = tot;
		}
		pos[x][1] = tot;
	}
	dfs(1);
	build(1, 1, n);
	int qnum;
	scanf("%d", &qnum);
	for(; qnum--; ) {
		int type, a ,b;
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d %d", &a, &b);
			int bb = b / 4;
			int aa = a;
			while(bb && father[aa]) {
				spread(aa, bb, 1);
				aa = father[aa];
				bb >>= 1;
			}
			while(a && b) {
				spread(a, b, -1);
				a = father[a];
				b >>= 1;
			}
			while(tree[1].first <= 0) {
				int c = tree[1].second;
				ins(dp[c][0], 1);
				modify(1, 1, n, local[c], local[c], INF);
			}
		} else {
			scanf("%d", &a);
			printf("%d\n", ask(dp[a][1]) - ask(dp[a][0] - 1));
		}
	}
	return 0;
}
