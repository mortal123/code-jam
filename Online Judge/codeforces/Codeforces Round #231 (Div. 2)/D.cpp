#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1111;

int n, lowest, step;
int a[N];

bool solve2(int i, int v, int bound) {
	int l = 0, r = 1111111;
	for(int j = 1; j < i; j++) {
		l = max(l, (v - (a[j] + bound) + (i - j - 1)) / (i - j));
		r = min(r, (v - (a[j] - bound)) / (i - j));
	}
	
	for(int j = i + 1; j <= n; j++) {
		l = max(l, (a[j] - bound - v + (j - i - 1)) / (j - i));
		r = min(r, (a[j] + bound - v) / (j - i));
	}
	
	if (l <= r) {
		lowest = v - (i - 1) * l;
		step = l;
		return 1;
	}
	
	return 0;
}

int solve(int bound) {
	for(int i = 1; i <= n; i++) {
		if (solve2(i, a[i] + bound, bound))
			return 1;
		if (solve2(i, a[i] - bound, bound))
			return 1;
	}
	
	return 0;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	sort(a + 1, a + n + 1);
	
	int l = 0, r = 111111, mid;
	while(l < r) {
		mid = (l + r) / 2;
		if (solve(mid))
			r = mid;
		else
			l = mid + 1;
	}
	
	solve(l);
	printf("%d\n", l);
	printf("%d %d\n", lowest, step);
	return 0;
}
