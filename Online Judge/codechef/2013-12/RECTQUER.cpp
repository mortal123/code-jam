#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 333;

int sum[11][N][N];

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				for(int k = 0; k <= 10; k++) {
					sum[k][i][j] = sum[k][i - 1][j] + sum[k][i][j - 1] - sum[k][i - 1][j - 1] + (x == k);
				}
			}
		int q;
		scanf("%d", &q);
		while(q--) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			int cnt = 0;
			for(int i = 0; i <= 10; i++) {
				if (sum[i][x2][y2] - sum[i][x1 - 1][y2] - sum[i][x2][y1 - 1] + sum[i][x1 - 1][y1 - 1])
					cnt++;
			}
			printf("%d\n", cnt);
		}
	}
	return 0;
}
