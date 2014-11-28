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
typedef pair<int, int> PII;

int down[N];
int n, tag[N], top[N], floor[N], pos[N], rpos[N], color[N];
int que[N], fa[N], size[N], son[N], dep[N], same[N], totColor;
int L[N], R[N];
vector<int> stack[N];

struct Node {
	int l, r, add, cover, color;
	long long sum;
	inline friend Node operator +(const Node &a, const Node &b) {
		Node c;
		c.l = a.l;
		c.r = b.r;
		
		return c;
	}
}T[N * 4];

void build(int root, int l, int r) {
	T[root].l = l;
	T[root].r = r;
	T[root].add = T[root].sum = 0;
	T[root].cover = 0;
	T[root].color = 0;
	if (l == r) {
		return;
	}
	build(root << 1, l, (l + r) >> 1);
	build(root << 1 | 1, ((l + r) >> 1) + 1, r);
}

inline void modify(Node &R, int ad, int c) {
	R.sum += 1LL * ad * (R.r - R.l + 1);
	R.add += ad;
	if (c) {
		R.color = R.cover = c;
	}
}

inline void pushDown(int root) {
	modify(T[root * 2], T[root].add, T[root].cover);
	modify(T[root * 2 + 1], T[root].add, T[root].cover);
	T[root].add = T[root].cover = 0;
}

inline void update(int root) {
	T[root].sum = T[root << 1].sum + T[root << 1 | 1].sum;
}

long long ask(int root, int l, int r) {
	if (l <= T[root].l && T[root].r <= r)
		return T[root].sum;
	pushDown(root);
	int mid = (T[root].l + T[root].r) / 2;
	long long res = 0;
	if (l <= mid)
		res += ask(root << 1, l, r);
	if (r > mid)
		res += ask(root << 1 | 1, l, r);
	update(root);
	return res;
}

int askColor(int root, int pos) {
	if (T[root].l == T[root].r)
		return T[root].color;
	pushDown(root);
	int mid = (T[root].l + T[root].r) / 2, res;
	if (pos <= mid)
		res = askColor(root << 1, pos);
	else
		res = askColor(root << 1 | 1, pos);
	update(root);
	return res;
}

void insert(int root, int l, int r, int v) {
	if (l <= T[root].l && T[root].r <= r) {
		modify(T[root], v, 0);
		return;
	}
	pushDown(root);
	int mid = (T[root].l + T[root].r) / 2;
	if (l <= mid)
		insert(root << 1, l, r, v);
	if (r > mid)
		insert(root << 1 | 1, l, r, v);
	update(root);
}

void colored(int root, int l, int r, int c) {
	if (l <= T[root].l && T[root].r <= r) {
		modify(T[root], 0, c);
		return;
	}
	pushDown(root);
	int mid = (T[root].l + T[root].r) / 2;
	if (l <= mid)
		colored(root << 1, l, r, c);
	if (r > mid)
		colored(root << 1 | 1, l, r, c);
	update(root);
}

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
	/*
	for(int i = 1; i <= n; i++) {
		printf("top = %d  floor = %d  tag = %d  pos = %d\n", top[i], floor[i], tag[i], pos[i]);
	}
	*/
}

void dfsOrder(int root) {
	static int st[N * 2], se[N * 2];
	int top = 0, stamp = 0;
	st[++top] = root;
	se[top] = e.last[root];
	L[root] = ++stamp;
	while(top) {
		int x = st[top];
		if (se[top] == -1) {
			R[x] = stamp;
			top--;
			continue;
		}
		int y = e.other[se[top]];
		se[top] = e.succ[se[top]];
		if (y == fa[x])
			continue;
		st[++top] = y;
		se[top] = e.last[y];
		L[y] = ++stamp;
	}
}

vector<int> vec;

void march(int x) {
	int s = 0;
	if (same[x] != 0) {
		insert(1, L[same[x]], R[same[x]], 1);
	} else if (x != floor[x]) {
		if (askColor(1, pos[x]) == askColor(1, pos[son[x]])) {
			insert(1, L[son[x]], R[son[x]], 1);
		}
	}
	++totColor;
	while(x) {
		vec.clear();
		int len = pos[x] - pos[top[x]];
		while(stack[top[x]].size() > 0 && stack[top[x]].back() <= len) {
			vec.push_back(stack[top[x]].back());
			stack[top[x]].pop_back();
		}
		while(vec.size()) {
			int l = vec.back();
			vec.pop_back();
			int y = rpos[pos[top[x]] + l];
			if (len > l)
				insert(1, L[son[y]], R[son[y]], -1);
			if (same[y]) {
				insert(1, L[same[y]], R[same[y]], 1);
				same[y] = 0;
			}
		}
		colored(1, pos[top[x]], pos[x], totColor);
		stack[top[x]].push_back(len);
		same[x] = s;
		s = top[x];
		x = fa[s];
	}
}

int Main() {
	int q;
	scanf("%d %d", &n, &q);
	
	e.clear(n);
	for(int i = 2; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a++; b++;
		e.addEdge(a, b);
	}
	buildTree();
	dfsOrder(1);
	build(1, 1, n);
	totColor = 0;
	for(int i = 1; i <= n; i++) {
		same[i] = 0;
		stack[i].clear();
	}
	for(int i = 1; i <= n; i++) {
		march(que[i]);
	}
	char type[10];
	for(; q--; ) {
		int x;
		scanf("%s %d", type, &x);
		if (type[0] == 'O') {
			march(x);
		} else {
			printf("%.6f\n", 1.0 * ask(1, L[x], R[x]) / size[x]);
		}
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		Main();
	}
	return 0;
}
