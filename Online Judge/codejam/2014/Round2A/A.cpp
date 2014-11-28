#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int N = 111111;

int n, a[N], limit;

int main() {
	freopen("A-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		scanf("%d %d", &n, &limit);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + n + 1);
		int ans = 0;
		for(int i = n, l = 1; i >= l; i--) {
			if (a[i] + a[l] <= limit) {
				l++;
			} 
			ans++;
		}
		printf("Case #%d: %d\n", ++testCount, ans);
	}
	return 0;
}
 
