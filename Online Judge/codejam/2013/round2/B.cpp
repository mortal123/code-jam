#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

long long P, N;
int bak[100], len;

int ok1(long long num, long long p, long long n)
{
	long long a = num, b = (1ll << n) - 1 - num;
	if (p >= (1ll << n))
		return 1;
	for(int i = 1; i <= n; i++)
	{
		long long key = bak[i];
		if (key == 0) {
			if (a != 0)
				return 0;
			b /= 2;
		}
		if (key == 1)
		{
			if (a == 0)
				return 1;
			if (a % 2 == 1) {
				a /= 2;
				b /= 2;
			} else {
				a = a / 2 - 1;
				b = b / 2 + 1;
			}
		}
	}
	return 0;
}

int ok2(long long num, long long p, long long n)
{
	long long a = num, b = (1ll << n) - 1 - num;
	if (p >= (1ll << n))
		return 1;
	for(int i = 1; i <= n; i++)
	{
		long long key = bak[i];
		if (key == 0) {
			if (b == 0)
				return 0;
			b--;
			if (a % 2 == 1) {
				a = a / 2 + 1;
				b /= 2;
			} else {
				a /= 2;
				b /= 2;
			}
		} else {
			if (b != 0)
				return 1;
			a = a / 2 + 1;
		}
	}
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		cin >> N >> P;
		cout << "Case #" << t << ": ";
		long long l = 0, r = (1ll << N) - 1;
		long long bp = P;
		for(int i = N; i >= 1; i--)
			bak[i] = P % 2, P /= 2;
		P = bp;
		while(l < r)
		{
			long long mid = (l + r) / 2 + 1;
			if (ok1(mid, P, N))
				l = mid;
			else
				r = mid - 1;
		}
		cout << l << " ";
		//ok1(l, P, N);
		l = 0, r = (1ll << N) - 1;
		while(l < r)
		{
			long long mid = (l + r) / 2 + 1;
			if (ok2(mid, P, N))
				l = mid;
			else
				r = mid - 1;
		}
		cout << l << endl;
	}
}
