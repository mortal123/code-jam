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

int f[1 << 24], n, k, a[300], b[300];

inline int good(long long x) {
	for(int i = 1; i <= k; i++)
		if (x == b[i])
			return 0;
	return 1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &k);
	for(int i = 1; i <= k; i++) {
		scanf("%d", &b[i]);
	}
	long long tot = 0;
	for(int i = 1; i <= n; i++)
		tot += a[i];
	if (!good(tot)) {
		printf("0\n");
		return 0;
	}
	
	long long ans = 0;
	f[0] = 1;
	for(int i = 0; i < (1 << n); i++) {
		int flag = 1; int sum = 0;
		for(int j = 0; j < n; j++)
			if ((1 << j) & i) {
				sum += a[j];
				if (sum > inf) {
					sum = -1;
					break;
				}
			}
		if (!good(sum))
			continue;
		for(int j = 0; j < n; j++)
			if (!((1 << j) & i)) {
				f[(1 << j) | i] += f[i];
				if (f[(1 << j) | i] >= mod)
					f[(1 << j) | i] -= mod;
			}
	}
	cout << f[(1 << n) - 1] << endl;
	return 0;
} 
