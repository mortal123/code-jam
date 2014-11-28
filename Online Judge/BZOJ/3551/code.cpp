#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 111111, M = 555555;
const int DEP = 20;
const int BOUND = 2 * 2222222;

struct Node {
	int sum;
	Node *child[2];
	Node(int sum) : sum(sum) {}
	Node() {}
};



Node *root[N + M];
Node mem[BOUND];
int used = 0;


inline Node *newNode(int s = 0) {
	mem[used] = Node(s);
	return &mem[used++];
}

int ra[N];
pair<int, int> sa[N];
int n, m, q;
vector<pair<int, pair<int, int> > > edges, edges2;
int bel[N + M], up[N + M][DEP];
vector<int> imNode;

Node *build(int x, int l, int r) {
	Node* t = newNode(0);
	if (l == r) {
		return t;
	}
	int mid = (l + r) >> 1;
	t->child[0] = build(x << 1, l, mid);
	t->child[1] = build(x << 1 | 1, mid + 1, r);
	return t;
}

Node *insert(Node *x, int l, int r, int pos) {
	Node* t = newNode();
	*t = *x;
	t->sum++;
	if (l == r) {
		return t;
	} else {
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			t->child[0] = insert(x->child[0], l, mid, pos);
		} else {
			t->child[1] = insert(x->child[1], mid + 1, r, pos);
		}
		return t;
	}
}

Node *combine(Node *a, Node *b) {
	if (a->sum == 0)
		return b;
	if (b->sum == 0)
		return a;
	Node *t = newNode(a->sum + b->sum);
	t->child[0] = combine(a->child[0], b->child[0]);
	t->child[1] = combine(a->child[1], b->child[1]);
	return t;
}

int ask(Node *x, int k) {
	int l = 1, r = n;
	while(1) {
		if (x->sum < k)
			return -1;
		if (l == r) {
			return sa[l].first;
		}
		int mid = (l + r) >> 1;
		if (x->child[1]->sum >= k) {
			x = x->child[1];
			l = mid + 1;
		} else {
			k -= x->child[1]->sum;
			r = mid;
			x = x->child[0];
		}
	}
}

int find(int x) {
	int p = x, t;
	while(bel[p] != p)
		p = bel[p];
	while(x != p) {
		t = bel[x];
		bel[x] = p;
		x = t;
	}
	return p;
}

void read(int &x) {
	x = 0;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) {
		x = x * 10 + ch - '0';
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i++) {
		int h;
		//scanf("%d", &h);
		read(h);
		sa[i].first = h, sa[i].second = i;
	}
	sort(sa + 1, sa + n + 1);
	for(int i = 1; i <= n; i++) {
		ra[sa[i].second] = i;
	}
	for(int i = 1; i <= m; i++) {
		int a, b, c;
		//scanf("%d %d %d", &a, &b, &c);
		read(a), read(b), read(c);
		edges.push_back(make_pair(c, make_pair(a, b)));
	}
	sort(edges.begin(), edges.end());
	root[0] = build(1, 1, n);
	for(int i = 1; i <= n; i++) {
		root[i] = insert(root[0], 1, n, ra[i]);
		imNode.push_back(i);
	}
	for(int i = 1; i <= n + m; i++) {
		bel[i] = i;
	}
	edges2 = edges;
	edges.clear();
	for(int i = 1; i <= m; i++) {
		int a = edges2[i - 1].second.first, b = edges2[i - 1].second.second;
		int fa = find(a), fb = find(b);
		if (fa == fb) {
			continue;
		} else {
			edges.push_back(edges2[i - 1]);
			bel[fa] = bel[fb] = i + n;
		}
	}
	m = (int)edges.size();
	for(int i = 1; i <= n + m; i++) {
		bel[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		int a = edges[i - 1].second.first, b = edges[i - 1].second.second;
		int fa = find(a), fb = find(b);
		if (fa == fb) {
			continue;
		} else {
			root[i + n] = combine(root[fa], root[fb]);
			bel[fa] = bel[fb] = i + n;
			up[fa][0] = up[fb][0] = i + n;
		}
	}
	for(int i = 1; i < DEP; i++)
		for(int j = 1; j <= n + m; j++) {
			up[j][i] = up[up[j][i - 1]][i - 1];
		}
	int lastAns = 0;
	for(int i = 1; i <= q; i++) {
		int x, lv, k;
		//scanf("%d %d %d", &x, &lv, &k);
		read(x), read(lv), read(k);
		/*
		if (lastAns != -1) {
			x ^= lastAns;
			lv ^= lastAns;
			k ^= lastAns;
		}*/
		for(int j = DEP - 1; j >= 0; j--) {
			if (up[x][j] && edges[up[x][j] - n - 1].first <= lv) {
				x = up[x][j];
			}
		}
		printf("%d\n", lastAns = ask(root[x], k));
	}
	return 0;
} 
