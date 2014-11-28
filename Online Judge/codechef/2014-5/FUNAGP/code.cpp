#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111111;

int n, q;
long long consR, mod1, mod2, mod, powerR[N], divide;
long long consV[N];

inline int readInt() {
	int x;
	scanf("%d", &x);
	return x;
}

long long power(long long a, long long b, long long mod) {
	if (b == 0)
		return 1;
	long long t = power(a, b >> 1, mod);
	if (b & 1) {
		return t * t % mod * (a % mod) % mod;
	} else {
		return t * t % mod;
	}
}

long long multiply(long long a, long long b) {
	a %= mod; b %= mod;
	long long result = (long long)((long double)a * b / mod);
	result = a * b - result * mod;
	while(result < 0)
		result += mod;
	while(result >= mod)
		result -= mod;
	return result;
}

struct SegmentTree {
	long long s[N << 2], d[N << 2], sum[N << 2];
	bool isLeaf[N << 2];
	int size[N << 2];
	void build(int x, int l, int r, long long v[]) {
		s[x] = d[x] = 0;
		isLeaf[x] = false;
		size[x] = r - l + 1;
		if (l == r) {
			isLeaf[x] = true;
			sum[x] = v[l] % mod;
		} else {
			int mid = (l + r) >> 1;
			build(x << 1, l, mid, v);
			build(x << 1 | 1, mid + 1, r, v);
			sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod1;
		}
	}
	
	void calc(int x, long long vs, long long vd) {
		if (isLeaf[x]) {
			(sum[x] += vs) %= mod;
		} else {
			(s[x] += vs) %= mod;
			(d[x] += vd) %= mod;
			vs %= mod1, vd %= mod1;
			long long sz = size[x];
			if (consR % mod1 == 1) {
				(sum[x] += vs * sz % mod1) %= mod1;
				(sum[x] += (sz - 1) * sz / 2 % mod1 * vd % mod1) %= mod1;
			} else {
				(sum[x] += ((vs + (sz - 1) * vd % mod1) % mod1 * 
					(powerR[sz] % mod1) % mod1 - vs + mod1) % mod1 * 
					divide % mod1) %= mod1;
				(sum[x] -= (vd * consR % mod1 * ((powerR[sz - 1] % mod1 - 1 + mod1) % mod1)) % mod1 * 
					divide % mod1 * divide % mod1) %= mod1;
				(sum[x] += mod1) %= mod1;
			}
			
		}
	}
	
	void pushDown(int x) {
		if (s[x] == 0 && d[x] == 0)
			return ;
		calc(x << 1, s[x], d[x]);
		calc(x << 1 | 1, multiply((s[x] + multiply(d[x], size[x << 1])) % mod, 
			powerR[size[x << 1]]), multiply(d[x], powerR[size[x << 1]]));
		s[x] = d[x] = 0;
	}
	
	void addAGP(int x, int l, int r, int ql, int qr, long long vs, long long vd) {
		if (l > qr || r < ql)
			return;
		if (ql <= l && r <= qr) {
			int span = l - ql;
			calc(x, multiply((vs + multiply(vd, span)) % mod, powerR[span]), multiply(vd, powerR[span]));
			return;
		}
		pushDown(x);
		int mid = (l + r) >> 1;
		addAGP(x << 1, l, mid, ql, qr, vs, vd);
		addAGP(x << 1 | 1, mid + 1, r, ql, qr, vs, vd);
		sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod1;
	}
	
	void power(int x, int l, int r, int p, int g) {
		if (l == r) {
			long long start = 1, base = sum[x] % mod2;
			while(g) {
				if (g & 1) {
					(start *= base) %= mod2;
				}
				g >>= 1;
				(base *= base) %= mod2;
			}
			sum[x] = start;
			return;
		}
		pushDown(x);
		int mid = (l + r) >> 1;
		if (p <= mid) {
			power(x << 1, l, mid, p, g);
		} else {
			power(x << 1 | 1, mid + 1, r, p, g);
		}
		sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod1;
	}
	
	long long askSum(int x, int l, int r, int ql, int qr) {
		if (l > qr || r < ql)
			return 0;
		if (ql <= l && r <= qr) {
			return sum[x] % mod1;
		}
		pushDown(x);
		int mid = (l + r) >> 1;
		long long result = (askSum(x << 1, l, mid, ql, qr) + askSum(x << 1 | 1, mid + 1, r, ql, qr)) % mod1;
		sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod1;
		return result;
	}
};

SegmentTree tree;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int testCount;
	scanf("%d", &testCount);
	while(testCount--) {
		cin >> n >> q >> consR >> mod1 >> mod2;
		divide = power((consR - 1) % mod1, mod1 - 2, mod1);
		//scanf("%d %d %lld %lld %lld", &n, &q, &consR, &mod1, &mod2);
		mod = mod1 * mod2;
		powerR[0] = 1;
		for(int i = 1; i <= n; i++) {
			consV[i] = readInt();
			powerR[i] = multiply(powerR[i - 1], consR);
		}
		
		tree.build(1, 1, n, consV);
		
		for(int i = 1; i <= q; i++) {
			int type;
			scanf("%d", &type);
			if (type == 0) {
				int s, d, l, r;
				scanf("%d %d %d %d", &s, &d, &l, &r);
				tree.addAGP(1, 1, n, l, r, s, d);
			} else if (type == 1) {
				int x, g;
				scanf("%d %d", &x, &g);
				tree.power(1, 1, n, x, g);
			} else {
				int l, r;
				scanf("%d %d", &l, &r);
				printf("%lld\n", tree.askSum(1, 1, n, l, r) % mod1);
				//cout << tree.askSum(1, 1, n, l, r) << endl;
			}
			//tree.askSum(1, 1, n, 4, 4);
			/*
			for(int j = 1; j <= n; j++) {
				cout << tree.askSum(1, 1, n, j, j) << " ";
			}
			cout << endl;
			*/
		}
	}
} 
