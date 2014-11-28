#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> bonus;

const int N = 1111;

int n, m, k;
int color[N];
int value[N][N];
int cost[N][N];
int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d %d", &n, &m, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &color[i]);
		}
		
		bonus.clear();
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				scanf("%d", &value[i][j]);
			}
		}
		
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			int maxV = 0;
			for(int j = 1; j <= m; j++) {
				scanf("%d", &cost[i][j]);
				maxV = max(maxV, value[i][j] - cost[i][j]);
			}
			
			bonus.push_back(maxV - value[i][color[i]]);
			ans += value[i][color[i]];
		}
		
		sort(bonus.begin(), bonus.end());
		reverse(bonus.begin(), bonus.end());
		for(int i = 0; i < k && i < (int)bonus.size(); i++) {
			if (bonus[i] > 0)
				ans += bonus[i];
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
