#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 2222;
const int inf = 1000000000;

char map[N][N];
int f[N][N], n, m, ans;
vector<pair<int, int> > points, ppt;

int dfs(int x, int y) {
	if (f[x][y] >= 0)
		return f[x][y];
	if (f[x][y] == -2)
		return inf;
	
	f[x][y] = -2;
	if (map[x][y] == '#')
		return f[x][y] = 0;
	
	if (map[x][y] == '>') {
		return f[x][y] = dfs(x, y + 1) + 1;
	} else if (map[x][y] == '<') {
		return f[x][y] = dfs(x, y - 1) + 1;
	} else if (map[x][y] == 'v') {
		return f[x][y] = dfs(x + 1, y) + 1;
	} else if (map[x][y] == '^') {
		return f[x][y] = dfs(x - 1, y) + 1;
	}
	
}

pair<int, int> move(pair<int, int> w) {
	int x = w.first, y = w.second;
	if (map[x][y] == '<')
		return make_pair(x, y - 1);
	if (map[x][y] == '>')
		return make_pair(x, y + 1);
	if (map[x][y] == '^')
		return make_pair(x - 1, y);
	if (map[x][y] == 'v')
		return make_pair(x + 1, y);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", map[i] + 1);
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			f[i][j] = -1;
			
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			dfs(i, j);
		}
	}
	
	if (n * m <= 2) {
		printf("0\n");
		return 0;
	}
	
	int maxV = -inf;
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			maxV = max(maxV, f[i][j]);
	
	if (maxV >= inf) {
		printf("-1\n");
		return 0;
	}
	
	ans = maxV + max(maxV - 1, 0);
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if (f[i][j] == maxV)
				points.push_back(make_pair(i, j));
		}
	}
	
	while(maxV) {
		if ((int)points.size() < 2)
			break;
		if (maxV == 1) {
			ans++;
		}
		
		ppt.clear();
		
		for(int i = 0; i < (int)points.size(); i++) {
			ppt.push_back(move(points[i]));
		}
		
		sort(ppt.begin(), ppt.end());
		ppt.erase(unique(ppt.begin(), ppt.end()), ppt.end());
		points = ppt;
		
		maxV--;
	}
	
	printf("%d\n", ans);
	return 0;
} 
