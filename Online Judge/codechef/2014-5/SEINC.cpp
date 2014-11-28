#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;

int n, a[N], b[N];

struct SegTree {
	int sum[N << 2], pre[N << 2];
	void update(int x) {
		sum[x] = sum[x << 1] + sum[x << 1 | 1];
		pre[x] = min(pre[x << 1], sum[x << 1] + pre[x << 1 | 1]);
	}
	void build(int x, int l, int r, int a[]) {
		if (l == r) {
			sum[x] = pre[x] = a[l];
		} else {
			int mid = (l + r) >> 1;
			build(x << 1, l, mid, a);
			build(x << 1 | 1, mid + 1, r, a);
			update(x);
		}
	}
	void modify(int x, int l, int r, int pos, int v) {
		if (l == r) {
			sum[x] = pre[x] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			modify(x << 1, l, mid, pos, v);
		} else {
			modify(x << 1 | 1, mid + 1, r, pos, v);
		}
		update(x);
	}
	int getMinPre() {
		return pre[1];
	}
};

SegTree tree;
int s1, s2;

void haveTry(int valve) {
	for(int i = n; s1 - 4 >= s2 && i >= 1; i--) {
		if (a[i] == valve) {
			tree.modify(1, 1, n, i, valve - 4);
			if (tree.getMinPre() < 0) {
				tree.modify(1, 1, n, i, valve);
			} else {
				s1 -= valve, s2 += -(valve - 4);
				a[i] = valve - 4;
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}		
		for(int i = 1; i <= n; i++) {
			scanf("%d", &b[i]);
			a[i] = (b[i] - a[i] + 4) % 4;
			b[i] = a[i];
		}
		for(int i = 1; i <= n; i++) {
			a[i] = (b[i] - b[i - 1] + 4) % 4;
		}
		
		tree.build(1, 1, n, a);
		s1 = 0, s2 = 0;
		
		for(int i = 1; i <= n; i++) {
			s1 += a[i];
		}
		haveTry(3);
		haveTry(2);
		haveTry(1);
		printf("%d\n", s1);
	}
	return 0;
}
