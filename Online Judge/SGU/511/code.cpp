#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000000;

long long n, p;
int prime[MAXN + 5], hash[MAXN + 5], slot, ss[MAXN + 5];
vector<int > vec;

long long sqr(long long a) {
	return a * a;
}

long long poww(long long a, long long b, long long mod) {
	if (b == 0)
		return 1 % mod;
	if (b % 2 == 1)
		return poww(a, b - 1, mod) * a % mod;
	return sqr(poww(a, b / 2, mod)) % mod;
}

int calc(long long p) {
	vec.clear();
	long long pp = p - 1;
	while(pp > 1) {
		vec.push_back(prime[pp]);
		pp /= prime[pp];
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for(int i = 2; ; i++) {
		bool flag = true;
		for(int j = 0; j < vec.size(); j++) {
			if (poww(i, (p - 1) / vec[j], p) == 1) {
				flag = false;
				break;
			}
		}
		if (flag)
			return i;
	}
}

void print(long long r, long long a, long long b, long long c) {
	cout << poww(r, a, p) << " " << poww(r, b, p) << " " << poww(r, c, p) << endl;
}

void work() {
	++slot;
	int r = calc(p);
	//cerr << r << endl;
	long long step = poww(r, n, p);
	for(long long i = 0, j = 1; hash[j] != slot; hash[j] = slot, ss[j] = i, ++i, j = j * step % p) {
		long long k;
		k = (j + p - 1) % p;
		if (hash[k] == slot) {
			print(r, ss[k], 0, i);
			return;
		}
		k = (j + 1) % p;
		if (hash[k] == slot) {
			print(r, i, 0, ss[k]);
			return;
		}
	}
	printf("-1\n");
} 

int main() {
	freopen("input.txt", "r", stdin);
	for(int i = 1; i <= MAXN; i++)
		prime[i] = i;
	for(int i = 2; i <= MAXN; i++) {
		if (prime[i] != i)
			continue;
		for(int j = i + i; j <= MAXN; j += i)
			prime[j] = min(prime[j], i);
	}
	int test;
	scanf("%d", &test);
	for(int i = 1; i <= test; i++) {
		cin >> n >> p;
		work();
	}
	return 0;
} 
