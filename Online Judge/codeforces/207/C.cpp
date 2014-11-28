#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

int a[5], b[5];
int n, sum = 0;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		b[x]++;
		sum += x;
	}
	int ans = -1;
	for(int i = 0; i <= sum; i++) { // four people box
		if (i * 4 > sum)
			continue;
		if ((sum - (i * 4)) % 3 != 0)
			continue;
		int a4 = i, a3 = (sum - (i * 4)) / 3;
		for(int j = 1; j <= 4; j++)
			a[j] = b[j];
		int tmp = 0;
		
		if (a4 > a[4]) {
			a4 -= a[4];
			a[4] = 0;
		} else {
			a[4] -= a4;
			a4 = 0;
			a[1] += a[4];
			a3 -= a[4];
			a[4] = 0;
		}
		
		if (a3 > a[3]) {
			a3 -= a[3];
			a[3] = 0;
		} else {
			a[3] -= a3;
			a3 = 0;
		}
		
		if (a[3]) { // 3 + 1 == 4
			int use = min(min(a[3], a[1]), a4);
			a4 -= use;
			a[3] -= use;
			a[1] -= use;
			tmp += use;
		}
		if (a[3]) {
			a[1] += 3 * a[3];
			a[3] = 0;
		}
		
		// a[3] = 0 a[4] = 0;
		
		if (a4) { // 2 + 2 * 1 == 4
			int use = min(min(a[2], a[1] / 2), a4);
			tmp += 2 * use;
			a4 -= use;
			a[2] -= use;
			a[1] -= 2 * use;
		}
		if (a4) { // 2  2
			int use = min(a[2] / 2, a4);
			tmp += 2 * use;
			a4 -= use;
			a[2] -= 2 * use;
		}
		if (a4) { // 1 1 1 1
			int use = min(a[1] / 4, a4);
			tmp += 3 * use;
			a4 -= use;
			a[1] -= 4 * use;
		}
		
		if (a3) { // 2 1
			int use = min(a3, min(a[2], a[1]));
			tmp += use;
			a3 -= use;
			a[2] -= use;
			a[1] -= use;
		}
		
		if (a3) { // 1 1 1
			int use = min(a3, a[1] / 3);
			tmp += 2 * use;
			a3 -= use;
			a[1] -= 3 * use;
		}
		
		if (a[2])
			a[1] += a[2] * 2, a[2] = 0;
		if (a3) {
			int use = min(a3, a[1] / 3);
			tmp += 2 * use;
			a3 -= use;
			a[1] -= 3 * use;
		}
		if (a4) {
			int use = min(a4, a[1] / 4);
			tmp += 3 * use;
			a4 -= use;
			a[1] -= 4 * use;
		}
		if (a[1] || a[2] || a[3] || a[4] || a3 || a4)
			continue;
		if (ans == -1 || tmp < ans)
			ans = tmp;
	}
	printf("%d\n", ans);
	return 0;
}
