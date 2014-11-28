#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)
#define OO 2147483647
#define priority_queue PQ

using namespace std;

int FASTBUFFER;

int test, n, i, j, tt, tag, a[100005], s[100005], Hash[100005];
vector <int> v[100005];

void dfs(int now);
void Merge(int a, int b);

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (i = 1; i <= n; i++)
			v[i].clear(), v[i].push_back(i), s[i] = a[i];
		dfs(n);
		for (i = 1; i <= n; i++)
			if (v[i].size())
				break;
		printf("Case #%d:\n", ++tt);
		for (j = 0; j < v[i].size() - 1; j++)
			printf("%d ", v[i][j] - 1);
		printf("%d\n", v[i][v[i].size() - 1] - 1);
	}
	
	return 0;
}

void dfs(int now)
{
	if (now == 1)
		return;
	int x = 0;
	tag++;
	for (i = 1; i <= n; i++)
	{
		if (v[i].empty())
			continue;
		if (s[i] & 1)
		{
			Hash[i] = tag;
			if (x == 0)
				x = i;
			else
				Merge(x, i), x = 0;
		}
	}
	
	if (x)
		v[x].clear();
	x = 0;
	for (i = 1; i <= n; i++)
	{
		if (v[i].empty() || Hash[i] == tag)
			continue;
		if (!(s[i] & 1))
		{
			if (x == 0)
				x = i;
			else
				Merge(x, i), x = 0;
		}
	}
	
	if (x)
		v[x].clear();
	dfs((now - 1) / 2);
}

void Merge(int a, int b)
{
	int i;
	if (v[a].size() > v[b].size())
		swap(a, b);
	for (i = 0; i < v[a].size(); i++)
		v[b].push_back(v[a][i]);
	v[a].clear();
	s[b] += s[a];
	s[a] = 0;
	s[b] /= 2;
}
