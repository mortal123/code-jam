#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 44;

int sum[N][N][N];
int n, p;
char ca[N][N][N], cb[N][N][N];
char buf[N * N * N];

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &p); gets(buf);
		gets(buf);
		for(int i = 1, cnt = 0; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					ca[i][j][k] = buf[cnt++];

		gets(buf);
		for(int i = 1, cnt = 0; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					cb[i][j][k] = buf[cnt++];
					
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++) {
					sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] + sum[i][j][k - 1] - sum[i - 1][j - 1][k] 
						- sum[i - 1][j][k - 1] - sum[i][j - 1][k - 1] + sum[i - 1][j - 1][k - 1] + (ca[i][j][k] == cb[i][j][k]);
				}
		
		int maxSize = -1, cnt = 0;
		
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++)
				for(int k = 1; k <= n; k++)
					for(int r = 1; r <= i && r <= j && r <= k; r++) {
						int ii = i - r, jj = j - r, kk = k - r;
						int tmp = sum[i][j][k] - sum[ii][j][k] - sum[i][jj][k] - sum[i][j][kk] + sum[ii][jj][k] 
								+ sum[ii][j][kk] + sum[i][jj][kk] - sum[ii][jj][kk];
						if (tmp * 100 >= p * (r * r * r)) {
							if (r > maxSize) {
								maxSize = r;
								cnt = 1;
							} else if (r == maxSize) {
								cnt++;
							}
						}
					}
		if (cnt == 0) {
			printf("-1\n");
		} else {
			printf("%d %d\n", maxSize, cnt);
		}
	}
	return 0;
}
