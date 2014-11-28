#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;

long long a[N];
int n, k;

void run() {
	long long mx = a[1];
	for(int i = 2; i <= n; i++) {
		mx = max(mx, a[i]);
	}
	for(int i = 1; i <= n; i++) {
		a[i] = mx - a[i];
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	if (k) {
		run();
		--k;
	}
	k %= 2;
	if (k) {
		run();
		--k;
	}
	for(int i = 1; i <= n; i++) {
		printf("%lld%c", a[i], i == n ? '\n' : ' ');
	}
}
