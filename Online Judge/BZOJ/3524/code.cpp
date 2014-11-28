#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 555555;

pair<int, int> tree[N << 2];
int n, m;
int a[N];

inline pair<int, int> combine(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first == b.first) {
		return make_pair(a.first, a.second + b.second);
	} else if (a.second >= b.second) {
		return make_pair(a.first, a.second - b.second);
	} else {
		return make_pair(b.first, b.second - a.second);
	}
}

void build(int x, int l, int r) {
	if (l == r) {
		tree[x].first = a[l];
		tree[x].second = 1;
	} else {
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
	}
}

pair<int, int> ask(int x, int l, int r, int ql, int qr) {
	if (qr < l || ql > r)
		return make_pair(0, 0);
	if (ql <= l && r <= qr) {
		return tree[x];
	}
	int mid = (l + r) >> 1;
	return combine(ask(x << 1, l, mid, ql, qr), ask(x << 1 | 1, mid + 1, r, ql, qr));
} 

vector<int> values;
vector<int> pos[N];

int cnt(int l, int r, int v) {
	int p = lower_bound(values.begin(), values.end(), v) - values.begin();
	return upper_bound(pos[p].begin(), pos[p].end(), r) - lower_bound(pos[p].begin(), pos[p].end(), l);
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		values.push_back(a[i]);
	}	
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	for(int i = 1; i <= n; i++) {
		pos[lower_bound(values.begin(), values.end(), a[i]) - values.begin()].push_back(i);
	}
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		int result = ask(1, 1, n, l, r).first;
		if (cnt(l, r, result) > (r - l + 1) / 2) {
			printf("%d\n", result);
		} else {
			printf("0\n");
		}
	}
}
