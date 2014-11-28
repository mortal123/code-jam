#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 50;

long long trans[3][3];
long long f[N][3][3];

int main() {
	freopen("input.txt", "r", stdin);
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			scanf("%I64d", &trans[i][j]);
			f[0][i][j] = 0;
		}
	}
	
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		if (i == 5)
			i = 5;
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++) {
				if (j == k) {
					f[i][j][k] = 0;
					continue;
				}
				
				f[i][j][k] = (1LL << 60);
				for(int l = 0; l < 3; l++) {
					if (l == j || l == k)
						continue;
					f[i][j][k] = min(f[i - 1][j][k] + trans[j][l] + f[i - 1][k][j] + trans[l][k] + f[i - 1][j][k], f[i - 1][j][l] + trans[j][k] + f[i - 1][l][k]);
				}
			}
		
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				for(int l = 0; l < 3; l++)
					f[i][k][l] = min(f[i][k][l], f[i][k][j] + f[i][j][l]);
	}
	
	printf("%I64d\n", f[n][0][2]);
	
	return 0;
} 
