#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 800000 + 5;

int tree[N << 1][12], temp[12];
int shift[N << 1];
int n, m, a[N], length[N], power[10];

inline int getID(const int &l, const int &r) {
	return l + r | l != r;
}

void doThis(int x, int v) {
	(shift[x] += v) %= 12;
	for(int i = 0; i < 12; i++) {
		temp[i] = tree[x][(v + i) % 12];
	}
	for(int i = 0; i < 12; i++) {
		tree[x][i] = temp[i];
	}
}

inline void update(int l, int r) {
	int x = getID(l, r);
	int mid = (l + r) >> 1;
	int lc = getID(l, mid), rc = getID(mid + 1, r);
	for(int i = 0; i < 12; i++) {
		tree[x][i] = max(tree[lc][i], tree[rc][i]);
	}
}

void pushDown(int l, int r) {
	int x = getID(l, r);
	int mid = (l + r) >> 1;
	int lc = getID(l, mid), rc = getID(mid + 1, r);
	if (shift[x]) {
		doThis(lc, shift[x]);
		doThis(rc, shift[x]);
		shift[x] = 0;
	}
}

void move(int &x, int len) {
	x = (x - x / power[len - 1] * power[len - 1]) * 10 + x / power[len - 1];
}

void build(int l, int r) {
	int x = getID(l, r);
	shift[x] = 0;
	if (l == r) {
		for(int i = 0; i < 12; i++) {
			tree[x][i] = a[l];
			move(a[l], length[l]);
		}
	} else {
		int mid = (l + r) >> 1;
		build(l, mid);
		build(mid + 1, r);
		update(l, r);
	}
}

int ask(int l, int r, int ql, int qr) {
	if (qr < l || r < ql) {
		return 0;
	}
	int x = getID(l, r);
	if (ql <= l && r <= qr) {
		return tree[x][0];
	}
	pushDown(l, r);
	int mid = l + r >> 1;
	int result = max(ask(l, mid, ql, qr), ask(mid + 1, r, ql, qr));
	update(l, r);
	return result;
}

void modify(int l, int r, int ql, int qr, int v) {
	if (qr < l || r < ql) {
		return ;
	}
	int x = getID(l, r);
	if (ql <= l && r <= qr) {
		doThis(x, v);
	} else {
		pushDown(l, r);
		int mid = l + r >> 1;
		modify(l, mid, ql, qr, v);
		modify(mid + 1, r, ql, qr, v);
		update(l, r);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	power[0] = 1;
	power[1] = 10;
	power[2] = 100;
	power[3] = 1000;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		int temp = a[i];
		length[i] = 0;
		while(temp) {
			length[i] ++;
			temp /= 10;
		}
		if (length[i] == 0) {
			length[i] = 1;
		}
	}
	build(1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int opt, l, r;
		scanf("%d %d %d", &opt, &l, &r);
		l++;
		r++;
		if (opt == 1) {
			printf("%d\n", ask(1, n, l, r));
		} else {
			int x;
			scanf("%d", &x);
			modify(1, n, l, r, x % 12);
		}
	}
	return 0;
} 
