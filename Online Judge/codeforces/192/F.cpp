#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 105, MAXM = MAXN * MAXN;

int next[MAXN], visit[MAXN];

struct eglist {
	int other[MAXM], succ[MAXM], last[MAXM], sum;
	void AddEdge(int a, int b) {
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
	}
	void clear() {
		memset(last, 0, sizeof(last));
		sum = 0;
	}
}e; 

int n;

char str[MAXN];

int find(int x) {
	for(int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (visit[y])
			continue;
		visit[y] = 1;
		if (next[y] == 0 || find(next[y])) {
			next[y] = x;
			return 1;
		}
	}
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for(int j = 1; j <= n; j++)
			if (str[j] == '.') {
				e.AddEdge(i, j);
			}
	}
	int ans = 0;
	memset(next, 0, sizeof(next));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			visit[j] = 0;
		ans += find(i);
	}
	if (ans != n) {
		printf("-1\n");
	} else {
		for(int i = 1; i <= n; i++)
			printf("%d %d\n", next[i], i);
	}
	return 0;
} 
