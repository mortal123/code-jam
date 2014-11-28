#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 3333;

vector<int> set[2];
bool map[N][N], visit[N];
int n, m, degree[N], bound;

void dfs(int x, int s) {
	visit[x] = true;
	set[s].push_back(x);
	for(int i = 1; i <= n; i++)
		if (!visit[i] && degree[i] >= bound && map[x][i] == false) {
			dfs(i, s ^ 1);
		}
}

void print(vector<int> &set) {
	sort(set.begin(), set.end());
	for(int i = 0; i < (int)set.size() && i < n / 3; i++) {
		printf("%d ", set[i]);
	}
	
	printf("\n");
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	bound = n * 2 / 3 - 1;
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = true;
		map[b][a] = true;
		degree[a]++;
		degree[b]++;
	}
	
	for(int i = 1; i <= n; i++)
		if (degree[i] >= bound && !visit[i]) {
			dfs(i, 0);
		}
	if ((int)set[0].size() >= n / 3) {
		print(set[0]);
	} else {
		print(set[1]);
	}
	return 0;
} 
