#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

long long n, m, v, k;

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		cin >> n >> m >> v >> k;
		int ans = 0;
		while(ans <= 100 && m < n && m > v) {
			m = (m - v) * k;
			ans++;
		}
		if (ans > 100 || m < n) {
			printf("-1\n");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
} 
