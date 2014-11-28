#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 4000;

int n, m;

char map[MAXN + 10][MAXN + 10];
int t, w, visit[MAXN + 10][MAXN + 10], mark[MAXN + 10][MAXN + 10];

struct node
{
	int x, y;
}q[MAXN * MAXN + 10], bak[MAXN * MAXN + 10], bak2[MAXN * MAXN + 10];
int top = 0, top2 = 0;;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
void Bfs(node s)
{	
	int b = 0, e = 0;
	q[++e] = s;
	visit[s.x][s.y] = 1;
	while(b < e)
	{
		node r = q[++b];
		for(int i = 0; i < 4; i++) {
			node tmp;
			tmp.x = r.x + dx[i];
			tmp.y = r.y + dy[i];
			if (tmp.x > n || tmp.y > m || tmp.x < 1 || tmp.y < 1 || map[tmp.x][tmp.y] == '.')
				continue;
			if (visit[tmp.x][tmp.y])
				continue;
			if (map[tmp.x][tmp.y] == map[s.x][s.y]) {
				q[++e].x = tmp.x, q[e].y = tmp.y;
				visit[tmp.x][tmp.y] = 1;
			} else {
				if (!mark[tmp.x][tmp.y]) {
					mark[tmp.x][tmp.y] = 1;
					bak2[++top2].x = tmp.x;
					bak2[top2].y = tmp.y;
				}
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for(int i = 1; i <= n; i++) {
		gets(map[i] + 1);
	}
	bak2[top2 = 1].x = 1, bak2[top2].y = 1;
	int ans = 0;
	do {
		for(int i = 1; i <= top2; i++)
			bak[i] = bak2[i];
		top = top2; top2 = 0;
		while(top) {
			Bfs(bak[top]);
			top--;
		}
		ans++;
	}while(top2);
	printf("%d\n", ans);
	return 0;
} 
