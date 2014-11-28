#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int LIM = 33, N = 1111111;

char a[N], b[N];
int n, m, lim;
int f[2][LIM];

int main() {
	freopen("input.txt", "r", stdin);
	while(scanf("%s%s", a + 1, b + 1) == 2) {
		n = strlen(a + 1);
		m = strlen(b + 1);
		scanf("%d", &lim);
		int now = 0, old = 1, ans = -1;
		for(int i = 0; i <= lim; i++)
			f[now][i] = min(m, i);
		if (lim >= m)
			ans = m;
		for(int i = 1; i <= n; i++) {
			swap(now, old);
			for(int j = 0; j <= lim; j++) {
				f[now][j] = j;
				if (j > 0 && f[old][j - 1] + 1 > f[now][j])
					f[now][j] = min(m, f[old][j - 1] + 1);
				if (j > 0 && f[now][j - 1] + 1 > f[now][j])
					f[now][j] = min(f[now][j - 1] + 1, m);
				if (f[old][j] == m || a[i] == b[f[old][j] + 1])
					f[now][j] = max(f[now][j], min(f[old][j] + 1, m));
			}
		}
		if (f[now][lim] < m)
			printf("-1\n"); 
		else {
			while(lim && f[now][lim - 1] >= m)
				lim--;
			printf("%d\n", lim);
		}
	}
	return 0;
} 
