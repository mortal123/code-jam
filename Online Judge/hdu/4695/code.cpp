#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

const int N = 55, M = 222;
const int MOD = (1e9 + 7);

int u[N], d[N], uNum, dNum, step;
long long n, k[M], x[M], ways[M];


vector<long long> multi(vector<long long> a, vector<long long> b) {
	// mul
	vector<long long> c(a.size() + b.size(), 0);
	for(int i = 0; i < (int)a.size(); i++)
		for(int j = 0; j < (int)b.size(); j++) {
			c[i + j] += a[i] * b[j] % MOD;
			c[i + j] %= MOD;
		}
	while((int)c.size() > step) {
		int lc = (int)c.size() - 1;
		for(int i = lc - step; i < lc; i++) {
			c[i] += k[i - (lc - step)] * c[lc] % MOD;
			c[i] %= MOD;
		}
		c.pop_back();
	}
	return c;
}

int main() {
	freopen("input.txt", "r", stdin);
	while(cin >> n) {
		cin >> uNum;
		fill(ways, ways + M, 0);
		ways[0] = 1;
		for(int i = 0; i < uNum; i++) {
			cin >> u[i];
		}
		for(int i = 0; i < M; i++)
			for(int j = 0; j < uNum; j++)
				if (i + u[j] < M)
					(ways[i + u[j]] += ways[i]) %= MOD;
		cin >> dNum;
		step = 0;
		fill(k, k + M, 0);
		for(int i = 0; i < dNum; i++) { 
			cin >> d[i];
			step = max(step, d[i]);
		}
		for(int i = 0; i < dNum; i++) {
			(k[step - d[i]] += ways[d[i]]) %= MOD;
		}
		x[0] = 1;
		for(int i = 1; i < step; i++) {
			x[i] = 0; 
			for(int j = 0; j < i; j++) {
				x[i] = (x[i] + x[j] * k[j - (i - step)] % MOD) % MOD;
			}
		}
		if (n < step) {
			cout << x[n] << endl;
			continue;
		}
		
		vector<long long> a(1, 1), b(2, 0);
		b[1] = 1;
		long long nn = n;
		while(n) {
			if (n & 1) {
				a = multi(a, b);
			}
			n >>= 1;
			b = multi(b, b);
		}
		long long ans = 0;
		for(int i = 0; i < step && i < (int)a.size(); i++) {
			ans += x[i] * a[i] % MOD;
			ans %= MOD;
		}
		cout << ans << endl;
	}
	return 0;
} 
