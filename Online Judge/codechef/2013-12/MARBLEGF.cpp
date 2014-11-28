#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1111111;

long long h[N];
int n, q;

int lowbit(int x) {
	return x & (-x);
}

long long ask(int x) {
	long long res = 0;
	for(int i = x; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

void ins(int a, int b) {
	for(int i = a; i <= n; i += lowbit(i)) {
		h[i] += b;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		ins(i, x);
	}
	static char buf[N];
	for(int i = 1; i <= q; i++) {
		char opt;
		int a, b;
		scanf("%s %d %d", buf, &a, &b);
		a++;
		opt = buf[0];
		if (opt == 'S') {
			b++;
			cout << ask(b) - ask(a - 1) << endl;
		} else if (opt == 'G') {
			ins(a, b);
		} else {
			ins(a, -b);
		}
	}
	return 0;
} 
