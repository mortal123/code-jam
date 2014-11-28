#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 2222;

int a[N], b[N];
int n, dp[N][N], from[N][N];

int run() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[i + n] = a[i];
		b[n - i + 1] = a[i];
	}
	memset(from, 0, sizeof(from));
	int ans = 0;
	for(int i = 1; i <= 2 * n; i++) {
		int left = 0;
        int up = 0;
        for (int j = 1; j <= n; ++j) {
            int upleft = INT_MIN;
            if (a[i] == b[j]) {
                upleft = dp[i - 1][j - 1] + 1;
            }
            if (from[i - 1][j]) {
                up++;
            }
            int mm = max(left, max(upleft, up));
            dp[i][j] = mm;
            if (left == mm) {
                from[i][j] = 0;
            } else if (upleft == mm) {
                from[i][j] = 1;
            } else {
                from[i][j] = 2;
            }
            left = mm;
        }
		if (i >= n) {
			int count = 0;
			for(int x = i, y = n; y; ) {
				if (from[x][y] == 1) {
					x--; y--;
					count++;
				} else if (from[x][y] == 0)
					y--;
				else
					x--;
			}
			ans = max(ans, count);
			int x = i - n + 1;
			from[x][0] = 0;
			int y = 0;
			for(; y <= n && from[x][y] == 0; y++);
			for(; x <= i; x++) {
				from[x][y] = 0;
				if (x == i) {
					break;
				}
				for(; y <= n; ++y) {
					if (from[x + 1][y] == 2) {
						break;
					}
					if (y + 1 <= n && from[x + 1][y + 1] == 1) {
						y++;
						break;
					}
				}
			}
		}
	}
	if (n)
		printf("%d\n", ans);
	return n;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for(; run(); );
	return 0;
} 
