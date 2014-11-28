#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

const int mod = 1000000007;
const int inf = 1000000000;

int f[1 << 24], n, k, a[300], b[300], g[1 << 24], cnt[4], num[1 << 24];
long long per[MAXN];

inline int good(long long x) {
	for(int i = 1; i <= k; i++)
		if (x == b[i])
			return 0;
	return 1;
}

int lowbit(int x){
	return x & (-x);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		g[1 << i] = a[i];
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++) {
		scanf("%d", &b[i]);
	}
	if (k == 2 && b[1] == b[2])
		k--;
	if (k == 2 && b[1] > b[2])
		swap(b[1], b[2]);
		
	for(int i = 1; i <= n; i++)
		per[i] = per[i - 1] * i % mod;
		
	long long tot = 0;
	for(int i = 1; i <= n; i++)
		tot += a[i];
	if (!good(tot)) {
		printf("0\n");
		return 0;
	}
	f[0] = 0; num[0] = 0;
	for(int i = 1; i < (1 << n); i++) {
		int j = lowbit(i);
		f[i] = f[i - j] + g[j];
		num[i] = num[i - j] + 1;
		if (f[i] > inf)
			f[i] = inf + 1;
		if (f[i] == b[1])
			cnt[1] = (cnt[1] + per[num[i]]) % mod;
		if (f[i] == b[2])
			cnt[2] = (cnt[2] + per[num[i]]) % mod;
	}
	ans = per[n];
	if (k >= 1)
		ans -= cnt[1], ans = (ans + mod) % mod;
	if (k >= 2)
		ans -= cnt[2], ans = (ans + mod) % mod;
	return 0;
} 
