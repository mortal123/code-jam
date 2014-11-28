#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 100000;

vector<int> primes;
vector<pair<int, int> > factor[N + 10];
bool used[N + 5];
int n, MOD, q, tot;
int tree[(N << 2) + 5], answer[N];
long long many[(N << 2) + 5];

__inline void update(int x) {
	tree[x] = 1LL * tree[x << 1] * tree[x << 1 | 1] % MOD;
}

int power(int x, long long p) {
	if (p == 0) {
		return 1 % MOD;
	}
	int temp = power(x, p >> 1);
	if (p & 1) {
		return 1LL * temp * temp % MOD * x % MOD;
	} else {
		return 1LL * temp * temp % MOD;
	}
}

void build(int x, int l, int r) {
	if (l == r) {
		tree[x] = 1;
		many[x] = 0;
	} else {
		int mid = ((l + r) >> 1);
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		update(x);
	}
}

void edit(int x, int l, int r, int p, int v) {
	if (l == r) {
		many[x] += v;
		tree[x] = power(primes[l], many[x]);
		return ;
	}
	int mid = ((l + r) >> 1);
	if (p <= mid) {
		edit(x << 1, l, mid, p, v);
	} else {
		edit(x << 1 | 1, mid + 1, r, p, v);
	}
	update(x);
}

void doit(int x, int opt) {
	for(int i = 0; i < (int)factor[x].size(); i++) {
		int pos = factor[x][i].first;
		int cnt = factor[x][i].second;
		edit(1, 0, tot - 1, pos, opt * cnt * x);
	}
} 

int main() {
	for(int i = 2; i <= N; i++) {
		if (used[i] == false) {
			primes.push_back(i);
			for(int j = i; j <= N; j += i) {
				used[j] = 1;
				int x = j, cnt = 0;
				while(x % i == 0) {
					x /= i;
					cnt++;
				}
				factor[j].push_back(make_pair(primes.size() - 1, cnt));
			}
		}
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d %d", &n, &MOD, &q);
		tot = 0;
		while(tot < primes.size() && n >= primes[tot]) {
			tot++;
		}
		build(1, 0, tot - 1);
		for(int r = 1; r <= (n + 1) / 2; r++) {
			doit(n - r + 1, 1);
			doit(r, -1);
			answer[r] = tree[1];
			//cout << r << endl;
		}
		for(int i = 1; i <= q; i++) {
			int r;
			scanf("%d", &r);
			if (r > n / 2) {
				r = n - r;
			}
			printf("%d\n", answer[r]);
		}
	}
	return 0;
}