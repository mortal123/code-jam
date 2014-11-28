#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 111;
const double eps = 1e-9;

int a[N], n;
double f[N][N];
int power[N], calc[N][N];

inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	for(int i = 0; i <= 100; i++)
		for(int j = 0; j <= 100; j++)
			calc[i][j] = gcd(i, j);
			
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		for(int i = 1; i <= 100; i++) {
			power[i] = 0;
			for(int j = 1; j <= n; j++) {
				if (a[j] % i == 0) {
					power[i]++;
				}
			}
		}
		
		for(int i = 1; i <= 100; i++) {
			if (i == 1) {
				f[n][i] = 1;
			} else {
				f[n][i] = 0;
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			for(int j = 0; j <= 100; j++) {
				f[i][j] = 0;
				if (j != 1) {
					if (power[j] > i) {
						f[i][j] = max(f[i][j], 1 - f[i + 1][j]);
					}
					for(int k = 1; k <= n; k++) {
						if (j == 0 || a[k] % j != 0)
							f[i][j] = max(f[i][j], 1 - f[i + 1][calc[a[k]][j]]);
					}
				} else {
					f[i][j] = 1;
				}
			}
		}
		printf("%d ", (int)(f[0][0] + eps));
		for(int i = 1; i <= 100; i++) {
			if (i == 1) {
				f[n][i] = 1;
			} else {
				f[n][i] = 0;
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			for(int j = 0; j <= 100; j++) {
				f[i][j] = 0;
				if (j != 1) {
					double lef = n - i;
					if (power[j] > i) {
						f[i][j] += (1 - f[i + 1][j]) / lef * (power[j] - i);
					}
					for(int k = 1; k <= n; k++) {
						if (j == 0 || a[k] % j != 0)
							f[i][j] += (1 - f[i + 1][calc[a[k]][j]]) / lef;
					}
				} else {
					f[i][j] = 1;
				}
			}
		}
		printf("%.4f\n", f[0][0] + eps);
	}
}
