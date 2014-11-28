#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <ctime>
using namespace std;

const int N = 5, M = N * 2;

vector<int> e[N + 5];
int visit[N + 10], number[N + 10], total;
set<pair<int, int> > edges;

void dfs(int x) {
	number[x] = ++total;
	visit[x] = 1;
	
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (!visit[y])
			dfs(y);
	}
}

int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	int test = 5;
	printf("%d\n", test);
	while(test--) {
		int n = N, m = M, q = N;
		printf("%d %d %d\n", n, m, q);
		edges.clear();
		for(int i = 1; i <= n; i++) {
			edges.insert(make_pair(i, i));
			e[i].clear();
		}
		for(int i = 2; i <= n; i++) {
			int a = rand() % (i - 1) + 1, b = i;
			e[a].push_back(b);
			edges.insert(make_pair(a, b));
		}
		
		for(int i = n; i <= m; i++) {
			int a = rand() % n + 1, b = rand() % n + 1;
			if (edges.count(make_pair(a, b))) {
				i--;
				continue;
			}
			e[a].push_back(b);
			edges.insert(make_pair(a, b));
		}
		
		fill(visit + 1, visit + n + 1, 0);
		total = 0;
		dfs(1);
		
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < (int)e[i].size(); j++) {
				printf("%d %d\n", number[i], number[e[i][j]]);
			}
		}
		
		for(int i = 1; i <= n; i++) {
			printf("%d ", i);
		}
		
		printf("\n");
	}
	return 0;
}
