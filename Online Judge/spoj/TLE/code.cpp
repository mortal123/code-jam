#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 50, M = 15;

const int MOD = 1000000000;
int f[2][1 << M], sum[1 << M];
int n, m, c[N], pos[1 << M];
int lowbit[1 << M];

inline void add(int &a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD; 
}

int main() {
	freopen("input.txt", "r", stdin);
	for(int i = 0; i < (1 << M); i++) {
		lowbit[i] = ((-i) & i);
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) {
			scanf("%d", &c[i]);
		}
		fill(f[0], f[0] + (1 << m), 0);
		f[0][0] = 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < (1 << m); j++) {
				f[1][j] = f[0][j];
				if (j) {
					add(f[1][j], f[1][j ^ lowbit[j]]);
					add(f[1][j], sum[lowbit[j]]);
					add(sum[lowbit[j]], f[1][j]);
				}
			}
			for(int j = 0; j < (1 << m); j++) {
				f[0][j] = f[1][((1 << m) - 1) ^ j];
				sum[j] = 0; 
			}
			for(int j = 0; j < (1 << m); j += c[i])
				f[0][j] = 0;
		}
		int ans = 0;
		for(int i = 0; i < (1 << m); i++)
			add(ans, f[0][i]);
		printf("%d\n", ans);
	}		
	for(int i = 0; i < m; i++)
		for(int j = 0; j < (1 << m); j++)
			if () 
	return 0;
} 
