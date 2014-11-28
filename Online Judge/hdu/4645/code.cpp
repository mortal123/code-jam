#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 111111, M = N * 2;
const int inf = 1000000000;

priority_queue<pair<int, int> > heap[N][2];

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

int size[N], father[N], son[N], g[N], pos[N], rpos[N], floor[N];
int weight[N], color[N], tag[N], n, m, top[N];

struct Node {
	int l, r, commonL, commonR, maxL, maxR;
	inline friend Node operator +(Node a, Node b) {
		Node c;
		c.l = a.l, c.r = b.r;
		c.commonL = a.commonL, c.maxL = a.maxL;
		if (c.commonL == a.r && color[rpos[a.r]] == color[rpos[b.l]])
			c.commonL = b.commonL, c.maxL = max(a.maxL, b.maxL);
		c.commonR = b.commonR, c.maxR = b.maxR;
		if (c.commonR == b.l && color[rpos[b.l]] == color[rpos[a.r]])
			c.commonR = a.commonR, c.maxR = max(b.maxR, a.maxR);
		return c;
	}
}T[N * 4];

void build(int root, int l, int r) {
	if (l == r) {
		T[root].l = l;
		T[root].r = r;
		T[root].commonL = r;
		T[root].commonR = l;
		T[root].maxL = T[root].maxR = 0;
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

int getTop(int x) {
	int c = color[x];
	while(!heap[x][c].empty()) {
		pair<int, int> p = heap[x][c].top();
		if (p.second == x && weight[x] != p.first || p.second != x && p.first != g[p.second] || 
			p.second != x && color[p.second] != c)
			heap[x][c].pop();
		else
			break;
	}
	if (heap[x][c].empty())
		return -inf;
	return heap[x][c].top().first;
}

void modify(int root, int pos) {
	if (T[root].l == T[root].r) {
		T[root].maxL = T[root].maxR = getTop(rpos[pos]);
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
		if (x == source) {
			heap[x][color[x]].push(make_pair(weight[x], x));
		} else {
			heap[x][color[s]].push(make_pair(g[s], s));
		}
		modify(1, pos[x]);
		x = top[x];
		Node tmp = subTree(x);
		g[x] = tmp.maxL;
		
		s = x;
		x = father[x];
	}
}

void clearHeap(priority_queue<pair<int, int> > &w) {
	while(!w.empty())
		w.pop();
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
			clearHeap(heap[i][0]);
			clearHeap(heap[i][1]);
			color[i] = 0;
			weight[i] = 0;
			g[i] = 0;
		}
		buildTree();
		static int col[N], wei[N];
		for(int i = 1; i <= n; i++) {
			scanf("%d", &col[i]);
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &wei[i]);
		}
		for(int i = 1; i <= n; i++) {
			weight[i] = wei[i];
			color[i] = col[i];
			doit(i);
		}
		int m;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			int type, a, b;
			scanf("%d %d", &type, &a);
			if (type == 0) {
				a = findFather(a);
				printf("%d\n", subTree(a).maxL);
			} else if (type == 1) {
				color[a] ^= 1;
				doit(a);
			} else if (type == 2) {
				scanf("%d", &b);
				weight[a] = b;
				doit(a);
			}
		}
	}
	return 0;
} 
