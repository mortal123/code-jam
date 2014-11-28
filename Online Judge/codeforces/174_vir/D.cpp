#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 210000;

long long a[MAXN], flag[MAXN];
long long sum[MAXN];
int q[MAXN], n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	memset(flag, 0, sizeof(flag));
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		scanf("%I64d", &a[i]);
	}
	for(int i = 2; i <= n; i++) {
		if (flag[i])
			continue;
		int x = i, top = 0;
		while(!flag[x]) {
			q[++top] = x;
			flag[x] = 2;
			x = a[x] + x;
			if (x > n)
				break;
			x -= a[x];
			if (x <= 0)
				break;
		}
		if (x >= 1 && x <= n && (sum[x] == -1 || flag[x] == 2)) {
			for(int j = 1; j <= top; j++)
				sum[q[j]] = -1;
			continue;
		}
		for(int j = 1; j <= top; j++)
			flag[q[j]] = 1;
		if (x <= 0 || x > n)
			q[++top] = n + 1;
		else
			q[++top] = x;

		for(int j = top - 1; j >= 1; j--) {
			int x = q[j];
			sum[x] = sum[q[j + 1]];
			sum[x] += a[x];
			x += a[x];
			if (x <= 0 || x > n)
				continue;
			sum[x] += a[x];
			x -= a[x];
		}
	}
	for(int i = 1; i < n; i++) {
		long long ans = 0;
		int x = 1;
		a[1] = i;
		ans += a[1];
		x += a[1];
		ans += a[x];
		x -= a[x];
		if (x <= 0 || x > n)
			printf("%I64d\n", ans);
		else if (x == 1)
			printf("-1\n");
		else {
			if (sum[x] == -1)
				printf("-1\n");
			else
				printf("%I64d\n", ans + sum[x]);
		}
	}
	return 0;
} 
