#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 111111;

long long a[MAXN], s, ans, now, sum;
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s += a[i];
	}
	s /= n;
	for(int i = 1; i <= n; i++) {
		a[i] -= s;
		a[i] += a[i - 1];
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		ans += abs(a[i] - a[(i + 1) / 2]);
	}
	printf("%lld\n", ans);
	return 0;
}
