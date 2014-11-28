#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n, m;

vector<int> s[2];
long long ans = 0;

void solve() {
	if ((int)s[0].size() < 2)
		return;
	for(int i = 0; i < (int)s[1].size(); i++) {
		if (s[1][i] >= s[0][0] && s[1][i] <= s[0].back()) {
			ans = max(ans, 2 * n);
			return ;
		}
	}
	
	
	for(int i = 0; i < (int)s[1].size(); i++) {
		if (s[1][i] < s[0][0]) {
			ans = max(ans, 2 * n - 2 * (s[0][0] - s[1][i]));
		} else if (s[1][i] > s[0].back()) {
			ans = max(ans, 2 * n - 2 * (s[1][i] - s[0].back()));
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		s[a].push_back(b);
	}
	
	for(int i = 0; i < 2; i++) {
		sort(s[i].begin(), s[i].end());
		if ((int)s[i].size() > 2) {
			ans = max(ans, s[i][(int)s[i].size() - 1] - s[i][0]);
		}
	}
	
	solve();
	vector<int> tmp = s[0];
	s[0] = s[1];
	s[1] = tmp;
	solve();
	
	printf("%d\n", ans);
	return 0;
}
