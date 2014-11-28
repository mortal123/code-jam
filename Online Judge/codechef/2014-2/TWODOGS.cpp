#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1111111;
const int INF = 111111111;

int n, a[N], k;
int right[N], left[N];

int main() {
	scanf("%d %d", &n, &k);
	fill(left, left + N, n + 1);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		right[a[i]] = i;
		left[a[i]] = min(left[a[i]], i);
	}
	
	int ans = INF;
	for(int i = 1; i <= n; i++) {
		if (a[i] <= k && a[i] * 2 != k && right[k - a[i]]) {
			ans = min(ans, max(min(i, n - i + 1), min(left[k - a[i]], n - right[k - a[i]] + 1)));
		}
	}

	if (ans == INF) {
		printf("-1\n");
	} else {
		printf("%d\n", ans);
	}
	
	return 0;
}
