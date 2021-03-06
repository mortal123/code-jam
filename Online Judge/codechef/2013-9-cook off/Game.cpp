#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111111;
const int MOD = int(1e9 + 7);

long long ans = 0;
long long a[N], tot, mm;
long long n, m, k;

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> m >> k;
	tot = 0;
	mm = 0;
	for(int i = 1; i <= n; i++) {
		long long x;
		cin >> x;
		a[i] = (m - x) / k + 1;
		tot += a[i];	
		mm = max(mm, a[i]);
	}
	tot -= mm;
	if (tot % 2 == 0) {
		ans = mm / 2 + 1;
	} else {
		ans = (mm + 1) / 2;
	}
	cout << ans % MOD << endl;
	return 0;	
} 
