#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 3000;
const int inf = 1000000000;

long long a[MAXN], b[MAXN], c[MAXN];
int n;

long long aabs(long long x)
{
	if (x >= 0)
		return x;
	return -x;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	a[1] = 0;
	for(int i = n - 1; i >= 1; i--)
	{
		int len = n - i;
		if (b[i] == 1)
		{
			int v = inf;
			for(int j = 1; j <= len; j++)
				if (a[j] < v)
					v = a[j];
			if (v <= 0)
				for(int j = 1; j <= len; j++)
					a[j] += (-v) + 1;
			else
				for(int j = 1; j <= len; j++)
					a[j] -= (v - 1);
			c[1] = 0;
			for(int j = 1; j <= len; j++)
				c[j + 1] = c[j] + a[j];
			for(int j = 1; j <= len + 1; j++)
				a[j] = c[j];
			for(int j = 1; j <= len + 1; j++)
				if (aabs(a[j]) > 2 * 1000000000)
				{
					printf("IMPOSSIBLE\n");
					exit(0);
				}
		} else 
		{
			int v = -inf;
			for(int j = 1; j <= len; j++)
				if (a[j] > v)
					v = a[j];
			if (v >= 0)
				for(int j = 1; j <= len; j++)
					a[j] -= v + 1;
			else
				for(int j = 1; j <= len; j++)
					a[j] += (-v - 1);
			c[1] = 0;
			for(int j = 1; j <= len; j++)
				c[j + 1] = c[j] + a[j];
			for(int j = 1; j <= len + 1; j++)
				a[j] = c[j];
			for(int j = 1; j <= len + 1; j++)
				if (aabs(a[j]) > 2 * 1000000000)
				{
					printf("IMPOSSIBLE\n");
					exit(0);
				}
		}
	}
	if (b[1] == 1 && a[n] > 1000000000)
	{
		for(int i = 1; i <= n; i++)
			a[i] -= (a[n] - 1000000000);
	}
	if (b[1] == 1 && a[1] < -1000000000)
	{
		for(int i = n; i >= 1; i--)
			a[i] += (-1000000000 - a[1]);
	}
	if (b[0] == 0 && a[n] < -1000000000)
	{
		for(int i = 1; i <= n; i++)
			a[i] += (-1000000000 - a[n]);
	}
	if (b[0] == 1 && a[1] > 1000000000)
	{
		for(int i = n; i >= 1; i--)
			a[i] -= (a[1] - 1000000000);
	}
	for(int i = 1; i <= n; i++)
		if (aabs(a[i]) > 1000000000)
		{
			printf("IMPOSSIBLE\n");
			exit(0);
		}
	for(int i = 1; i <= n; i++)
		cout << a[i] <<  ((i == n) ? '\n' : ' ');
	return 0;
}
