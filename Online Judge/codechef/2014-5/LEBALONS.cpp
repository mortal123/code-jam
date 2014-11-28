#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

vector<pair<int, int> > packs;
int n, m;
long double tv[2][44], ways[2][44];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		packs.clear();
		for(int i = 1; i <= n; i++) {
			int c, p;
			scanf("%d %d", &c, &p);
			packs.push_back(make_pair(c, p));
		}
		sort(packs.begin(), packs.end());
		memset(tv, 0, sizeof(tv));
		memset(ways, 0, sizeof(ways));
		int cur = 0;
		ways[cur][0] = 1;
		for(int i = 0, j; i < n; i = j) {
			for(j = i; j < n && packs[j].first == packs[i].first; j++);
			cur ^= 1;
			for(int k = 0; k <= n; k++)
				ways[cur][k] = tv[cur][k] = 0;
			long double w = 1, v = 0;
			for(int k = i; k < j; k++) {
				w *= 2;
				v += packs[k].second;
			}
			for(int k = 0; k <= n; k++) {
				ways[cur][k] += ways[cur ^ 1][k];
				tv[cur][k] += tv[cur ^ 1][k];
				if (k < n) {
					tv[cur][k + 1] += tv[cur ^ 1][k] * (w - 1) + v * ways[cur ^ 1][k] * (w / 2);
					ways[cur][k + 1] += ways[cur ^ 1][k] * (w - 1);
				}
			}
		}
		long double ansv = 0, answ = 0;
		for(int i = m; i <= n; i++) {
			ansv += tv[cur][i];
			answ += ways[cur][i];
		}
		long double a = ansv / answ;
		printf("%.10f\n", (double)a);
	}
	return 0;
} 
