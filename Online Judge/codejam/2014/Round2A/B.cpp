#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int N = 1111;

int n;
int a[N];

int main() {
	freopen("B-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		int ans = 0;
		int nn = n;
		for(int i = 1; i <= nn; i++) {
			int pos = -1;
			for(int j = 1; j <= n; j++) {
				if (pos == -1 || a[pos] > a[j]) {
					pos = j;
				}
			}
			ans += min(pos - 1, n - pos);
			for(int j = pos; j < n; j++) {
				a[j] = a[j + 1];
			}
			n--;
		}
		static int testCount = 0;
		printf("Case #%d: %d\n", ++testCount, ans);
	}
	return 0;
}
 
