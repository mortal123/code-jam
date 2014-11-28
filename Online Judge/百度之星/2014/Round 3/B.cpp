#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)
#define OO 2147483647
#define priority_queue PQ

using namespace std;

int FASTBUFFER;

void dfs(int i, int f);
void Add(int A[], int a, int b);
int Ask(int A[], int a);

int test, n, i, a, b, sum, root, rnow, q, tt, tot;
int e[200005], succ[200005], last[200005], val[200005], vv[200005];
int Left[200005], Right[200005];
int A[200005], B[200005];
char type[20];

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
			last[i] = 0;
		sum = 0;
		for (i = 1; i < n; i++)
		{
			scanf("%d %d", &a, &b);
			e[++sum] = b, succ[sum] = last[a], last[a] = sum;
			e[++sum] = a, succ[sum] = last[b], last[b] = sum;
		}
		
		for (i = 1; i <= n; i++)
			scanf("%d", &val[i]);
		tot = 0;
		dfs(1, 0);
		for (i = 1; i <= n; i++)
			A[i] = B[i] = 0;
		Add(A, 1, 1);
		root = 1;
		for (i = 1; i <= n; i++)
			Add(B, i, vv[i]);
		scanf("%d", &q);
		printf("Case #%d:\n", ++tt);
		for (i = 1; i <= q; i++)
		{
			scanf("%s", type);
			if (type[0] == 'Q')
			{
				scanf("%d", &a);
				if (a == root)
					printf("%d\n", Ask(B, n));
				else
				{
					if (Ask(A, Right[a]) - Ask(A, Left[a] - 1) == 0)
						printf("%d\n", Ask(B, Right[a]) - Ask(B, Left[a] - 1));
					else
					{
						int y;
						for (int x = last[a]; x; x = succ[x])
						{
							y = e[x];
							if (Left[y] > Left[a] && Left[y] <= Left[root] && Right[y] >= Left[root])
								break;
						}
						
						printf("%d\n", Ask(B, n) - (Ask(B, Right[y]) - Ask(B, Left[y] - 1)));
					}
				}
			}
			
			else if (type[0] == 'C')
			{
				scanf("%d %d", &a, &b);
				Add(B, Left[a], b - val[a]);
				val[a] = b;
			}
			
			else
			{
				scanf("%d", &a);
				Add(A, Left[root], -1);
				Add(A, Left[a], 1);
				root = a;
				rnow = Ask(B, Right[a]) - Ask(B, Left[a] - 1);
			}
		}
	}
	
	return 0;
}

void dfs(int i, int f)
{
	Left[i] = ++tot;
	vv[tot] = val[i];
	for (int x = last[i]; x; x = succ[x])
		if (e[x] != f)
			dfs(e[x], i);
	Right[i] = tot;
}

void Add(int A[], int a, int b)
{
	for (int i = a; i <= n; i += (i & (0 - i)))
		A[i] += b;
}

int Ask(int A[], int a)
{
	int ret = 0, i;
	for (i = a; i > 0; i -= (i & (0 - i)))
		ret += A[i];
	return ret;
}
