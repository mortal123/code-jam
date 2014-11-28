#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1111;

pair<int, int> pairs[N * 2];
int n, m;

int main() {
	scanf("%d %d", &m, &n);
	for(int i = 1; i < m; i++) {
		int x;
		scanf("%d", &x);
		pairs[i] = make_pair(x, 0);
	}
	
	for(int i = 1; i < n; i++) {
		int x;
		scanf("%d", &x);
		pairs[m - 1 + i] = make_pair(x, 1);
	}
	
	sort(pairs + 1, pairs + n + m - 2 + 1);
	
	int cnt[2] = {0}, ans = 0;
	for(int i = n + m - 2; i >= 1; i--) {
		ans += pairs[i].first * (cnt[pairs[i].second ^ 1] + 1);
		cnt[pairs[i].second]++;
	}
	
	printf("%d\n", ans);
}
