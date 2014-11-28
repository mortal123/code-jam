#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int INF = (1 << 20);
int isCir[N], shash[N], stamp = 0;
int eny[N], n, value[N];
vector<int> sons[N];
vector<int> queue;
int f[N][2], g[N][2][2], ans = 0;

int main() {
	freopen("input.txt", "r", stdin);
	
	int test;
	scanf("%d", &test);
	for(int testCount = 1; testCount <= test; testCount++) {
		printf("Case #%d:\n", testCount);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &eny[i]);
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &value[i]);
		}
		for(int i = 1; i <= n; i++) {
			shash[i] = 0;
			isCir[i] = 0;
			sons[i].clear();
		}
		stamp = 0;
		
		for(int i = 1; i <= n; i++) {
			int cur = i;
			++stamp;
			while(!shash[cur]) {
				shash[cur] = stamp;
				cur = eny[cur];
			} 
			if (shash[cur] == stamp) {
				++stamp;
				while(!(shash[cur] == stamp)) {
					isCir[cur] = 1;
					shash[cur] = stamp;
					cur = eny[cur];
				}
			}
		}
		queue.clear();
		for(int i = 1; i <= n; i++) {
			if (!isCir[i]) {
				sons[eny[i]].push_back(i);
			} else {
				queue.push_back(i);
			}
		}
		for(int i = 0; i < (int)queue.size(); i++) {
			for(int j = 0; j < (int)sons[queue[i]].size(); j++) {
				queue.push_back(sons[queue[i]][j]);
			}
		}
		for(int i = (int)queue.size() - 1; i >= 0; i--) {
			int x = queue[i];
			f[x][0] = 0;
			f[x][1] = value[x];
			for(int j = 0; j < (int)sons[x].size(); j++) {
				int y = sons[x][j];
				f[x][1] += f[y][0];
				f[x][0] += max(f[y][0], f[y][1]);
			}
		}
		ans = 0;
		++stamp;
		for(int i = 1; i <= n; i++) {
			if (isCir[i] && shash[i] != stamp) {
				vector<int> path;
				int c = i;
				while(shash[c] != stamp) {
					shash[c] = stamp;
					path.push_back(c);
					c = eny[c];
				}
				for(int j = 0; j < 2; j++)
					for(int k = 0; k < 2; k++)
						g[0][j][k] = -INF;
				g[0][0][0] = f[path[0]][0];
				g[0][1][1] = f[path[0]][1];
				for(int j = 1; j < (int)path.size(); j++) {
					int x = path[j];
					for(int k = 0; k < 2; k++) {
						g[j][k][0] = max(g[j - 1][k][0], g[j - 1][k][1]) + f[path[j]][0];
						g[j][k][1] = g[j - 1][k][0] + f[path[j]][1];
					}
				}
				int len = (int)path.size() - 1;
				ans += max(g[len][0][0], max(g[len][0][1], g[len][1][0]));
			}
		}
		printf("%d\n", ans);
	}
	
}
