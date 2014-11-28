#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

double ans = 1e100;

int a[100];
int n;

void dfs(int dep, int x, int y, int z) {
	if (dep > n) {
		if (x + y >= z && x + z >= y && y + z >= x) {
			double p = (x + y + z) / 2.0;
			ans = min(ans, p * (p - x) * (p - y) * (p - z));
		}
		return;
	}
	dfs(dep + 1, x + a[dep], y, z);
	dfs(dep + 1, x, y + a[dep], z);
	dfs(dep + 1, x, y, z + a[dep]);
	dfs(dep + 1, x - a[dep], y, z);
	dfs(dep + 1, x, y - a[dep], z);
	dfs(dep + 1, x, y, z - a[dep]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	dfs(1, 0, 0, 0);
	printf("%.10f\n", sqrt(ans));
	return 0;
}
