#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 16;
const int inf = 1000000000;

int knight[] = {-2, -1, 1, 2};
int n, m, c;
char map[MAXN][MAXN];
int hash[MAXN][MAXN], inQueue[MAXN][MAXN], danger[MAXN][MAXN];
int sx, sy, f[1 << 16][MAXN][MAXN];

struct Node {
	int v, x, y;
	Node(int v, int x, int y) : v(v), x(x), y(y) {}
	Node() {}
	friend bool operator <(const Node &a, const Node &b) {
		return a.v < b.v;
	}
};

struct Piece {
	int x, y;
	string name;
	Piece(int x, int y, string name) : x(x), y(y), name(name) {}
	void attack(int danger[MAXN][MAXN], int map[MAXN][MAXN]) {
		if (name == "rook") {
			for(int dx = -1; dx <= 1; dx++)
				for(int dy = -1; dy <= 1; dy++) 
					if (dx + dy == 1 || dx + dy == -1) {
						for(int i = 1; ; i++) {
							int xx = x + dx * i, yy = y + dy * i;
							if (xx > n || xx < 1 || yy < 1 || yy > m)
								break;
							danger[xx][yy]++;
							if (map[xx][yy])
								break;
						}
					}
		} else if (name == "knight") {
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 4; j++) {
					if (abs(knight[i]) + abs(knight[j]) != 3)
						continue;
					int xx = x + knight[i], yy = y + knight[j];
					if (xx > n || xx < 1 || yy < 1 || yy > m)
						continue;
					danger[xx][yy]++;
				}
		} else if (name == "bishop") {
			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					if (abs(i) + abs(j) == 2) {
						for(int k = 1; ; k++) {
							int xx = x + k * i, yy = y + k * j;
							if (xx > n || xx < 1 || yy < 1 || yy > m)
								break;
							danger[xx][yy]++;
							if (map[xx][yy])
								break;						
						}
					}
		}
	}
};

vector<Piece> pieces;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", map[i] + 1);
		for(int j = 1; j <= m; j++) {
			if (map[i][j] == '*') {
				sx = i, sy = j;
			} else if (map[i][j] != '.') {
				if (map[i][j] == 'K')
					pieces.push_back(Piece(i, j, "knight"));
				else if (map[i][j] == 'B')
					pieces.push_back(Piece(i, j, "bishop"));
				else if (map[i][j] == 'R') 
					pieces.push_back(Piece(i, j, "rook"));
			}
		}
	}
	c = pieces.size();
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k < (1 << c); k++)
				f[k][i][j] = inf;
	f[(1 << c) - 1][sx][sy] = 0;
	for(int i = (1 << c) - 1; i >= 0; i--) {
		priority_queue<Node> q;
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= m; k++)
				inQueue[j][k] = 0, danger[j][k] = 0, hash[j][k] = 0;
		for(int k = 0; k < c; k++)
			if ((1 << k) & i)
				hash[pieces[k].x][pieces[k].y] = k + 1;
		for(int k = 0; k < c; k++)
			if ((1 << k) & i)
				pieces[k].attack(danger, hash);
		/*
		for(int j = 1; j <= n; j++, printf("\n"))
			for(int k = 1; k <= m; k++)
			printf("%d", danger[j][k]);
		printf("\n");
		*/
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= m; k++)
				q.push(Node(-f[i][j][k], j, k));
		while(!q.empty()) {
			Node tmp = q.top();
			q.pop();
			if (inQueue[tmp.x][tmp.y] || f[i][tmp.x][tmp.y] > inf / 2)
				continue;
			inQueue[tmp.x][tmp.y] = 1;
			for(int j = -1; j < 2; j++)
				for(int k = -1; k < 2; k++) {
					if (j == 0 && k == 0)
						continue;
					int x = tmp.x + j, y = tmp.y + k;
					if (danger[x][y] != 0 || x < 1 || x > n || y < 1 || y > m)
						continue;
					if (f[i][tmp.x][tmp.y] + 1 < f[i][x][y]) {
						f[i][x][y] = f[i][tmp.x][tmp.y] + 1;
						q.push(Node(-f[i][x][y], x, y));
					}
				}
		}
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= m; k++) {
				if (hash[j][k] && (i & (1 << (hash[j][k] - 1)))) {
					f[i - (1 << (hash[j][k] - 1))][j][k] = min(f[i - (1 << (hash[j][k] - 1))][j][k], f[i][j][k]);
				}
			}
	}
	int ans = inf;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if (f[0][i][j] < ans)
				ans = f[0][i][j];
	if (ans > inf / 2)
		printf("-1\n");
	else
		printf("%d\n", ans);
	return 0;	
}
