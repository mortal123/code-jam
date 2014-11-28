#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 200000;
const long long mod = 1000000000;

struct bignum
{
	long long a, b, c;
	void clear() {
		a = b = c = 0;
	}
	friend bignum operator +(bignum a, bignum b) {
		bignum res;
		res.clear();
		res.a = a.a + b.a;
		res.b = a.b + b.b;
		res.c = a.c + b.c;
		res.b += res.c / mod;
		res.c %= mod;
		
		res.a += res.b / mod;
		res.b %= mod;
		return res;
	}
	friend bignum operator -(bignum a, bignum b) {
		bignum res;
		res.clear();
		res.a = a.a - b.a;
		res.b = a.b - b.b;
		res.c = a.c - b.c;
		if (res.b < 0 || res.b == 0 && res.c < 0)
			res.b += mod, res.a--;
		if (res.c < 0) {
			res.c += mod;
			res.b--;
		}
		return res;
	}
	friend bignum operator *(bignum a, long long b) {
		bignum res;
		res.clear();
		res.a = a.a * b;
		res.b = a.b * b;
		res.c = a.c * b;
		
		res.b += res.c / mod;
		res.c %= mod;
		
		res.a += res.b / mod;
		res.b %= mod;
		return res;
	}
	friend bignum operator +(bignum a, long long b) {
		bignum res;
		res.clear();
		res.a = a.a;
		res.b = a.b;
		res.c = a.c + b;
		
		res.b += res.c / mod;
		res.c %= mod;
		
		res.a += res.b / mod;
		res.b %= mod;
		return res;
	}	
	friend int operator <(bignum a, bignum b) {
		if (a.a != b.a)
			return a.a < b.a;
		if (a.b != b.b)
			return a.b < b.b;
		return a.c < b.c;
	}	
	friend int operator >(bignum a, bignum b) {
		return b < a;
	}	
	void print()
	{
		if (!a)
			if (!b)
				printf("%I64d\n", c);
			else {
				printf("%I64d", b);
				printf("09%I64d\n", c);
			}
		else {
			printf("%I64d", a);
			printf("%09I64d", b);
			printf("%09I64d\n", c);
		}
	}
};

long long a[MAXN], b[MAXN];
bignum dp[MAXN];
int s, t;
int q[MAXN];

bignum calc(int j, int i) {
	return dp[j] + (a[i] * b[j] - b[j] + b[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%I64d", &a[i]);
	}
	for(int i = 1; i <= n; i++) {
		scanf("%I64d", &b[i]);
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++)
		dp[i].clear();
	dp[1] = dp[1] + b[1];
	s = 1, t = 1;
	q[s] = 1;
	for(int i = 2; i <= n; i++) {
		while(t > s && calc(q[s + 1], i) < calc(q[s], i))
			s++;
		dp[i] = calc(q[s], i);
		while(t > s && (dp[q[t]] - dp[q[t - 1]]) * (b[i] - b[q[t]]) < (dp[i] - dp[q[t]]) * (b[q[t]] - b[q[t - 1]]))
			t--;
		q[++t] = i;
	}
	//for(int i = 1; i <= n; i++)
	//	dp[i].print();
	dp[n].print();
	return 0;
} 
