#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1111111;

int test;
int a[N], cnt2, cnt3;
long long ans;

int main() {
	scanf("%d", &test);
	while(test--) {
		int n;
	
		ans = cnt2 = cnt3 = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if (a[i] == 2) {
				ans += cnt3;
				cnt2++;
			} else if (a[i] > 2) {
				ans += cnt2 + cnt3;
				cnt3++;
			}
		}
		
		cout << ans << endl;
	}
	return 0;
} 
