#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#define PQ priority_queue
#define OO 2147483647
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)

int FASTBUFFER;

using namespace std;

int test, n, i, j, k, exist[105], ok[105][105], a[105], s[105], win[105][105];
double f[105][105], ans;

int main()
{
	freopen("input.txt", "r", stdin); freopen("output2.txt", "w", stdout);
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d", &n);
		for (i = 1; i <= 100; i++)
			exist[i] = 0;
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]), exist[a[i]] = 1;
		for (i = 2; i <= 100; i++)
		{
			s[i] = 0;
			for (j = 1; j <= n; j++)
				if (a[j] % i == 0)
					s[i]++;
		}
		
		memset(ok, 0, sizeof(ok));
		memset(win, 0, sizeof(win));
		for (i = 2; i <= 100; i++)
			for (j = 1; j <= n; j++)
				ok[i][__gcd(i, a[j])]++;
		win[n][1] = 1;
		for (i = n - 1; i >= 1; i--)
		{
			win[i][1] = 1;
			for (j = 2; j <= 100; j++)
			{
				if (s[j] > i && win[i + 1][j] == 0)
					win[i][j] = 1;
				for (k = 1; k < j; k++)
					if (ok[j][k] && win[i + 1][k] == 0)
						win[i][j] = 1;
			}	
		}
		
		for (i = 1; i <= n; i++)
			if (win[1][a[i]] == 0)
				break;
		if (i <= n)
			printf("1 ");
		else
			printf("0 ");
		memset(f, 0, sizeof(f));
		int now = a[1];
		for (i = 1; i <= n; i++)
			now = __gcd(now, a[i]);
		if (now != 1)
		{
			if (n & 1)
				printf("1.0000\n");
			else
				printf("0.0000\n");
			continue;
		}
		
		for (i = 1; i <= n; i++)
			f[1][a[i]] += (1.0) / (double)n;
		for (i = 1; i < n; i++)
		{
			for (j = 2; j <= 100; j++)
			{
				if (s[j] > i)
					f[i + 1][j] += f[i][j] * (double)(s[j] - i) / (double)(n - i);
				for (k = 1; k < j; k++)
					f[i + 1][k] += f[i][j] * (double)ok[j][k] / (double)(n - i);
			}
		}
		
		ans = 0.0;
		for (i = 2; i <= n; i += 2)
			ans += f[i][1];
		printf("%.4f\n", ans);
	}
	
	return 0;
}
