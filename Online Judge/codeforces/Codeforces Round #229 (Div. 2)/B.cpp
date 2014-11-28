#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;

int a[N], b[N];
long long ans = 0;

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		if (2 * a[i] < b[i] || b[i] < 2) {
			ans--;
		} else {
			ans += 1LL * (b[i] / 2) * (b[i] - b[i] / 2);
		}
	}
	
	printf("%I64d\n", ans);
	return 0;
} 
