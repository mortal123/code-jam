#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 110000;

int size, h[MAXN];
vector<int> val;
int n, a[MAXN];
long long anss[MAXN];

struct Node {
	int l, r, id;
	Node(int l, int r, int id) : l(l), r(r), id(id) {}
	Node() {}
	friend int operator <(Node a, Node b) {
		return a.l / size == b.l / size ? a.r < b.r : a.l < b.l;
	}
};
vector<Node> pairs;

inline int lowbit(const int &x) {
	return x & -x;
}

inline int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

inline void ins(int pos, int v) {
	for(int i = pos; i <= val.size(); i += lowbit(i)) {
		h[i] += v;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	size = max(10.0, sqrt(n));
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		val.push_back(a[i]);
	}
	sort(val.begin(), val.end());
	val.erase(unique(val.begin(), val.end()), val.end());
	for(int i = 1; i <= n; i++) {
		a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
	}
	int qnum;
	scanf("%d", &qnum);
	for(int i = 1; i <= qnum; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		pairs.push_back(Node(l, r, i));
	}
	sort(pairs.begin(), pairs.end());
	int L = 1, R = 0;
	long long ans = 0;
	for(int i = 0; i < pairs.size(); i++) {
		while(R < pairs[i].r) {
			ans += ask(val.size()) - ask(a[++R]);
			ins(a[R], 1);
		}
		while(L > pairs[i].l) {
			ans += ask(a[--L] - 1);
			ins(a[L], 1);
		}
		while(R > pairs[i].r) {
			ans -= ask(val.size()) - ask(a[R]);
			ins(a[R--], -1);
		}
		while(L < pairs[i].l) {
			ans -= ask(a[L] - 1);
			ins(a[L++], -1);
		}
		anss[pairs[i].id] = ans;
	}
	for(int i = 1; i <= qnum; i++)
		printf("%lld\n", anss[i]);
	return 0;
} 
