#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int N = 111111;

vector<pair<int, int> > op;
int cnt[N];

int main() {
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);
	for(int i = 1; i <= p; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		op.push_back(make_pair(a, b));
	}
	sort(op.begin(), op.end());
	for(int i = 1; i <= m; i++) {
		cnt[i] = 1;
	}
	for(int row = 1, i = 0; row <= n; row++) {
		bool flag = true;
		int begin = 1, end = m, ii = i;		
		for(i = ii; i < p && op[i].first == row; i++) {
			cnt[op[i].second]++;
			if (op[i].second < m) {
				cnt[op[i].second + 1]--;
			}
			if (op[i].second == 1) {
				begin++;
			}
			if (op[i].second == m) {
				end++;
			}
		}
		for(i = ii; i < p && op[i].first == row; i++) {
			if (op[i].second < m && cnt[op[i].second + 1] < 0) {
				flag = false;
			}
		}
		if (!flag) {
			printf("-1\n");
		} else {
			printf("%d\n", end - begin);
		}
		for(i = ii; i < p && op[i].first == row; i++) {
			cnt[op[i].second]--;
			if (op[i].second < m) {
				cnt[op[i].second + 1]++;
			}
		}
	}
}
