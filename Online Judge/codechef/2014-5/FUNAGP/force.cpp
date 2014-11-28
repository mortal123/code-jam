#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111111;

int p1, p2, n, ratio, q;
long long a[N], mod;

long long multiply(long long a, long long b) {
	long long result = 0;
	a %= mod; b %= mod;
	while(b) {
		if (b & 1) {
			(result += a) %= mod;
		}
		b >>= 1;
		(a += a) %= mod;
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d %d %d %d", &n, &q, &ratio, &p1, &p2);
		mod = 1LL * p1 * p2;
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			a[i] = x;
		}
		for(int i = 1; i <= q; i++) {
			int t;
			scanf("%d", &t);
			if (t == 0) {
				int s, d, l, r;
				scanf("%d %d %d %d", &s, &d, &l, &r);
				long long power = 1;
				for(int j = l; j <= r; j++) {
					(a[j] += multiply(s + 1LL * (j - l) * d, power)) %= mod;
					power = multiply(power, ratio);
				}
			} else if (t == 1) {
				int x, g;
				scanf("%d %d", &x, &g);
				long long s = 1;
				a[x] %= p2;
				for(int j = 1; j <= g; j++) {
					s = s * a[x] % p2;
				}
				a[x] = s;
			} else {
				int l, r;
				scanf("%d %d", &l, &r);
				long long ans = 0;
				for(int j = l; j <= r; j++) {
					(ans += a[j]) %= p1;
				}
				cout << ans << endl;
			}
			for(int j = 1; j <= n; j++) {
				cout << a[j] << " ";
			}
			cout << endl;
		}
	}
}
