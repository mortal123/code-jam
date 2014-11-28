#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2600 * 2, M = N * 20, SPAN = 100000;
const int INF = 1000000000;

int n, m, source, target, f[SPAN];
vector<pair<int, int> > edges[SPAN + 11];

void work() {
	scanf("%d %d", &n, &m);
	vector<int> date, earning, start, finish, rate;
	for(int i = 1; i <= SPAN; i++) {
		edges[i].clear();
	}
	for(int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		date.push_back(a);
		earning.push_back(b);
	}
	for(int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		start.push_back(a);
		finish.push_back(b);
		rate.push_back(c);
		edges[a].push_back(make_pair(b, c));
	}
	for(int i = SPAN; i >= 1; i--) {
		f[i] = 0;
		if (i < SPAN)
			f[i] = f[i + 1];
		for(int j = 0; j < (int)edges[i].size(); j++) {
			f[i] = max(f[i], f[edges[i][j].first] + edges[i][j].second);
		}
	}
	double ans = 0;
	for(int i = 0; i < n; i++) {
		ans += 1.0 * earning[i] * f[date[i]];
	}
	printf("%.2f\n", ans / 100);
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		static int countTest = 0;
		printf("Case #%d:\n", ++countTest);
		work();
	}
	return 0;
} 
