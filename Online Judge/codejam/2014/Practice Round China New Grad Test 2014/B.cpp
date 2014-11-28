#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const double g = 9.8;
double v, d;

int main() {
	freopen("B-small-attempt1.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int Test;
	scanf("%d", &Test);
	for(int test = 1; test <= Test; test++) {
		scanf("%lf %lf", &v, &d);
		double ss = 0.5 * g * d / v / v;
		ss *= 2;
		ss = asin(min(1.0, ss));
		ss /= 2;
		printf("Case #%d: %.8lf\n", test, ss / acos(-1.0) * 180);
	}
	return 0;
}
