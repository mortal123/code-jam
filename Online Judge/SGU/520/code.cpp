#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1100;

bool win[MAXN];
int map[MAXN][MAXN];
int dis[MAXN], q[MAXN], head, tail;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = map[b][a] = 1;
	}
	head = 0, tail = 0;
	q[++tail] = 1;
	dis[1] = 1;
	while(head < tail) {
		int x = q[++head];
		for(int i = 1; i <= n; i++)
			if (map[x][i]) {
				if (dis[i])
					continue;
				dis[i] = dis[x] + 1;
				q[++tail] = i;
			}
	}
	for(int i = tail; i >= 1; i--) {
		win[q[i]] = false;
		for(int j = 1; j <= n; j++) {
			if (map[q[i]][j] && dis[j] == dis[q[i]] + 1) {
				if (win[j] == false)
					win[q[i]] = true;
			}
		}
	}
	printf("%s\n", win[1] == false ? "Nikolay " : "Vladimir");
	return 0;
}
