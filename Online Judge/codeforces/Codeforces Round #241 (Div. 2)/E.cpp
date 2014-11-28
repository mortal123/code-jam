#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 555;
const int INF = 111111111;
int f[N][N], c[N][N];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = INF, c[i][j] = 0;
	for(int i = 1; i <= m; i++) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);
		f[a][b] = f[b][a] = l;
		c[a][b] = c[b][a] = 1;
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k++) {
				if (j != i && j != k && k != i) {
					if (f[j][i] + f[i][k] < f[j][k]) {
						f[j][k] = f[j][i] + f[i][k];
						c[j][k] = c[j][i] + c[i][k];
					} else if (f[j][i] + f[i][k] == f[j][k]) {
						c[j][k] += c[j][i] + c[i][k];
					}
				}
			}
	}
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			printf("%d ", c[i][j]);
	printf("\n");
	return 0;
} 
