#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

const int N = 5555, M = 111;

int num[2][M];
int n, m;
int res[N][2];

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int c;
		scanf("%d", &c);
		num[0][c] ++;
		num[1][c] ++;
	}
	
	int ans = 0;
	
	for(int i = 1; i <= n; i++) {
		int l = -1;
		for(int j = 1; j <= m; j++) {
			if (num[0][j] == 0)
				continue;
			if (l == -1 || num[0][j] > num[0][l])
				l = j;
		}
		
		int r = -1;
		for(int j = 1; j <= m; j++) {
			if (num[1][j] == 0 || j == l)
				continue;
			if(r == -1 || num[1][j] > num[1][r])
				r = j;
		}
		
		if (r == -1) {
			res[i][0] = res[i][1] = l;
			num[0][l]--;
			num[1][l]--;
		} else {
			ans++;
			res[i][0] = l;
			res[i][1] = r;
			num[0][l]--;
			num[1][r]--;
		}
	}
	
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++) {
		printf("%d %d\n", res[i][0], res[i][1]);
	}
	return 0;
} 
