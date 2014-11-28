#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 222;

bool active[N];
int n, edge[N][N], degree[N];
int group[N];

void construct() {
	int v = 1;
	for(; v <= n && (!active[v] || degree[v] % 2 == 0); v++);
	if (v > n) {
		for(int i = 1; i <= n; i++) {
			if (active[i]) {
				group[i] = 1;
			}
		}
		return ;
	}
	vector<int> s;
	for(int i = 1; i <= n; i++) {
		if (active[i] && edge[v][i]) {
			s.push_back(i);
			degree[i]--;
		}
	}
	for(int i = 0; i < (int)s.size(); i++)
		for(int j = 0; j < (int)s.size(); j++)
			if (i != j)
				edge[s[i]][s[j]] ^= 1;
	active[v] = false;
	construct();
	int cnt = 0;
	for(int i = 0; i < (int)s.size(); i++) {
		if (group[s[i]] == 1) {
			cnt ^= 1;
		}
	}
	if (cnt == 0) {
		group[v] = 1;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &degree[i]);
		for(int j = 1; j <= degree[i]; j++) {
			int b;
			scanf("%d", &b);
			edge[i][b] = 1;
		}
		active[i] = true;
	}
	construct();
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if (group[i])
			ans++;
	}
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++) {
		if (group[i]) {
			printf("%d%c", i, --ans ? ' ' : '\n');
		}
	}
	return 0;
} 
