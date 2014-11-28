#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;

int a[N];
pair<int, vector<int> > vec[N], tmp[N];
int n;

void combine(pair<int, vector<int> > &a, const pair<int, vector<int> > &b, const pair<int, vector<int> > &c) {
	a.first = (b.first + c.first) / 2;
	a.second = b.second;
	for(int i = 0; i < (int)c.second.size(); i++) {
		a.second.push_back(c.second[i]);
	}
}

void divide(int n) {
	if (n == 1)
		return ;
	for(int i = 1; i <= n; i++) {
		tmp[i].second.clear();
	}
	int last = -1, tot = 0;
	for(int i = 1; i <= n; i++) {
		if (vec[i].first & 1) {
			if (last == -1) {
				last = i;
			} else {
				combine(tmp[++tot], vec[last], vec[i]);
				last = -1;
			}
		}
	}
	last = -1;
	for(int i = 1; i <= n; i++) {
		if (vec[i].first % 2 == 0) {
			if (last == -1) {
				last = i;
			} else {
				combine(tmp[++tot], vec[last], vec[i]);
				last = -1;
			}
		}
	}
	for(int i = 1; i <= n / 2; i++) {
		vec[i] = tmp[i];
	}
	divide(n / 2);
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			vec[i].second.clear();
			vec[i].first = a[i];
			vec[i].second.push_back(i);
		}
		divide(n);
		static int testCount = 0;
		printf("Case #%d:\n", ++testCount);
		for(int i = 0; i < (int)vec[1].second.size(); i++) {
			printf("%d%c", vec[1].second[i] - 1, i == vec[1].second.size() - 1 ? '\n' : ' ');
		}
	}
}
