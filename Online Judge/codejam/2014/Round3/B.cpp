#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int INF = 1111111111;
const int LIMIT = 2000;
const int N = 111;

int p, q, n;
int h[N], g[N];
int f[N][LIMIT + 1][2];
int result[222][22][2];

int getDP(int hp, int paused, int who) {
	if (paused < 0)
		return 2;
	if (hp <= 0 && paused > 0)
		return 2;
	if (hp <= 0) {
		return (who ^ 1);
	}
	if (result[hp][paused][who] != -1)
		return result[hp][paused][who];
	int &res = result[hp][paused][who];
	res = 0;
	if (who == 0) {
		res = min(getDP(hp, paused - 1, 1), getDP(hp - p, paused, 1));
	} else {
		res = getDP(hp - q, paused, 0);
	}
	return res;
}

int fresh(int &a, int b) {
	a = max(a, b);
}

int main() {
	freopen("B-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		scanf("%d %d %d", &p, &q, &n);
		memset(result, -1, sizeof(result));
		for(int i = 1; i <= n; i++) {
			scanf("%d %d", &h[i], &g[i]);
		}
		for(int i = 0; i <= n + 1; i++)
			for(int j = 0; j <= LIMIT; j++)
				for(int k = 0; k < 2; k++)
					f[i][j][k] = -INF;
		f[1][0][0] = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= LIMIT; j++)
				for(int k = 0; k < 2; k++) {
					if (f[i][j][k] < 0)
						continue;
					for(int used = 0; used <= j; used++) {
						int cur = h[i] - p * used;
						if (cur <= 0) {
							fresh(f[i + 1][j - used][k], f[i][j][k] + g[i]);
							break;
						}
						
						for(int paused = 0; ; paused++) {
							int r = getDP(cur, paused, k);
							if (r == 2)
								break;
							if (r == 0) {
								fresh(f[i + 1][j - used + paused][1], f[i][j][k] + g[i]);
							} else {
								fresh(f[i + 1][j - used + paused][0], f[i][j][k]);
							}
						}
					}
				}
		int ans = 0;
		for(int i = 0; i <= LIMIT; i++)
			for(int j = 0; j < 2; j++)
				ans = max(ans, f[n + 1][i][j]);
		printf("Case #%d: %d\n", ++testCount, ans);
	}
	return 0;
} 
