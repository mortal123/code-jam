#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream> 
using namespace std;

const int N = 555555;

int a[N], n, m, b[N], tot;

int main() {
	scanf("%d", &n);
	tot = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		while(tot >= 2) {
			if (a[tot - 1] >= a[tot] && a[tot] >= x) {
				ans += x;
				tot--;
			} else if (a[tot - 1] <= a[tot] && a[tot] <= x) {
				ans += b[tot - 1];
				b[tot - 1] = a[tot];
				tot--;
			} else if (a[tot - 1] >= a[tot] && a[tot] <= x) {
				ans += min(a[tot - 1], x);
				tot--;
			} else {
				break;
			}
		}
		a[++tot] = x;
		b[tot] = x;
	}
	if (tot == 3) {
		ans += min(a[1], a[3]);
	}
	cout << ans << endl;
	return 0;
}
