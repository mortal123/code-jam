#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 3333;
const long long INF = (1LL << 60);
long long p[N], f[2][N][2];
int n, times;

int main() {
	scanf("%d %d", &n, &times);
	for(int i = 1; i <= n; i++) {
		scanf("%I64d", &p[i]);
	}	
	
	for(int i = 0; i < 2; i++)
		for(int j = 0; j <= times; j++)
			for(int k = 0; k < 2; k++)
				f[i][j][k] = -INF;
	
	long long ans = 0;
	f[0][0][0] = 0;
	for(int i = 0; i < n; i++) {
		int cur = i % 2, last = (i + 1) % 2;
		for(int j = 0; j <= times; j++)
			for(int k = 0; k < 2; k++)
				f[last][j][k] = -INF;
		
		for(int j = 0; j <= times; j++)
			for(int k = 0; k < 2; k++) {
				f[last][j][k] = max(f[last][j][k], f[cur][j][k]);
				if (k == 0 && j < times) {
					f[last][j + 1][1] = max(f[last][j + 1][1], f[cur][j][k] - p[i + 1]);
				} else if (k == 1) {
					f[last][j][0] = max(f[last][j][0], f[cur][j][k] + p[i + 1]);
				}
			}
	}
	
	for(int i = 0; i <= times; i++)
		ans = max(ans, f[n % 2][i][0]);
		
	printf("%I64d\n", ans);
	return 0;
} 
