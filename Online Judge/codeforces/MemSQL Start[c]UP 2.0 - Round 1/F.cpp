#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MOD = 1e9 + 9;
const int EP = 7;

const int N = 333333;

int treeL[N << 2], treeR[N << 2];
int power[N];
int a[N], n;

void update(int x, int l, int m, int r) {
	treeL[x] = 1LL * treeL[x << 1] * power[r - m] % MOD + treeL[x << 1 | 1];
	treeL[x] %= MOD;
	treeR[x] = 1LL * treeR[x << 1 | 1] * power[m - l + 1] % MOD + treeR[x << 1];
	treeR[x] %= MOD;
}

void build(int x, int l, int r) {
	if (l == r) {
		treeL[x] = treeR[x] = 2;
		return ;
	}
	int m = (l + r) / 2;
	build(x << 1, l, m);
	build(x << 1 | 1, m + 1, r);
	update(x, l, m, r);
}


void modify(int x, int l, int r, int pos) {
	if (l == r) {
		treeL[x] = treeR[x] = 1;
		return ;
	}
	int m = (l + r) / 2;
	if (pos <= m) {
		modify(x << 1, l, m, pos);
	} else {
		modify(x << 1 | 1, m + 1, r, pos);
	}
	update(x, l, m, r);
}

int getL(int x, int l, int r, int ql, int qr) {
	if (qr < l || ql > r) {
		return 0;
	}
	if (ql <= l && r <= qr) {
		return 1LL * treeL[x] * power[qr - r] % MOD;
	}
	
	int m = (l + r) / 2;
	
	return (getL(x << 1, l, m, ql, qr) + getL(x << 1 | 1, m + 1, r, ql, qr)) % MOD;
}

int getR(int x, int l, int r, int ql, int qr) {
	if (qr < l || ql > r) {
		return 0;
	}
	if (ql <= l && r <= qr) {
		return 1LL * treeR[x] * power[l - ql] % MOD;
	}
	
	int m = (l + r) / 2;
	
	return (getR(x << 1, l, m, ql, qr) + getR(x << 1 | 1, m + 1, r, ql, qr)) % MOD;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	build(1, 1, n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	power[0] = 1;
	for(int i = 1; i <= n; i++) {
		power[i] = 1LL * power[i - 1] * EP % MOD;
	}
	for(int i = 1; i <= n; i++) {
		modify(1, 1, n, a[i]);
		int len = min(a[i] - 1, n - a[i]);
		if (getL(1, 1, n, a[i] - len, a[i] - 1) != getR(1, 1, n, a[i] + 1, a[i] + len)) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
