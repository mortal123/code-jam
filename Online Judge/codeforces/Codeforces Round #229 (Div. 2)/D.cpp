#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 55;

vector<pair<int, int> > paths[N][N];

int visit[N][N];
int dis[N][N];
vector<pair<int, int> > q;
int dx[2] = {0, 1};
int dy[2] = {1, 0};
int n, m, k;

int cnt[1000];

void print(int x, int y) {
	for(int i = 0; i < (int)paths[x][y].size(); i++) {
		printf("(%d, %d) ", paths[x][y][i].first, paths[x][y][i].second);
	}
	
	printf("\n");
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	q.push_back(make_pair(1, 1));
	paths[1][1].push_back(make_pair(1, 1));
	visit[1][1] = 1;
	dis[1][1] = 1;
	cnt[1] = 1;
	
	for(int head = 0; head < (int)q.size(); head++) {
		pair<int, int> tmp = q[head];
		for(int i = 0; i < 2; i++) {
			int x = tmp.first + dx[i];
			int y = tmp.second + dy[i];
			if (x > n || y > m || visit[x][y])
				continue;
			visit[x][y] = 1;
			paths[x][y] = paths[tmp.first][tmp.second];
			paths[x][y].push_back(make_pair(x, y));
			q.push_back(make_pair(x, y));
			dis[x][y] = dis[tmp.first][tmp.second] + 1;
			cnt[dis[x][y]]++;
		}
	}
	
	int ans = 0, dep = 0, last = 0, sum = 0;
	for(dep = 1; ; dep++) {
		if (sum + cnt[dep] >= k) {
			last = k - sum;
			ans += (k - sum) * dep;
			break;
		} else {
			ans += cnt[dep] * dep;
			sum += cnt[dep];
		}
	}
	
	printf("%d\n", ans);
	for(int i = dep; i >= 1; i--) {
		for(int j = 1; j <= n && last; j++) 
			for(int k = 1; k <= m && last; k++)
				if (dis[j][k] == i) {
					last--;
					print(j, k);
				}
		last = cnt[i - 1];
	}
	return 0;
} 
