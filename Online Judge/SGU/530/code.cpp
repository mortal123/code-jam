#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 110000, MAXM = 210000;

struct eglist {
	int other[MAXM * 2], succ[MAXM * 2], last[MAXM * 2], sum;
	void clear() {
		memset(last, -1, sizeof(last));
		sum = 0;
	}
	void addEdge(int a, int b) {
		other[sum] = b, succ[sum] = last[a], last[a] = sum++;
		other[sum] = a, succ[sum] = last[b], last[b] = sum++;
	}
}e;

const int inf = 1000000000;

int dis[4][MAXN];
int n, m, visit[MAXN], q[MAXN];

int main() {
	scanf("%d %d", &n, &m);
	e.clear();
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e.addEdge(a, b);
	}	
	for(int i = 1; i <= 3; i++) {
		int head = 0, tail = 0;
		for(int j = 1; j <= n; j++)
			visit[j] = 0, dis[i][j] = inf;
		dis[i][i] = 0, visit[i] = 1;
		q[++tail] = i;
		while(head < tail) {
			int x = q[++head];
			for(int j = e.last[x]; ~j; j = e.succ[j]) {
				int y = e.other[j];
				if (!visit[y]) {
					visit[y] = 1;
					q[++tail] = y;
					dis[i][y] = dis[i][x] + 1;
				}
			}
		}
	}
	bool flag = false;
	for(int i = 1; i <= n; i++) {
		if (!(dis[1][2] + 2 <= dis[1][i] + dis[2][i]) && !(dis[2][3] + 2 <= dis[2][i] + dis[3][i]) 
			&& !(dis[1][3] + 2 <= dis[1][i] + dis[3][i]))
				flag = true;
	}
	if (flag) {
		printf("1\n");
	} else {
		printf("2\n");
	}
}
