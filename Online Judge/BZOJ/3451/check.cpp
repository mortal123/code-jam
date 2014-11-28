#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 33333;

vector<int> e[N];
int n;
double ans = 0;

void dfs(int x, int length, int from) {
	ans += 1.0 / length;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == from)
			continue;
		dfs(y, length + 1, x);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("answer.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	
	for(int i = 0; i < n; i++) {
		dfs(i, 1, -1);
	}
	
	printf("%.4f\n", ans);
	return 0;
}
