#include <cstdio>
#include <cstdlib> 
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 111111;

int n, l, r, ql, qr;
int a[N], sum[N];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d %d %d", &n, &l, &r, &ql, &qr);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	long long ans = 1LL << 60;
	for(int i = 0; i <= n; i++) {
		int L = i, R = n - i;
		long long tmp = 0;
		tmp = (long long)l * sum[i] + (long long)r * (sum[n] - sum[i]);
		tmp += 1LL * ql * max(0, (L - R - 1)) + 1LL * qr * max((R - L - 1), 0);
		ans = min(ans, tmp);
	}
	cout << ans << endl;
	return 0;
}
