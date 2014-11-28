#include <cstdio>
#include <cstdlib>

int p[MAXN], N, M, K;
int sa[MAXN], bx[MAXN], by[MAXN], buc[MAXN], rank[MAXN], h[MAXN];

void Init()
{
	scanf("%d %d %d", &N, &M, &K);
	for(int i = 1;i <= N;i++)
		scanf("%d", &p[i]), p[i + N] = p[i];
}

int cmp(int r[], int i, int j, int k)
{
	return r[i] == r[j] && r[i + k] == r[j + k];
}

void Suffix_Array(int p[], int N, int M)
{
	int *x = bx, *y = by, tot = M;
	for(int i = 1;i <= N;i++) buc[x[i] = p[i]]++;
	for(int i = 1;i <= M;i++) buc[i] += buc[i - 1];
	for(int i = 1;i <= N;i++) sa[buc[x[i]--]] = i;
	for(int k = 1;k <= N;k *= 2)
	{
		M = tot, tot = 0;
		for(int i = N - k + 1;i <= N;i++) y[++tot] = i;
		for(int i = 1;i <= N;i++) if (sa[i] > k) y[++tot] = sa[i] - k;
		for(int i = 0;i <= M;i++) buc[i] = 0;
		for(int i = 1;i <= N;i++) buc[x[y[i]]]++;
		for(int i = 1;i <= M;i++) buc[i] += buc[i - 1];
		for(int i = 1;i <= N;i++) sa[buc[x[y[i]]]--] = y[i];
		swap(x, y);
		x[sa[1]] = tot = 1;
		for(int i = 2;i <= N;i++)
		{
			if (!cmp(y, sa[i - 1], sa[i], k))
				tot++;
			x[sa[i]] = tot;
		}
	}
	for(int i = 1;i <= N;i++)
		rank[sa[i]] = i;
	int len = 0;
	for(int i = 1;i <= N;i++)
	{
		
	}
	
}

void Work()
{
	int *
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Suffix_Array(p, N * 2, M + 1):
	return 0;
}