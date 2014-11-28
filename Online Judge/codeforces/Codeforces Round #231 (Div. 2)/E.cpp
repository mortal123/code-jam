#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;

int a[N], b[N], n;

int main() {
	scanf("%d", &n);
	double x, y;
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i], &b[i]);
		x += a[i];
		y += b[i];
	}
	
	x /= n;
	y /= n;
	
	double ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += (x - a[i]) * (x - a[i]);
		ans += (y - b[i]) * (y - b[i]);
	}
	
	printf("%.10lf\n", ans);
	return 0;
}
