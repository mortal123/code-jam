#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int p1 = 103, p2 = 47;
//const long long mod = 1000000009;

const int MAXN = 800;

int left[MAXN][MAXN], right[MAXN][MAXN], up[MAXN][MAXN];
int hash[MAXN][MAXN], mi1[MAXN], mi2[MAXN];
int mat[MAXN][MAXN];
char buf[MAXN];
int n, m;

int check(int r, int print = 0) {
	if (!r)
		return 1;
	for(int i = 1; i <= n; i++) {
		long long res = 0;
		for(int j = m; j >= m - r + 2; j--) {
			res = res * p1 + mat[i][j];
		}
		for(int j = m - r + 1; j >= 1; j--) {
			res = res * p1 + mat[i][j];
			hash[i][j] = res;
			res -= mi1[r - 1] * mat[i][j + r - 1];
		}
	}
	for(int i = 1; i <= m - r + 1; i++) {
		long long res = 0;
		for(int j = n; j >= n - r + 2; j--) {
			res = res * p2 + hash[j][i];
		}
		for(int j = n - r + 1; j >= 1; j--) {
			res = res * p2 + hash[j][i];
			left[j][i] = res;
			res -= mi2[r - 1] * hash[j + r - 1][i]; 
		}
	}
	for(int i = 1; i <= m - r + 1; i++) {
		long long res = 0;
		for(int j = 1; j < r; j++) {
			res = res * p2 + hash[j][i];
		}
		for(int j = r; j <= n; j++) {
			res = res * p2 + hash[j][i];
			up[j][i] = res;
			res -= mi2[r - 1] * hash[j - r + 1][i];
		}
	}
	for(int i = 1; i <= n; i++) {
		long long res = 0;
		for(int j = 1; j < r; j++) {
			res = res * p1 + mat[i][j];
		}
		for(int j = r; j <= m; j++) {
			res = res * p1 + mat[i][j];
			hash[i][j] = res;
			res -= mi1[r - 1] * mat[i][j - r + 1];
		}
	}
	for(int i = r; i <= m; i++) {
		long long res = 0;
		for(int j = n; j >= n - r + 2; j--) {
			res = res * p2 + hash[j][i];
		}
		for(int j = n - r + 1; j >= 1; j--) {
			res = res * p2 + hash[j][i];
			right[j][i] = res;
			res -= mi2[r - 1] * hash[j + r - 1][i];
		}
	}
	for(int i = 1; i <= n - r + 1; i++)
		for(int j = 1; j <= m - r + 1; j++) {
			if (left[i][j] == right[i][j + r - 1] && left[i][j] == up[i + r - 1][j]) {
				if (print) {
					printf("%d %d %d %d\n", i, j, i + r - 1, j + r - 1);
				}
				return 1;
			}
		}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	mi1[0] = mi2[0] = 1;
	for(int i = 1; i <= 750; i++)
		mi1[i] = mi1[i - 1] * p1, mi2[i] = mi2[i - 1] * p2;
		
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", buf + 1);
		for(int j = 1; j <= m; j++)
			mat[i][j] = buf[j] - 'a' + 1;
	}
	if (min(n, m) == 1) {
		printf("1 1 1 1\n");
		return 0;
	}
	int l = 0, r = min(n, m) / 2, mid;
	if (r * 2 + 1 > min(n, m))
		r--;
	while(l < r) {
		mid = (l + r) / 2 + 1;
		if (check(2 * mid + 1))
			l = mid;
		else
			r = mid - 1;
	}
	int now = l * 2 + 1;
	l = 0, r = min(n, m) / 2;
	while(l < r) {
		mid = (l + r) / 2 + 1;
		if (check(2 * mid)) 
			l = mid;
		else
			r = mid - 1;
	}
	now = max(now, 2 * l);
	check(now, 1);
	return 0;
}
