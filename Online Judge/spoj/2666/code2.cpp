#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 111111, M = N * 2;
const int inf = 500000000;
const int BLACK = 0, WHITE = 1; 
typedef pair<int, int> PII;

priority_queue<PII> heap[N];
int down[N];
int n, tag[N], top[N], floor[N], pos[N], f[N], g[N], rpos[N], fv[N], color[N];
int que[N], fa[N], size[N], son[N];
priority_queue<PII> ansQ;


struct Node {
	int l, r, maxL, maxR, opt, length;
	inline friend Node operator +(const Node &a, const Node &b) {
		Node c;
		c.l = a.l;
		c.r = b.r;
		c.maxL = max(a.maxL, a.length + fv[rpos[b.l]] + b.maxL);
		c.maxR = max(b.maxR, b.length + fv[rpos[b.l]] + a.maxR);
		c.opt = max(max(a.opt, b.opt), a.maxR + fv[rpos[b.l]] + b.maxL);
		c.length = a.length + fv[rpos[b.l]] + b.length;
		return c;
	}
	void set(int v1, int v2) {
		maxL = maxR = v1;
		opt = v1 + v2;
		if (color[rpos[l]] == WHITE) {
			opt = max(v1, opt);
		} 
	}
}T[N * 4];

struct eglist {
	int other[M], succ[M], last[M], sum, length[M];
	void clear() {
		sum = 0;
		memset(last, -1, sizeof(last));
	}
	void addEdge(int a, int b, int c) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum, length[sum++] = c;
		other[sum] = a, succ[sum] = last[b], last[b] = sum, length[sum++] = c;
	}
}e;

void build(int root, int l, int r) {
	T[root].l = l;
	T[root].r = r;
	T[root].maxL = T[root].maxR = T[root].opt = -inf;
	T[root].length = 0;
	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(root * 2, l, mid);
	build(root * 2 + 1, mid + 1, r);
	T[root].length = T[root * 2].length + T[root * 2 + 1].length + fv[rpos[mid + 1]];
}

void modify(int root, int pos, int v1, int v2) {
	if (T[root].l == T[root].r) {
		T[root].set(v1, v2);
		return ;
	}
	int mid = (T[root].l + T[root].r) / 2;
	if (pos <= mid)
		modify(root * 2, pos, v1, v2);
	else
		modify(root * 2 + 1, pos, v1, v2);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

Node ask(int root, int l, int r) {
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

void buildTree() {
	int head = 1, tail = 1;
	que[tail] = 1;
	fa[1] = 0;
	for(; head <= tail; ++head) {
		int x = que[head];
		for(int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == fa[x])
				continue;
			fa[y] = x;
			fv[y] = e.length[i];
			que[++tail] = y;
		}
	}
	memset(size, 0, sizeof(size));
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
	memset(tag, -1, sizeof(tag));
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
	/*
	for(int i = 1; i <= n; i++) {
		printf("top = %d  floor = %d  tag = %d  pos = %d\n", top[i], floor[i], tag[i], pos[i]);
	}
	*/
	build(1, 1, tot);
}

int getAns() {
	while(!ansQ.empty()) {
		int x = ansQ.top().second;
		if (f[x] != ansQ.top().first)
			ansQ.pop();
		else
			break;
	}
	return ansQ.top().first;
}

PII getV(int x, priority_queue<PII> &s, int expect = -1) {
	int self = -inf;
	if (color[x] == WHITE)
		self = 0;
	while(!s.empty()) {
		PII it = s.top();
		if (it.second == x && it.first != self || 
			it.second != x && it.first != g[it.second] + fv[it.second] || 
			it.second == expect )
			s.pop();
		else
			break;
	}
	if (s.size())
		return s.top();
	return make_pair(-inf, 0);
}

void pop(priority_queue<PII> &s) {
	if (!s.empty())
		s.pop();
}

void doit(int x) {
	color[x] ^= 1;
	int s = 0;
	while(x) {
		if (color[x] == WHITE) {
			heap[x].push(make_pair(0, x));
		}
		PII first, second;
		first = getV(x, heap[x]);
		pop(heap[x]);
		second = getV(x, heap[x], first.second);
		heap[x].push(first);
		
		modify(1, pos[x], first.first, second.first);
		
		s = top[x];
		x = fa[s];
		Node tmp = ask(1, pos[s], pos[floor[s]]);
		//PII see = getV(x, heap[x]);
		g[s] = max(getV(s, heap[s]).first, tmp.maxL);
		if (x) {
			heap[x].push(make_pair(g[s] + fv[s], s));
		}
		f[s] = tmp.opt;
		ansQ.push(make_pair(f[s], s));
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ansQ.push(make_pair(-inf, 0));
	f[0] = -inf;
	
	scanf("%d", &n);
	e.clear();
	for(int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		e.addEdge(a, b, c);
	}
	for(int i = 1; i <= n; i++) {
		f[i] = g[i] = -inf;
		color[i] = BLACK;
	}
	buildTree();
	for(int i = 1; i <= n; i++) {
		doit(i);
	}
	int q, cnt = 0;
	scanf("%d", &q);
	for(; q--; ) {
		if (++cnt == 5) {
			cnt = 5;
		}
		static char type[1000];
		int x;
		scanf("%s", type);
		if (type[0] == 'A') {
			int res = getAns();
			if (res < 0) {
				printf("They have disappeared.\n");
			} else {
				printf("%d\n", res);
			}
		} else {
			scanf("%d", &x);
			doit(x);
		}
	}
	return 0;
}
