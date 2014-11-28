#include<cstdio>
#include<iostream>

using namespace std;

const int N = 3000 + 10;

int n, m;
int vis[N][N];
int a[N], b[N];

int gcd(int a, int b)
{
	return ! b ? a : gcd(b, a % b);
}

void solve()
{
	cin >> n >> m;
	int c = (2 * n  - 2) * (2  * m - 2) / gcd(2 * n - 2, 2 * m - 2);
	
	int x = 1, y = 1, opt1 = 1, opt2 = 1;
	for(int i = 0; i < c; ++ i) {
		a[i] = x; b[i] = y;
		vis[x][y] = 1;
		if (x == n) opt1 = -1;
		if (y == m) opt2 = -1;
		if (x == 1) opt1 = 1;
		if (y == 1) opt2 = 1;
		x += opt1;
		y += opt2;
	}
	
	int ret = 0, ans = 0;
	int bb = gcd(2 * n - 2, 2 * m - 2);
	
	for(int i = 0; i < c; ++ i) cout << a[i] << ' ';
	cout << endl;
	for(int i = 0; i < c; ++ i) cout << b[i] << ' ';
	cout << endl;
	
	for(int i = 1; i <= n; ++ i)
		for(int j = 1; j <= m; ++ j) {
			if (vis[i][j]) {
				cout << i << ' ' << j << endl;
				++ ret;
			}
			if ((i - j) % bb == 0 || (i + j - 2) % bb == 0) {
				cout << i << ' ' << j << endl;
				++ ans;
			}
		}
	cout << ret << ' ' << ans << endl;
}

int main()
{
	solve();
	return 0;
} 
