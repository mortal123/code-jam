#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 110;

int area;
char map[MAXN][MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i <= n + 1; i++)
		for(int j = 0; j <= m + 1; j++)
			map[i][j] = '0';
	for(int i = 1; i <= n; i++) {
		scanf("%s", map[i] + 1);
		map[i][m + 1] = '0';
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if (map[i][j] == '0')
				continue;
			area += 2;
			for(int k = -1; k <= 1; k++)
				for(int l = -1; l <= 1; l++) {
					if (abs(k + l) != 1)
						continue;
					if (map[i][j] > map[i + k][j + l])
						area += map[i][j] - map[i + k][j + l];
				}
		}
	printf("%d\n", area);
	return 0;
}
