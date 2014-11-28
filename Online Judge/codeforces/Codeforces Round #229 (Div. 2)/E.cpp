#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5555555;

long long v[N], h[N], vi[N], hi[N];
int n, m, q;

long long ask(long long a[], int pos) {
	long long res = 0;
	for(int i = pos; i; i -= (i & (-i))) {
		res += a[i];
	} 
	
	return res;
}

long long ins(long long a[], int n, int pos, long long val) {
	for(int i = pos; i <= n; i += (i & (-i))) {
		a[i] += val;
	}
}

long long solve(long long a[N], long long ai[N], int pos, int n) {
	return ask(a, pos) * (pos + 1) - ask(ai, pos);
}

int main() {
	scanf("%d %d %d", &n, &m, &q);
	long long total = 0;
	for(int i = 1; i <= q; i++) {
		int x1, x2, y1, y2, type, val;
		scanf("%d %d %d %d %d", &type, &x1, &y1, &x2, &y2);
		if (type == 0) {
			scanf("%d", &val);
			total += 1LL * val * (x2 - x1 + 1) * (y2 - y1 + 1);
			// vertical
			
			ins(v, n, x1, 1LL * val * (y2 - y1 + 1));
			ins(vi, n, x1, 1LL * val * (y2 - y1 + 1) * x1);
			ins(v, n, x2 + 1, -1LL * val * (y2 - y1 + 1));
			ins(vi, n, x2 + 1, -1LL * val * (y2 - y1 + 1) * (x2 + 1));
			
			ins(h, m, y1, 1LL * val * (x2 - x1 + 1));
			ins(hi, m, y1, 1LL * val * y1 * (x2 - x1 + 1));
			ins(h, m, y2 + 1, -1LL * val * (x2 - x1 + 1));
			ins(hi, m, y2 + 1, -1LL * val * (y2 + 1) * (x2 - x1 + 1));
		} else if (type == 1) {
			long long ans = 0;
			ans = solve(v, vi, x2, n) - solve(v, vi, x1 - 1, n)
				+ solve(h, hi, y2, m) - solve(h, hi, y1 - 1, m);
			printf("%I64d\n", ans - total);
		}
	}
	return 0;
} 
