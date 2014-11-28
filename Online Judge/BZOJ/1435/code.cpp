#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#define GET(a, b) (((a) >> (b)) & 1)
#define SET(x, p, v) ((x) & (~(1 << (p))) | ((v) << (p))) 

using namespace std;

const int N = 16;
const int MOD = 19901013;

int dp[N][N][N][N];
vector<pair<int, int> > vec[2];
int n, m;
char map[N][N];
int f[N], g[N][N];

inline void add(int &a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	if (a < 0)
		a += MOD;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", map[i] + 1);
	for(int l = 1; l <= m; l++)
		for(int r = l; r <= m; r++)
			for(int u = 1; u <= n; u++) {
				int now = 0, nxt = 1;
				vec[0].clear();
				vec[1].clear();
				vec[now].push_back(make_pair(0, 1));
				for(int i = u; i <= n; i++) {
					for(int j = l; j <= r; j++) {
						vec[nxt].clear();
						int v = (map[i][j] == 'x');
						for(int k = 0; k < vec[now].size(); k++) {
							vec[nxt].push_back(make_pair(SET(vec[now][k].first, j, v), vec[now][k].second));
							if (v)
								continue;
							int tmp = SET(vec[now][k].first, j, 1);
							if (j - 1 >= l && GET(vec[now][k].first, j - 1) == 0)
								vec[nxt].push_back(make_pair(SET(tmp, j - 1, 1), vec[now][k].second));
							if (i - 1 >= u && GET(vec[now][k].first, j) == 0)
								vec[nxt].push_back(make_pair(SET(tmp, j, 1), vec[now][k].second));
						}
						sort(vec[nxt].begin(), vec[nxt].end());
						int size = 0;
						for(int k = 0; k < vec[nxt].size(); k++) {
							if (k == 0 || vec[nxt][k].first != vec[nxt][k - 1].first) {
								vec[nxt][size++] = vec[nxt][k];
							} else {
								add(vec[nxt][size - 1].second, vec[nxt][k].second);
							}
						}
						vec[nxt].resize(size);
						swap(now, nxt);
					}
					int res = 0;
					for(int j = 0; j < vec[now].size(); j++)
						add(res, vec[now][j].second);
					dp[l][r][u][i] = res;
				}
			}
	int ans = 0;
	for(int i = 0; i < (1 << (n - 1)); i++) {
		vector<int> start;
		start.push_back(0);
		for(int j = 0; j < (n - 1); j++)
			if ((i >> j) & 1)
				start.push_back(j + 1);
		start.push_back(n);
		for(int j = 1; j <= m; j++)
			for(int k = j; k <= m; k++) {
				g[j][k] = 1;
				for(int l = 0; l < (int)start.size() - 1; l++)
					g[j][k] = (long long)g[j][k] * dp[j][k][start[l] + 1][start[l + 1]] % MOD;
			}
		long long ways = 0;
		for(int j = 1; j <= m; j++) {
			f[j] = g[1][j];
			for(int k = 1; k < j; k++)
				add(f[j], -int((long long)f[k] * g[k + 1][j] % MOD));
		}
		if ((int)start.size() % 2)
			add(ans, -f[m]);
		else
			add(ans, f[m]);
	}
	printf("%lld\n", ans);
	return 0;
} 
