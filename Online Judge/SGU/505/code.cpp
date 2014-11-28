#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

const int MAXN = 410000;

struct Mystring {
	string s;
	int id;
	friend int operator <(const Mystring &a, const Mystring &b) {
		return a.s < b.s;
	}
	void reserve() {
		for(int i = 0, j = s.length() - 1; i < j; i++, j--)	
			swap(s[i], s[j]);
	}
}pre[MAXN], suf[MAXN], text[MAXN];

int left1[MAXN], right1[MAXN];
int left2[MAXN], right2[MAXN];
int n, m, ans[MAXN], h[MAXN], q[MAXN];

int lowbit(int x) {
	return x & -x;
}

int ask(int pos) {
	assert(pos >= 0);
	int res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

int ins(int pos, int val) {
	assert(pos > 0);
	for(int i = pos; i <= n; i += lowbit(i))
		h[i] += val;
}

int belong(string &s, string &t) {
	if (t.length() < s.length())
		return 0;
	for(int i = 0; i < s.length(); i++)
		if (s[i] != t[i])
			return 0;
	return 1;
}

void calc(int left[], int right[], Mystring p[]) {
	sort(text + 1, text + n + 1);
	//sort(p + 1, p + m + 1);
	for(int i = 1; i <= m; i++) {
		int L, R, l, r, mid;
		l = 1, r = n, mid;
		while(l < r) {
			mid = (l + r) / 2;
			if (text[mid] < p[i])
				l = mid + 1;
			else
				r = mid;
		}
		L = l;
		if (!belong(p[i].s, text[L].s)) {
			left[p[i].id] = 1, right[p[i].id] = 0;
			continue;
		}
		l = L, r = n;
		while(l < r) {
			mid = (l + r) / 2 + 1;
			if (!belong(p[i].s, text[mid].s))
				r = mid - 1;
			else
				l = mid;
		}
		R = l;
		left[p[i].id] = L;
		right[p[i].id] = R;
	}/*
	cout << "--text--" << endl;
	for(int i = 1; i <= n; i++) {
		cout << text[i].s << endl;
	}
	cout << "--and--" << endl;
	for(int i = 1; i <= m; i++) {
		cout << p[i].s << " " << left[p[i].id] << " " << right[p[i].id] << endl;;
	}*/
}

inline int calcV(const int &x) {
	if (x < 0)
		return left2[-x] - 1;
	return right2[x];
}

inline int cmp(const int &a, const int &b) {
	return calcV(a) < calcV(b);
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> text[i].s;
	}
	cin >> m;
	for(int i = 1; i <= m; i++) {
		cin >> pre[i].s;
		pre[i].id = i;
		cin >> suf[i].s;
		suf[i].reserve();
		suf[i].id = i;
	}
	calc(left1, right1, pre);
	for(int i = 1; i <= n; i++)
		text[i].id = i;
	for(int i = 1; i <= n; i++)
		text[i].reserve();
	calc(left2, right2, suf);
	for(int i = 1; i <= m; i++)
		q[i] = i;
	for(int i = 1; i <= m; i++)
		q[i + m] = -i;
	sort(q + 1, q + 2 * m + 1, cmp);
	int j = 0;
	for(int i = 1; i <= 2 * m; i++) {
		int x = abs(q[i]), v = calcV(q[i]);
		while(j < v) { 
			ins(text[++j].id, 1);
			//cout << "ins " << text[j].id << endl;
		}
		if (q[i] > 0)
			ans[x] += ask(right1[x]) - ask(left1[x] - 1);
		else
			ans[x] -= ask(right1[x]) - ask(left1[x] - 1);
		//cout << x << " " << left1[x] << " " << right1[x] << endl;
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
