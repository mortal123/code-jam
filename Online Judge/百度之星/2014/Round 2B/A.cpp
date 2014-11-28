#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int INF = (1 << 30);

vector<pair<int, int> > pairs;
int n;
pair<int, int> charm[N];

void renew() {
	pair<int, int> ch = make_pair(-INF, -1);
	for(int j = 0; j < n; j++) {
		if (pairs[j].second > 0) {
			ch = pairs[j];
		}
		charm[j] = make_pair(pairs[j].first - ch.first, -ch.second);
	}
	ch = make_pair(INF, -1);
	for(int j = n - 1; j >= 0; j--) {
		if (pairs[j].second > 0) {
			ch = pairs[j];
		}
		charm[j] = min(charm[j], make_pair(ch.first - pairs[j].first, -ch.second));
	}
}

int main() {
	int test;
	scanf("%d", &test);
	for(int testCount = 1; testCount <= test; testCount++) {
		printf("Case #%d:\n", testCount);
		pairs.clear();
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			int x, h;
			scanf("%d %d", &x, &h);
			pairs.push_back(make_pair(x, h));
		}
		renew();
		int q;
		scanf("%d", &q);
		for(int i = 0; i < q; i++) {
			static char buf[10];
			int a, b;
			scanf("%s", buf);
			if (buf[0] == 'U') {
				scanf("%d %d", &a, &b);
				pairs[a].second = b;
				renew();
			} else {
				scanf("%d", &a);
				int ans = 0;
				for(int j = 0; j < n; j++) {
					if (-charm[j].second <= a) {
						ans++;
					}
				}
				printf("%d\n", ans);
			}
		}
	}
} 
