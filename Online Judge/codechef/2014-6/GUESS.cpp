#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	int n, m;
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		long long a, b;
		b = 1LL * n * m;
		a = 1LL * n / 2 * ((m + 1) / 2) + 1LL * (n + 1) / 2 * (m / 2);
		if (a == 0)
			b = 1;
		long long g = gcd(a, b);
		a /= g;
		b /= g;
		cout << a << "/" << b << endl;
	}
	return 0;
}
