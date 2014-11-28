#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

#define hash HASH

const int N = 333;
const int MAGIC = 10007;

long long tree[N << 2], power[N], hash[N];
int number[N], size[N << 2];
int pos[N], mat[N][N], a[N];
int n;

map<long long, int> mp;
vector<pair<long long, int> > table;

__inline void update(int x) {
	tree[x] = tree[x << 1] * power[size[x << 1 | 1]] + tree[x << 1 | 1];
}

void build(int x, int l, int r) {
	size[x] = r - l + 1;
	if (l == r) {
		tree[x] = a[l] - 1;
	} else {
		int mid = ((l + r) >> 1);
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		update(x);
	}
}

void edit(int x, int l, int r, int p) {
	if (l == r) {
		tree[x]++;
		return ;
	}
	int mid = ((l + r) >> 1);
	if (p <= mid) {
		edit(x << 1, l, mid, p);
	} else {
		edit(x << 1 | 1, mid + 1, r, p);
	}
	update(x);
}

long long ask(int x, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) {
		return 0;
	}
	if (ql <= l && r <= qr) {
		return tree[x] * power[qr - r];
	}
	int mid = ((l + r) >> 1);
	return ask(x << 1, l, mid, ql, qr) + ask(x << 1 | 1, mid + 1, r, ql, qr);
}

bool check() {
	for(int i = 1; i <= n; i++) {
		pos[a[i]] = i;
	}
	build(1, 1, n);
	static vector<pair<long long, int> > compare;
	compare = table;
	for(int i = 1; i <= n; i++) {
		int x = pos[i];
		long long temp = ask(1, 1, n, 1, x - 1) * power[n - x] + ask(1, 1, n, x + 1, n);
		int r = lower_bound(compare.begin(), compare.end(), make_pair(temp, 0)) - compare.begin();
		if (r == (int)compare.size() || compare[r].first != temp || compare[r].second == 0) {
			return false;
		} 
		compare[r].second--;
		edit(1, 1, n, x);
	}
	return true;
}


void solve() {
	scanf("%d", &n);
	static int order[N];
	for(int i = 1; i <= n; i++) {
		order[i] = i;
	}
	random_shuffle(order + 1, order + n + 1);
	mp.clear();
	for(int i = 1; i <= n; i++) {
		long long h = 0;
		for(int j = 1; j < n; j++) {
			scanf("%d", &mat[order[i]][j]);
			h = h * MAGIC + mat[order[i]][j];
		}
		mp[hash[order[i]] = h]++;
	}

	table.clear();
	for(map<long long, int> :: iterator it = mp.begin(); it != mp.end(); ++it) {
		table.push_back(*it);
	}

	for(int i = 1; i <= n; i++) {
		bool before = false;
		for(int j = 1; j < i; j++) {
			if (hash[i] == hash[j]) {
				before = true;
			}
		}
		if (before) {
			continue;
		}
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k < n; k++) {
				a[k] = mat[i][k];
				if (a[k] >= j) {
					a[k]++;
				}
			}
			a[n] = j;
			if (check()) {
				for(int k = 1; k <= n; k++) {
					printf("%d%c", a[k], k == n ? '\n' : ' ');
				}
				return ;
			}
		}
	}
}

int main() {
	power[0] = 1;
	for(int i = 1; i <= 300; i++) {
		power[i] = power[i - 1] * MAGIC;
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		solve();
	}
	return 0;
}