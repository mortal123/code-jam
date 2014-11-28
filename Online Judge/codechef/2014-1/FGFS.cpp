#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int N = 2 * 111111;

vector<pair<int, pair<int, int> > > events;

int n, k;
int val[N], ans;

inline void read(int &a) {
	a = 0;
	char ch;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	
	for(; ch >= '0' && ch <= '9'; ch = getchar()) {
		a = a * 10 + ch - '0';
	}
}

int main() {
	
	freopen("input.txt", "r", stdin);
	
	int test;
	scanf("%d", &test);
	//test = 30;
	
	while(test--) {
		scanf("%d %d", &n, &k);
		//n = 100000, k = 30;
		ans = 0;
		events.clear();
		
		for(int i = 1; i <= n; i++) {
			val[i] = 0;
		}
		
		for(int i = 1; i <= n; i++) {
			int s, f, p;
			read(s), read(f), read(p);
			//s = 1, f = 100, p = 1;
			events.push_back(make_pair(p, make_pair(s, i)));
			events.push_back(make_pair(p, make_pair(f, -i)));
		}
		
		sort(events.begin(), events.end());
		
		for(int i = 0, j = 0; i < 2 * n; i = j) {
			int best = 0;
			for(j = i; j < 2 * n && events[j].first == events[i].first; j++) {
				if (events[j].second.second < 0) {
					best = max(best, val[-events[j].second.second]);
				} else {
					val[events[j].second.second] = best + 1;
				}
			}
			
			ans += best;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
