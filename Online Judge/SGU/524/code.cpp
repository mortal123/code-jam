#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 500;

double pos[MAXN];
double ansStart, ansShift, ansTotShift;
int n;

double dis(double a, double b) {
	return fabs(a - b);
}

void Fresh(int s, double d) {
	double tmp = pos[s], now = 0;
	for(int i = s + 1; i <= n; i++) {
		tmp += d;
		now += dis(tmp, pos[i]);
	}
	tmp = pos[s];
	for(int i = s - 1; i >= 1; i--) {
		tmp -= d;
		now += dis(tmp, pos[i]);
	}
	if (now < ansTotShift) {
		ansTotShift = now;
		ansShift = d;
		ansStart = pos[s] - (s - 1) * d;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lf", &pos[i]);
	}
	ansTotShift = 1e100;
	for(int i = 1; i <= n; i++) 
		for(int j = i + 1; j <= n; j++)
			Fresh(i, (pos[j] - pos[i]) / (j - i));
	printf("%.10lf\n", ansTotShift);
	for(int i = 1; i <= n; i++) {
		printf("%.10lf ", ansStart);
		ansStart += ansShift;
	}
	printf("\n");
	return 0;
}
