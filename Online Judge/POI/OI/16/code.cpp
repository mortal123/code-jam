#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 222222;

struct Node {
	long long minV, tag;
	void operator += (long long v) {
		minV += v;
		tag += v;
	}
}T[N * 4];

int n, m, k, d;

void build(int root, int l, int r) {
	T[root].tag = 0;
	if (l == r) {
		T[root].minV = 1LL * min(n - l + 1, d + 1) * k;
		return;
	}
	
	int mid = (l + r) >> 1;
	
	build(root * 2, l, mid);
	build(root * 2 + 1, mid + 1, r);
	
	T[root].minV = min(T[root * 2].minV, T[root * 2 + 1].minV);
}

void insert(int root, int l, int r, int ql, int qr, int v) {
	if (qr < l || ql > r)
		return;
	
	if (ql <= l && r <= qr) {
		T[root] += v;
	} else {
		T[root * 2] += T[root].tag;
		T[root * 2 + 1] += T[root].tag;
		T[root].tag = 0;
		
		int mid = (l + r) >> 1;
		insert(root * 2, l, mid, ql, qr, v);
		insert(root * 2 + 1, mid + 1, r, ql, qr, v);
		T[root].minV = min(T[root * 2].minV, T[root * 2 + 1].minV);
	}
	
}

int main() {
	scanf("%d %d %d %d", &n, &m, &k, &d);
	build(1, 1, n);
	
	for(int i = 1; i <= m; i++) {
		int r, x;
		scanf("%d %d", &r, &x);
		insert(1, 1, n, r, n, -x);
		if (T[1].minV < 0) {
			printf("NIE\n");
		} else {
			printf("TAK\n");
		}
		
	}
	return 0;
}
