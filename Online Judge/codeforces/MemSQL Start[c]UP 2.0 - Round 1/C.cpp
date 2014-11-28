#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
double ans = 0;
int main() {
	scanf("%d %d", &n, &m);
	double  tot = n * m;
	printf("%.12f\n", 1.0 / n + 1.0 * m * (m - 1) * (n - 1) / tot / (tot - 1));
	return 0;
}

