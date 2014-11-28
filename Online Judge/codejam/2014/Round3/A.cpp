#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int N = 1111111;

int n, p, q, r, s;
long long a[N], sum[N];

long long solve(int l, int r) {
	long long ret = sum[r] - sum[l - 1];
	if (l > 1) {
		ret = max(ret, sum[l - 1]);
	}
	if (r < n) {
		ret = max(ret, sum[n] - sum[r]);
	}
	return ret;
}

int main() {
	freopen("A-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		long long ans = (1LL << 60);
		scanf("%d %d %d %d %d", &n, &p, &q, &r, &s);
		for(int i = 0; i < n; i++) {
			a[i + 1] = ((1LL * i * p + q) % r + s);
			sum[i + 1] = sum[i] + a[i + 1];
		}
		for(int r = 1, l = 1; r <= n; r++) {
			while(l < r && sum[l - 1] < sum[r] - sum[l - 1])
				l++;
			ans = min(ans, solve(l, r));
			if (l > 1)
				ans = min(ans, solve(l - 1, r));
		}
		printf("Case #%d: %.12f\n", ++testCount, 1 - 1.0 * ans / sum[n]);
	}
	return 0;
} 
