#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110000;
const int inf = 1100000000;

struct Node {
	int l, r, minID, size, sub, minHp;
	void clear(int ll, int rr) {
		l = ll; r = rr;
		sub = 0;
	}
	inline friend Node operator +(const Node &a, const Node &b) {
		Node c;
		c.clear(a.l, b.r);
		if (a.minHp < b.minHp) {
			c.minID = a.minID;	
			c.minHp = a.minHp;
		} else {
			c.minID = b.minID;
			c.minHp = b.minHp;	
		}
		c.size = a.size + b.size;
		c.sub = 0;
		return c;
	}
	
	void dec(int x) {
		minHp -= x;
		sub += x;
	}
	
	void push(Node &a, Node &b) {
		a.dec(sub);
		b.dec(sub);
		sub = 0;
	}
}T[MAXN * 4];

pair<int, int> sec[MAXN];
vector<int> e[MAXN];
int n, m, health[MAXN];
int posL[MAXN], posR[MAXN], ID[MAXN], cnt = 0;

void dfs(int x) {
	posL[x] = ++cnt;
	ID[cnt] = x;
	for(int i = 0; i < e[x].size(); i++) {
		dfs(e[x][i]);
	}
	posR[x] = cnt;
}

void build(int root, int l, int r) {
	T[root].clear(l, r);
	if (l == r) {
		T[root].size = 1;
		T[root].minHp = health[ID[l]];
		T[root].minID = l;
	} else {
		int mid = (l + r) / 2;
		build(root * 2, l, mid);
		build(root * 2 + 1, mid + 1, r);
		T[root] = T[root * 2] + T[root * 2 + 1];
	}
}

pair<int, int> getID(int root, int l, int r) {
	if (l > r)
		return make_pair(inf, 0);
	if (l <= T[root].l && T[root].r <= r) {
		return make_pair(T[root].minHp, T[root].minID);
	}
	int mid = (T[root].l + T[root].r) / 2;
	T[root].push(T[root * 2], T[root * 2 + 1]);
	pair<int, int> res;
	res.first = inf;
	if (l <= mid)
		res = min(res, getID(root * 2, l, r));
	if (r > mid)
		res = min(res, getID(root * 2 + 1, l, r));
	T[root] = T[root * 2] + T[root * 2 + 1];
	return res;
} 

void insert(int root, int l, int r, int v) {
	if (l > r)
		return;
	if (l <= T[root].l && T[root].r <= r) {
		T[root].dec(v);
		return;
	}
	int mid = (T[root].l + T[root].r) / 2;
	T[root].push(T[root * 2], T[root * 2 + 1]);
	if (l <= mid)
		insert(root * 2, l, r, v);
	if (r > mid)
		insert(root * 2 + 1, l, r, v);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

int ask(int root, int l, int r) {
	if (l > r)
		return 0;
	if (l <= T[root].l && T[root].r <= r)
		return T[root].size;
	int mid = (T[root].l + T[root].r) / 2;
	T[root].push(T[root * 2], T[root * 2 + 1]);
	
	int res = 0;
	if (l <= mid)
		res += ask(root * 2, l, r);
	if (r > mid)
		res += ask(root * 2 + 1, l, r);
	T[root] = T[root * 2] + T[root * 2 + 1];
	return res;
}

void delet(int root, int ps) {
	if (T[root].l == T[root].r) {
		T[root].minHp = inf;
		T[root].size = 0;
		return;
	}
	int mid = (T[root].l + T[root].r) / 2;
	T[root].push(T[root * 2], T[root * 2 + 1]);
	if (ps <= mid)
		delet(root * 2, ps);
	else
		delet(root * 2 + 1, ps);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int sup;
		scanf("%d %d", &health[i], &sup);
		e[sup].push_back(i);
	}	
	dfs(0);
	build(1, 1, n + 1);
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int type, a, x;
		scanf("%d %d", &type, &a);
		if (type == 1) {
			scanf("%d", &x);
			pair<int, int> del;
			while(1) {
				del = getID(1, posL[a] + 1, posR[a]);
				if (del.first > x)
					break;
				delet(1, del.second); 
			}
			insert(1, posL[a] + 1, posR[a], x);
		} else {
			printf("%d\n", ask(1, posL[a] + 1, posR[a]));
		}
	}
	return 0;
} 
