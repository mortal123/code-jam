#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 111111, M = N * 2;
const int inf = 1000000000;
const int BLACK = 1, WHITE = 0;

int f[N][2], g[N];

struct eglist {
	int other[M], succ[M], last[M], sum;
	void clear(int n) {
		sum = 1;
		fill(last, last + n + 1, 0);
	}
	void addEdge(int a, int b) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;

int size[N], father[N], son[N], pos[N], rpos[N], floor[N];
int color[N], tag[N], n, m, top[N];

struct Node {
	int l, r, commonL, commonR, sumL, sumR;
	inline friend Node operator +(const Node &a, const Node &b) {
		Node c;
		c.l = a.l, c.r = b.r;
		c.commonL = a.commonL, c.sumL = a.sumL;
		if (c.commonL == a.r && color[rpos[a.r]] == color[rpos[b.l]])
			c.commonL = b.commonL, c.sumL = a.sumL + b.sumL;
		c.commonR = b.commonR, c.sumR = b.sumR;
		if (c.commonR == b.l && color[rpos[b.l]] == color[rpos[a.r]])
			c.commonR = a.commonR, c.sumR = b.sumR + a.sumR;
		return c;
	}
}T[N * 4];

void build(int root, int l, int r) {
	if (l == r) {
		T[root].l = l;
		T[root].r = r;
		T[root].commonL = r;
		T[root].commonR = l;
		T[root].sumL = T[root].sumR = f[rpos[l]][BLACK];
	} else {
		int mid = (l + r) / 2;
		build(root * 2, l, mid);
		build(root * 2 + 1, mid + 1, r);
		T[root] = T[root * 2] + T[root * 2 + 1];
	}
}

void buildTree() {
	static int q[N];
	int tail = 0;
	q[tail++] = 1;
	father[1] = 0;
	for(int head = 0; head < tail; head++) {
		int x = q[head];
		for(int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == father[x])
				continue;
			q[tail++] = y;
			father[y] = x;
		}
	}
	fill(size + 1, size + n + 1, 0);
	for(int i = tail - 1; i >= 0; i--) {
		int x = q[i];
		size[x]++;
		size[father[x]] += size[x];
		son[x] = -1;
		for(int iter = e.last[x]; iter; iter = e.succ[iter]) {
			int y = e.other[iter];
			if (y == father[x])
				continue;
			if (son[x] == -1 || size[y] > size[son[x]])
				son[x] = y;
		}
		f[x][WHITE] = 1;
		if (son[x] != -1) {
			f[x][BLACK] = size[x] - size[son[x]];
		} else {
			f[x][BLACK] = size[x];
		}
		
		g[x] = size[x];
	}
	int count = 0;
	fill(tag + 1, tag + n + 1, -1);
	tag[0] = 0;
	for(int i = 0; i < tail; i++) {
		int x = q[i];
		if (tag[x] == -1) {
			tag[x] = tag[father[x]] + 1;
			int temp = x, last;
			while(temp != -1) {
				top[temp] = x;
				pos[temp] = ++count;
				rpos[count] = temp;
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
	build(1, 1, count);
}

Node askTree(int root, int l, int r) {
	if (l <= T[root].l && T[root].r <= r) {
		return T[root];
	}
	int mid = (T[root].l + T[root].r) / 2;
	if (l > mid)
		return askTree(root * 2 + 1, l, r);
	if (r <= mid)
		return askTree(root * 2, l, r);
	return askTree(root * 2, l, r) + askTree(root * 2 + 1, l, r);
}

void modify(int root, int pos) {
	if (T[root].l == T[root].r) {
		int x = rpos[pos];
		T[root].sumL = T[root].sumR = f[x][color[x]];
		return;
	}
	int mid = (T[root].l + T[root].r) / 2;
	if (pos <= mid)
		modify(root * 2, pos);
	else
		modify(root * 2 + 1, pos);
	T[root] = T[root * 2] + T[root * 2 + 1];
}

Node subTree(int x) {
	Node tmp = askTree(1, pos[x], pos[floor[x]]);
	return tmp;
}

int findFather(int x) {
	while(1) {
		Node tmp = askTree(1, pos[top[x]], pos[x]);
		if (tmp.commonR == tmp.l) {
			x = top[x];
		} else {
			x = rpos[tmp.commonR];
			break;
		}
		if (father[x] && color[x] == color[father[x]])
			x = father[x];
		else
			break;
	}
	return x;
}

void doit(int x) {
	int source = x, s = 0;
	
	while(x) {
		if (x != source) {
			f[x][color[s]] -= g[s];
		}
		
		x = top[x];
		s = x;
		x = father[x];
	}

	x = source; s = 0;
	color[x] ^= 1;
		
	while(x) {
		if (x != source) {
			f[x][color[s]] += g[s];
		}
		
		modify(1, pos[x]);
		x = top[x];
		Node tmp = subTree(x);
		
		g[x] = tmp.sumL;
		
		s = x;
		x = father[x];
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(scanf("%d", &n) == 1) {
		e.clear(n);
		for(int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			e.addEdge(a, b);
		}
		for(int i = 1; i <= n; i++) {
			f[i][0] = f[i][1] = g[i] = 0;
			color[i] = 0;
		}
		buildTree();
		
		for(int i = 1; i <= n; i++) {
			color[i] = BLACK;
		}
		
		int m;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			int type, a, b;
			scanf("%d %d", &type, &a);
			if (type == 0) {
				a = findFather(a);
				printf("%d\n", subTree(a).sumL);
			} else if (type == 1) {
				doit(a);
			}
		}
	}
	return 0;
} 
