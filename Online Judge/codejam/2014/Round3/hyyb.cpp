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

int test, p, q, n, i, j, k, now, ans, tt, need[105], tower[105], h[105], g[105];
int f[105][1005][1005];

int main()
{
	freopen("BBBB1.in", "r", stdin); freopen("output2.txt", "w", stdout);
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d %d %d", &p, &q, &n);
		for (i = 1; i <= n; i++)
			scanf("%d %d", &h[i], &g[i]);
		for (i = 1; i <= n; i++)
		{
			now = h[i];
			if (now <= q)
			{
				need[i] = (now - 1) / p + 1;
				tower[i] = 0;
				continue;
			}
			
			int s = 0;
			while (1)
			{
				int x = (now - 1) % q + 1;
				if (x <= p)
				{
					need[i] = s + 1;
					tower[i] = (now - 1) / q;
					break;
				}
				
				now -= p;
				s++;
			}
		}
		
		for (j = 0; j <= 1000; j++)
			for (k = 0; k <= 1000; k++)
				if (k != 0)
					f[0][j][k] = -OO;
		f[0][0][0] = ans = 0;
		for (i = 1; i <= n; i++)
			for (j = 0; j <= 1000; j++)
				for (k = max(0, j - 1); k <= 1000; k++)
				{
					f[i][j][k] = -OO;
					if (j >= 1)
						f[i][j][k] = f[i][j - 1][k];
					int temp = k - ((h[i] - 1) / q + 1), t2;
					if (temp >= max(0, j - 1))
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][temp]);
					temp = k - tower[i], t2 = j - need[i];
					if (temp >= max(0, t2 - 1) && t2 >= 0)
						f[i][j][k] = max(f[i][j][k], f[i - 1][t2][temp] + g[i]);
					if (j > k)
						ans = max(ans, f[i][j][k]);
				}
		printf("Case #%d: %d\n", ++tt, ans);
	}
	
	return 0;
}
