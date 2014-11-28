#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1111;

bool vis[N][N];
int up[N], left[N], right[N];
int ans[N][N], wide[N][N];

int n, m, k;
pair<int, int> stack[N];

int fresh(int &a, int b) {
	a = max(a, b);
}

int main() {
	freopen("input.txt", "r", stdin);
	
	memset(vis, false, sizeof(vis));
	
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		vis[x][y] = true;
	}
	
	for(int i = 1; i <= n; i++) {
		if (i == 4) {
			i = 4;
		}
		int top = 0;
		for(int j = 1; j <= m; j++) {
			up[j]++;
			if (vis[i][j])
				up[j] = 0;
		}
		
		stack[top = 1] = make_pair(0, 0);
		
		for(int j = 1; j <= m; j++) {
			while(top && stack[top].second >= up[j])
				top--;
			left[j] = stack[top].first;
			stack[++top] = make_pair(j, up[j]);
		}
		
		stack[top = 1] = make_pair(m + 1, 0);
		
		for(int j = m; j >= 1; j--) {
			while(top && stack[top].second >= up[j])
				top--;
			right[j] = stack[top].first;
			stack[++top] = make_pair(j, up[j]);
		}
		
		for(int j = 1; j <= m; j++) {
			fresh(wide[i - up[j] + 1][i], (right[j] - left[j] - 1));
		}
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = n; j >= i; j--) {
			wide[i][j] = max(wide[i][j], wide[i][j + 1]);
		}
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			wide[i][j] = max(wide[i - 1][j], wide[i][j]);
		}
	
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++) {
			ans[i][j] = (j - i + 1) * wide[i][j];
		}
	
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			fresh(ans[i][j + 1], ans[i][j]);
	
	for(int i = 1; i <= n; i++)
		for(int j = i; j >= 1; j--)
			fresh(ans[j - 1][i], ans[j][i]);
	
	int q;
	scanf("%d", &q);
	while(q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", ans[l][r]);
	}
	
	return 0;
}

/*
**xx*
x**x*
*x***
*****
*****
*/
