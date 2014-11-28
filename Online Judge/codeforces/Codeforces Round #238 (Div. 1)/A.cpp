#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

const int N = 1111;

int n, q;
int mat[N][N];
int main() {
	scanf("%d", &n);
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			scanf("%d", &mat[i][j]);
		ans ^= (mat[i][i] * mat[i][i]);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);
		if (type == 3) {
			printf("%d", ans);
		} else {
			int x;
			scanf("%d", &x);
			ans ^= 1;
		}
	}
	printf("\n");
	return 0;
}
