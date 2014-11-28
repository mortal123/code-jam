#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 222222, M = N * 2;
const int inf = 500000000;
const int BLACK = 0, WHITE = 1; 
typedef pair<int, int> PII;

priority_queue<pair<PII, int> > heap[N];
int down[N];
int n, tag[N], top[N], floor[N], pos[N], rpos[N], color[N];
int que[N], fa[N], size[N], son[N], dep[N];
PII g[N];

struct Node {
	int l, r;
	PII opt, maxL;
	inline friend Node operator +(const Node &a, const Node &b) {
		Node c;
		c.l = a.l;
		c.r = b.r;
		c.opt = max(a.opt, b.opt);
		c.maxL = max(a.maxL, b.maxL);
		return c;
	}
}T[N * 4];

Node EMPTY;
PII init[N];

struct eglist {
	int other[M], succ[M], last[M], sum;
	void clear(int n) {
		sum = 0;
		fill(last + 1, last + n + 1, -1);
	}
	void addEdge(int a, int b) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum++;
		other[sum] = a, succ[sum] = last[b], last[b] = sum++;
	}
}e;

void build(int root, int l, int r) {
	T[root].l = l;
	T[root].r = r;
	T[root].maxL = T[root].opt = init[rpos[l]];
	T[root].opt.first -= 2 * dep[rpos[l]];
	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(root * 2, l, mid);
	build(root * 2 + 1, mid + 1, r);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

void modify(int root, int pos, PII v) {
	if (T[root].l == T[root].r) {
		T[root].opt = T[root].maxL = v;
		T[root].opt.first -= 2 * dep[rpos[pos]];
		return ;
	}
	int mid = (T[root].l + T[root].r) / 2;
	if (pos <= mid)
		modify(root * 2, pos, v);
	else
		modify(root * 2 + 1, pos, v);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

Node ask(int root, int l, int r) {
	if (l > r) {
		return EMPTY;
	}
	if (l <= T[root].l && T[root].r <= r) 
		return T[root];
	int mid = (T[root].l + T[root].r) / 2;
	if (l <= mid && r > mid)
		return ask(root * 2, l, r) + ask(root * 2 + 1, l, r);
	if (l <= mid)
		return ask(root * 2, l, r);
	else
		return ask(root * 2 + 1, l, r);
}

int FROM;

PII getV(int x, priority_queue<pair<PII, int> > &s, int del = -1) {
	PII self = make_pair(-inf, 0);
	if (color[x] == WHITE)
		self.first = dep[x], self.second = x;
	while(!s.empty()) {
		pair<PII, int> it = s.top();
		if (it.second == x && it.first != self || 
			it.second != x && it.first != g[it.second] || 
			it.second == del )
			s.pop();
		else
			break;
	}
	if (s.size()) {
		FROM = s.top().second;
		return s.top().first;
	}
	FROM = -1;
	return make_pair(-inf, 0);
}

void buildTree() {
	int head = 1, tail = 1;
	que[tail] = 1;
	fa[1] = 0;
	dep[1] = 0;
	for(; head <= tail; ++head) {
		int x = que[head];
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == fa[x])
				continue;
			fa[y] = x;
			dep[y] = dep[x] + 1;
			que[++tail] = y;
		}
	}
	fill(size + 1, size + n + 1, 0);
	for(int i = n; i >= 1; i--) {
		int x = que[i];
		size[x]++;
		size[fa[x]] += size[x];
		son[x] = -1;
		int mm = -1;
		for(int j = e.last[x]; ~j; j = e.succ[j]) {
			int y = e.other[j];
			if (y == fa[x])
				continue;
			if (size[y] > mm) {
				mm = size[y];
				son[x] = y;
			}
		}
	}
	int tot = 0;
	fill(tag + 1, tag + n + 1, -1);
	tag[0] = 0;
	for(int i = 1; i <= n; i++) {
		int x = que[i];
		if (tag[x] == -1) {
			tag[x] = tag[fa[x]] + 1;
			int temp = x, last;
			while(temp != -1) {
				top[temp] = x;
				pos[temp] = ++tot;
				rpos[tot] = temp;
				tag[temp] = tag[x];
				last = temp;
				temp = son[temp];
			}
			temp = x;
			while(temp != -1) {
				floor[temp] = last;
				temp = son[temp];
			}
		}
	}
	for(int i = n; i >= 1; i--) {
		int x = que[i];
		heap[x].push(make_pair(make_pair(dep[x], x), x));
		init[x] = getV(x, heap[x]);
		if (top[x] == x) {
			g[x] = init[x];
			int tx = son[x];
			while(tx != -1) {
				g[x] = max(g[x], init[tx]);
				tx = son[tx];
			}
			heap[fa[x]].push(make_pair(g[x], x));
		}
	}
	/*
	for(int i = 1; i <= n; i++) {
		printf("top = %d  floor = %d  tag = %d  pos = %d\n", top[i], floor[i], tag[i], pos[i]);
	}
	*/
	build(1, 1, tot);
}


int doit(int x) {
	color[x] ^= 1;
	int s = 0;
	PII res = make_pair(-dep[x], x);
	
	
	if (color[x] == WHITE) {
		heap[x].push(make_pair(make_pair(dep[x], x), x));
	}
	
	while(x) {
		modify(1, pos[x], getV(x, heap[x]));
		PII firstV = getV(x, heap[x]);
		if (FROM != s) {
			res = max(res, make_pair(firstV.first - 2 * dep[x], firstV.second));
		} else {
			int FROMbak = FROM;
			if (!heap[x].empty())
				heap[x].pop();
			PII secondV = getV(x, heap[x], FROMbak);
			res = max(res, make_pair(secondV.first - 2 * dep[x], secondV.second));
			heap[x].push(make_pair(firstV, FROMbak));
		}
		
		Node down = ask(1, pos[x] + 1, pos[floor[x]]);
		res = max(res, make_pair(down.maxL.first - 2 * dep[x], down.maxL.second));
		
		s = top[x];
		Node up = ask(1, pos[s], pos[x] - 1);
		//PII see = getV(x, heap[x]);
		
		res = max(res, up.opt);
		g[s] = max(getV(x, heap[x]), max(down.maxL, up.maxL));
		
		x = fa[s];
		if (x) {
			heap[x].push(make_pair(g[s], s));
		}
	}
	return res.second;
}

int Main() {
	int q;
	scanf("%d %d", &n, &q);
	
	e.clear(n);
	for(int i = 1; i <= n; i++)
		while(!heap[i].empty()) {
			heap[i].pop();
		}
	for(int i = 2; i <= n; i++) {
		int parant;
		scanf("%d", &parant);
		e.addEdge(parant, i);
	}
	for(int i = 1; i <= n; i++) {
		g[i] = make_pair(-inf, -1);
		color[i] = WHITE;
	}
	buildTree();
	for(; q--; ) {
		int x;
		scanf("%d", &x);
		printf("%d\n", doit(x));
		//doit(x);
	}
	return 0;
}

int main() {
	EMPTY.opt = EMPTY.maxL = make_pair(-inf, 0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		Main();
	}
	return 0;
}
