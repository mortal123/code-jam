#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char map[111][111];
int d[111][111];
int dx[8] = {1, -1, 1, -1, -1, 1, 0, 0};
int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

int dfs(int r, int c, int x, int y) {
	int ret = 1;
	if (d[x][y] != 0) {
		d[x][y] = -1;
		return ret;
	}
	
	d[x][y] = -1;
	for(int k = 0; k < 8; k++) {
		int xx = x + dx[k];
		int yy = y + dy[k];
		if (xx < 1 || xx > r || yy < 1 || yy > c || map[xx][yy] == '*')
			continue;
		if (d[xx][yy] != -1) {
			ret += dfs(r, c, xx, yy);
		}
	}
	
	return ret;
}

int check(int r, int c) {
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++) {
			d[i][j] = 0;
		}
	int cnt = 0;
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++) {
			cnt += (map[i][j] != '*');
			for(int k = 0; k < 8; k ++) {
				int x = i + dx[k];
				int y = j + dy[k];
				if (x < 1 || x > r || y < 1 || y > c)
					continue;
				if (map[x][y] == '*')
					d[i][j]++;
			}
		}
	if (cnt > dfs(r, c, 1, 1))
		return 0;
	return 1;
}

int solveh(int r, int c, int h, int tot) {
	for(int j = 1; j <= c; j++) 
		for(int i = 1; i <= r; i++) {
			if (i <= h && tot) {
				if (i == 1 && j == 1) {
					map[i][j] = 'c';
				} else {
					map[i][j] = '.';
				}
				tot--;
			} else {
				map[i][j] = '*';
			}
		}
	if (tot)
		return 0;
	if (!check(r, c))
		return 0;
	return 1;
}


int solvew(int r, int c, int w, int tot) {
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++) {
			if (j <= w && tot) {
				if (i == 1 && j == 1) {
					map[i][j] = 'c';
				} else {
					map[i][j] = '.';
				}
				tot--;
			} else {
				map[i][j] = '*';
			}
		}
	if (tot)
		return 0;
	if (!check(r, c))
		return 0;
	return 1;
}

void print(int r, int c) {
	return ;
		 	for(int i = 1; i <= r; i++) {
		 		for(int j = 1; j <= c; j++)
		 			printf("%c", map[i][j]);
		 		printf("\n");
			 }
}

int main() {
	freopen("C-small-attempt4.in", "r", stdin);
	//freopen("C-small-attempt3.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		//printf("Case #%d:\n", ++testCount);
		int r, c, m;
		scanf("%d %d %d", &r, &c, &m);
		 m = r * c - m;
		 if (m == 1) {
		 	solvew(r, c, 1, m);
		 	print(r, c);
		 	continue;
		 }
		 if (r == 1) {
		 	solveh(r, c, 1, m);
		 	print(r, c);
		 	continue;
		 }
		 if (c == 1) {
		 	solvew(r, c, 1, m);
		 	print(r, c);
		 	continue;
		 }
		 
		 if (m <= 3 || m == 5 || m == 7) {
		 	//printf("%d %d %d\n", r, c, m);
		 	//printf("Impossible\n");
		 	continue;
		 }
		 
		 for(int i = 1; i <= r; i++)
		 	for(int j = 1; j <= c; j++) {
		 		if (i * j + m == r * c && i + 1 < r && j + 1 < c) {
		 			
		 		}
		 	}
		 
		 bool flag = false;
		 if (m == 4) {
		 	solvew(r, c, 2, m);
		 	flag = true;
		 } else if (m == 6) {
		 	if (r >= 3) {
		 		solvew(r, c, 3, m);
		 	} else {
		 		solvew(r, c, 2, m);
		 	}
		 	flag = true;
		 } 
		 for(int w = 2; flag == false && w <= m && w <= c; w++) {
		 	if (solvew(r, c, w, m))
		 		flag = true;
		 }
		 
		 for(int h = 2; flag == false && h <= m && h <= r; h++) {
		 	if (solveh(r, c, h, m))
		 		flag = true;
		 }
		 if (!flag) {
		 	 printf("%d %d %d\n", r, c, m);
		 	//printf("Impossible\n");
		 } else {
		 	print(r, c);
		 }
	}
	return 0;
}
