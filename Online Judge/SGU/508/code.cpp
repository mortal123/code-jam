#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 52;

double C[MAXN][MAXN];
int p;
double P[MAXN];

int main() {
	for(int i = 0; i <= 50; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	int n, l, l1, l2;
	double tot = 0;
	scanf("%d %d %d %d", &n, &l1, &l2, &p);
	l = l1 + l2;
	for(int i = 0; i <= n; i++) {
		double pp = 1;
		if (l1 > i || l2 > (n - i)) {
			continue;
		}
		pp = C[i][l1] * C[n - i][l2];
		P[i] = pp;
		tot += pp;
	}
	for(int i = 0; i <= n; i++) {
		P[i] /= tot;
		//printf("%.8lf\n", P[i]);
	}
	for(int len = 1; len <= n + 1; len++)
		for(int i = 0; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			double res = 0;
			for(int k = i; k <= j; k++)
				res += P[k];
			if (i == 1 && j == 26)
				i = 1;
			if ((res + 1e-16) * 100 >= p) {
				printf("%d %d\n", i, j);
				return 0;
			}
		}
	return 0;
} 
