#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 21;


vector<pair<int, int> > items;
int length[1 << N], member[1 << N];
int digit[1 << N];
int n, dist;

inline int lowbit(int x) {
	return x & (-x);
}


int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	for(int i = 0; i <= 20; i++) {
		digit[1 << i] = i;
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		items.clear();
		double ans = 0;
		scanf("%d %d", &n, &dist);
		for(int i = 0; i < n; i++) {
			int a, c;
			scanf("%d %d", &a, &c);
			items.push_back(make_pair(a, c));
			if (a >= dist) {
				ans += a - dist;
			}
		}
		
		for(int i = 0; i <= n; i++) {
			vector<int> used, others;
			for(int j = 0; j < n; j++) {
				if (items[j].second == i) {
					used.push_back(items[j].first);
				} else {
					others.push_back(items[j].first);
				}
			}
			if ((int)used.size() < 2)
				continue;
			int m = (int)others.size();
			for(int j = 0; j < (1 << m); j++) {
				if (j) {
					length[j] = length[j ^ lowbit(j)] + others[digit[lowbit(j)]];
					member[j] = member[j ^ lowbit(j)] + 1;
				}
				long double c = 2 * max(0, min(used[0] + dist, used[0] + length[j] + used[1]) - 
									max(1 + dist, used[0] + length[j] + 1) + 1);
				for(int k = member[j] + 1; k <= n - 1; k++) {
					c *= (k - member[j]);
					c /= k;
				}
				c /= n;
				ans += c;
			}
		}
		printf("%.8f\n", ans);
	}
	return 0;
} 
