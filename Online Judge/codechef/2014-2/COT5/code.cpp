#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

const int N = 222222;

int maxBound = 0;
int n, m;

struct Quer {
	int op, a, b;
}q[N];

pair<int, int> pairs[N];

struct Node {
	int mp, mv, tl, tr;
	bool isLeaf;
	Node(int a, int b, int c, int d) : mp(a), mv(b), tl(c), tr(d) {}
	
	Node(int mv) : mv(mv) {
		if (mv > 0)
			tl = tr = 1;
		else
			tl = tr = 0;
	}
	
	Node() {}
}T[N << 2];

int jumpToRight(int x, int h) {
	
	if (x > maxBound) {
		int y = maxBound;
		y++;
		y--;
	}assert(x <= maxBound);
	if (T[x].isLeaf) {
		return h < T[x].mv;
	}
	
	return T[x << 1].mv <= h ? jumpToRight(x << 1 | 1, h) : T[x].tr - T[x << 1].tr + jumpToRight(x << 1, h);
}

int jumpToLeft(int x, int h) {
	
	if (x > maxBound) {
		int y = maxBound;
		y++;
		y--;
	}assert(x <= maxBound);
	if (T[x].isLeaf) {
		return h < T[x].mv;
	}
	
	return T[x << 1 | 1].mv <= h ? jumpToLeft(x << 1, h) : T[x].tl - T[x << 1 | 1].tl + jumpToLeft(x << 1 | 1, h); 
}

void update(int x) {
	if (T[x << 1].mv > T[x << 1 | 1].mv) {
		T[x].mv = T[x << 1].mv;
		T[x].mp = T[x << 1].mp;
	} else {
		T[x].mv = T[x << 1 | 1].mv;
		T[x].mp = T[x << 1 | 1].mp;
	}
	
	T[x].tr = T[x << 1].tr + jumpToRight(x << 1 | 1, T[x << 1].mv);
	T[x].tl = T[x << 1 | 1].tl + jumpToLeft(x << 1, T[x << 1 | 1].mv);
}

void build(int x, int l, int r) {
	maxBound = max(maxBound, x);
	T[x] = Node(l, 0, 0, 0);
	if (l == r) {
		T[x].isLeaf = true;
		//printf("isLeaf %d\n", x);
		return ;
	}
	
	T[x].isLeaf = false;
	int mid = (l + r) / 2;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}

void modify(int x, int l, int r, int pos, int v) {
	if (l == r) {
		pairs[pos].second = v;
		T[x].mp = l;
		T[x].mv = v;
		if (v)
			T[x].tl = T[x].tr = 1;
		else
			T[x].tl = T[x].tr = 0;
		return ;		
	}
	
	int mid = (l + r) / 2;
	if (pos <= mid) 
		modify(x << 1, l, mid, pos, v);
	else 
		modify(x << 1 | 1, mid + 1, r, pos, v);
	/*printf("enter modify as %d\n", x);
	if (x == 65672)
		x = 65672;
	*/
	update(x);
	/*
	printf("over modify\n");
	*/
}

int askMaxPos(int x, int l, int r, int ql, int qr) {
	if (l > qr || r < ql)
		return 0;
	
	if (ql <= l && r <= qr) {
		return T[x].mp;
	}
	
	int mid = (l + r) / 2;
	int ra = askMaxPos(x << 1, l, mid, ql, qr);
	int rb = askMaxPos(x << 1 | 1, mid + 1, r, ql, qr);
	
	if (pairs[ra].second > pairs[rb].second)
		return ra;
	else
		return rb;
}

void getNode(int x, int l, int r, int ql, int qr, vector<int> &vec) {
	if (ql > r || qr < l)
		return ;
		
	if (ql <= l && r <= qr) {
		vec.push_back(x);
		return ;
	}
	
	int mid = (l + r) / 2;
	getNode(x << 1, l, mid, ql, qr, vec);
	getNode(x << 1 | 1, mid + 1, r, ql, qr, vec);
}

int calcDepth(int a) {
	vector<int> left, right;
	getNode(1, 1, n, 1, a, left);
	getNode(1, 1, n, a, n, right);
	int res = 0;
	for(int i = (int)left.size() - 1, last = 0; i >= 0; i--) {
		res += jumpToLeft(left[i], last);
		last = max(last, T[left[i]].mv);
	}
	
	for(int i = 0, last = 0; i < (int)right.size(); i++) {
		res += jumpToRight(right[i], last);
		last = max(last, T[right[i]].mv);
	}
	
	return res - 2;
}

int main() {
	freopen("input.txt", "r", stdin);
	n = 0;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int op, a, b;
		scanf("%d %d", &op, &a);
		q[i].op = op;
		q[i].a = a;
		if (op == 0) {
			scanf("%d", &b);
			q[i].b = b;
			pairs[++n] = make_pair(a, 0);
		} else if (op == 1) {
		} else if (op == 2) {
			scanf("%d", &b);
			q[i].b = b;
		}
	}
	
	sort(pairs + 1, pairs + n + 1);
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		
		//printf("step %d\n", i);
		if (q[i].op == 0) {
			int pos = lower_bound(pairs + 1, pairs + n + 1, make_pair(q[i].a, 0)) - pairs;
			//printf("type 1\n");
			modify(1, 1, n, pos, q[i].b);
		} else if (q[i].op == 1) {
			int pos = lower_bound(pairs + 1, pairs + n + 1, make_pair(q[i].a, 0)) - pairs;
			//printf("type 2\n");
			modify(1, 1, n, pos, 0);
		} else {
			int a = lower_bound(pairs + 1, pairs + n + 1, make_pair(q[i].a, 0)) - pairs;
			int b = lower_bound(pairs + 1, pairs + n + 1, make_pair(q[i].b, 0)) - pairs;
			if (a > b)
				swap(a, b);
			int ps = askMaxPos(1, 1, n, a, b);
			printf("%d\n", calcDepth(a) + calcDepth(b) - 2 * calcDepth(ps));
			/*
			printf("depth %d = %d\n", a, calcDepth(a));
			printf("depth %d = %d\n", b, calcDepth(b));
			printf("depth %d = %d\n", ps, calcDepth(ps));
			*/
		}
	}
	return 0;
} 
