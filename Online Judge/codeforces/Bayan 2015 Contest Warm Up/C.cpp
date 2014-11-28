#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1111;

int n, m, nn, mm;
int sx, sy, visit[N][N];
char map[N][N];

void full(int x, int y, int xx, int yy) {
	for(int i = x; i <= xx; i++)
		for(int j = y; j <= yy; j++) {
			visit[i][j] = 1;
		}
}

bool solve(int nn, int mm) {
	memset(visit, 0, sizeof(visit));
	int x = sx, y = sy;
	if (x + nn - 1 >= n || y + mm - 1 >= m) {
		return false;
	}
	full(x, y, x + nn - 1, y + mm - 1);
	while(1) {
		if (x + nn < n && map[x + nn][y] == 'X') {
			full(x + nn, y, x + nn, y + mm - 1);
			x++;
		} else if (y + mm < m && map[x][y + mm] == 'X') {
			full(x, y + mm, x + nn - 1, y + mm);
			y++;
		} else {
			break;
		}
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			if (visit[i][j] != (map[i][j] == 'X')) {
				return false;
			}
		}
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	sx = -1, sy = -1;
	for(int i = 0; i < n; i++) {
		scanf("%s", map[i]);
		for(int j = 0; j < m; j++) {
			if (map[i][j] == 'X' && sx == -1) {
				sx = i;
				sy = j;
			}
		}
	}
	
	if (solve(1, 1)) {
		printf("1\n");
	} else {
		nn = n + 1, mm = m + 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0, k = 0; j < m; j = k) {
				if (map[i][j] != 'X') {
					k = j + 1;
					continue;
				}
				for(k = j; k < m && map[i][k] == 'X'; k++);
				mm = min(mm, k - j);
			}
		}
		for(int i = 0; i < m; i++) {
			for(int j = 0, k; j < n; j = k) {
				if (map[j][i] != 'X') {
					k = j + 1;
					continue;
				}
				for(k = j; k < n && map[k][i] == 'X'; k++);
				nn = min(nn, k - j);
			}
		}
		int answer = n * m + 1;
		if (solve(1, mm)) {
			answer = min(answer, mm);
		}
		if (solve(nn, 1)) {
			answer = min(answer, nn);
		}
		if (solve(nn, mm)) {
			answer = min(answer, nn * mm);
		}
		for(int i = 1; i < mm; i++) {
			if (nn * i <= answer && solve(nn, i)) {
				answer = min(answer, nn * i);
			}
		}
		for(int i = 1; i < nn; i++) {
			if (mm * i <= answer && solve(i, mm)) {
				answer = min(answer, i * mm);
			}
		}
		if (answer > n * m) {
			puts("-1");
		} else {
			printf("%d\n", answer);
		}
	}
	
	return 0;
}

