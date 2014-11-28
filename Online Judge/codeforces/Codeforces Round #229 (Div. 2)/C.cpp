#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111, K = 11;

int sumk[N], sum[N];
int a[N], n, q, k;
char str[N];

int main() {
	scanf("%d %d %d", &n, &k, &q);
	scanf("%s", str + 1);
	for(int i = 1; i <= n; i++) {
		a[i] = (str[i] == '1');
		sumk[i] = a[i];
		if (i > k) {
			sumk[i] += sumk[i - k];
		}
		
		sum[i] = a[i] + sum[i - 1];
	}
	
	for(int i = 1; i <= q; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		int ans = 0, totk = (r - l + 1) / k;
		ans = totk - (sumk[r] - sumk[l - 1]);
		ans += (sum[r] - sum[l - 1]) - (sumk[r] - sumk[l - 1]);
		printf("%d\n", ans);
	}
	return 0;
} 
