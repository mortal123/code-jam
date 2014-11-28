#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 45;
const int stop = 500000;

char str[MAXN][MAXN];
int visit[MAXN], n, ans, hate[MAXN], ch[MAXN];
long long limit = 0;

void dfs(int dep, int now) {
	if (++limit >= stop)
		return;
	if (now + (n - dep + 1) <= ans)
		return;
	ans = max(ans, now);
	if (dep > n)
		return;
	int x, e = -1;
	for(int i = 1; i <= n; i++)
		if (ch[i]) {
			hate[i] = 0;
			for(int j = 1; j <= n; j++)
				if (ch[j] && str[i][j] == 'Y')
					hate[i]++;
		}
					
	for(int i = 1; i <= n; i++) {
		if (!visit[i]) {
			int cnt = 0, hat = 0;
			for(int j = 1; j <= n; j++)
				if (!visit[j] && str[i][j] == 'Y') {
					cnt++;
				} else if (ch[j] && str[i][j] == 'Y') {
					if (hate[j] == 1) {
						cnt = -10000;
						break;
					}
					hat++;
				}
			if (hat <= 1 && cnt > e) {
				e = cnt;
				x = i;
			}
		}
	}
	if (e >= 0) {
		visit[x] = ch[x] = 1;
		dfs(dep + 1, now + 1);
	} else 
		return;
	visit[x] = 1;
	ch[x] = 0;
	dfs(dep + 1, now);
	
	visit[x] = ch[x] = 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T, base;
	scanf("%d", &T);
	while(T--) {
		base = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%s", str[i] + 1);
			visit[i] = ch[i] = 0;
			int c = 0;
			for(int j = 1; j <= n; j++)
				if (str[i][j] == 'Y')
					c++;
			if (c == 0)
				visit[i] = ch[i] = 1, base++;
		}
		ans = 0;
		limit = 0;
		dfs(1, 0);
		printf("%d\n", ans + base);
	}
	return 0;
}
