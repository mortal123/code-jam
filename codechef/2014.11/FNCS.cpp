#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

#define left LEFT
#define right RIGHT

const int N = 100000 + 5;
const int MAX_LIMIT = 400;
const long long LONG = 1e14;

int LIMIT;
int coe[300 + 1][N];
int n, q, m, left[N], right[N];
int a[N];
pair<long long, long long> answer[N];
long long h[N];

__inline void add(pair<long long, long long> &a, long long b) {
	a.second += b;
	if (a.second < 0) {
		a.first --;
		a.second += LONG;
	} else if (a.second >= LONG) {
		a.first ++;
		a.second %= LONG;
	}
}

__inline void add2(pair<long long, long long> &a, const pair<long long, long long> &b) {
	a.second += b.second;
	a.first += b.first;
	if (a.second >= LONG) {
		a.first += a.second / LONG;
		a.second %= LONG;
	}
}

__inline int lowbit(int x) {
	return x & (-x);
}

__inline void ins(int x, int v) {
	for(int i = x; i <= n; i += lowbit(i)) {
		h[i] += v;
	}
}

__inline long long ask(int x) {
	long long res = 0;
	for(int i = x; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

int main() {
	scanf("%d", &n);
	LIMIT = min(n, MAX_LIMIT);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		ins(i + 1, a[i]);
	}
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &left[i], &right[i]);
		left[i]--;
		right[i]--;
	}
	m = 0;
	for(int i = 0; i < n; i += LIMIT) {
		for(int j = i; j < n && j < i + LIMIT; j++) {
			coe[m][left[j]]++;
			coe[m][right[j] + 1]--;
		}
		answer[m] = make_pair(0, 0);
		for(int j = 0, last = 0; j < n; j++) {
			last += coe[m][j];
			coe[m][j] = last;
			add(answer[m], 1LL * last * a[j]);
		}
		m++;
	}
	/*for(int i = 0; i < n; i++) {
		cout << answer[i] << endl;
	}*/
	scanf("%d", &q);
	for(int i = 0; i < q; i++) {
		int type, s, t;
		scanf("%d %d %d", &type, &s, &t);
		//cout << type << endl;
		if (type == 1) {
			s--;
			ins(s + 1, t - a[s]);
			for(int j = 0; j < m; j++) {
				add(answer[j], 1LL * coe[j][s] * (t - a[s]));
			}
			a[s] = t;
		} else {
			s--;
			t--;
			pair<long long, long long> res = make_pair(0, 0);
			while(s <= t && s % LIMIT != 0) {
				add(res, ask(right[s] + 1) - ask(left[s]));
				s++;
			}
			while(s + LIMIT - 1 <= t) {
				add2(res, answer[s / LIMIT]);
				s += LIMIT;
			}
			while(s <= t) {
				add(res, ask(right[s] + 1) - ask(left[s]));
				s++;
			}
			if (res.first) {
				printf("%lld%014lld\n", res.first, res.second);
			} else {
				printf("%lld\n", res.second);
			}
			//cout << res << endl;
		}
	}
	return 0;
}