#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111111;

int n, k;
long long a[N], sum[N], lMax[N];
int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			sum[i] = sum[i - 1] + a[i];
		}
		
		long long cur = sum[n];
		for(int i = n; i >= 1; i--) {
			cur = max(cur, sum[i]);
			lMax[i] = cur;
		}
		
		long long pMin = 0, ans = -(1LL << 60);
		
		cur = a[1];
		for(int i = 1; i + k < n; i++) {
			cur = max(cur, sum[i] - pMin);
			ans = max(ans, cur + lMax[i + k + 1] - sum[i + k]);
			pMin = min(pMin, sum[i]);
		}
		
		cout << ans << endl;
	}
	
	return 0;
}
