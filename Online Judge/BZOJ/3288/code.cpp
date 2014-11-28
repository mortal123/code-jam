#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 12;

int mat[MAXN + 10][MAXN + 10];
int ans = 0, visit[MAXN], a[MAXN + 10];

void dfs(int dep, int tar, int now) {
	if (tar < dep) {
		int cnt = 0;
		for(int i = 1; i <= tar; i++)
			for(int j = i + 1; j <= tar; j++)
				if (a[i] > a[j])
					cnt++;
		if (cnt % 2 == 0)
			ans += now;
		else
			ans -= now;
		return;
	}
	for(int i = 1; i <= tar; i++) {
		if (visit[i])
			continue;
		a[dep] = i;
		visit[i] = 1;
		dfs(dep + 1, tar, now * mat[dep][i]);
		visit[i] = 0;
	}
}

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	for(int i = 1; i <= MAXN; i++)
		for(int j = 1; j <= MAXN; j++)
			mat[i][j] = gcd(i, j);
	for(int i = 1; i <= MAXN; i++) {
		ans = 0;
		dfs(1, i, 1);
		printf("%d: %d\n", i, ans);
	}
	return 0;
}
