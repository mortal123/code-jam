#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1200000;

char str[MAXN], s2[MAXN];
int N, bx[MAXN], by[MAXN], lp[MAXN][21], rank[MAXN], buc[MAXN], sa[MAXN];
int st[MAXN], ed[MAXN], id[MAXN], len, mi[MAXN];

void Init()
{
	gets(str + 1);
	len = strlen(str + 1);
	scanf("%d\n", &N);
	for(int i = 1;i <= N;i++)
	{
		st[i] = len + 1;
		gets(s2 + 1);
		int tmplen = strlen(s2 + 1);
		ed[i] = st[i] + tmplen;
		for(int j = st[i];j <= ed[i];j++)
			id[j] = i, str[++len] = s2[j];
	}
}

void ArraySuffix(char str[], int len)
{
	int *x = bx, *y = by, p = len;
	for(int i = 1;i <= len;i++) buc[x[i] = str[i]]++;
	for(int i = 1;i <= len;i++) buc[i] += buc[i - 1];
	for(int i = len;i >= 1;i--) sa[buc[x[i]]--] = i;
	for(int k = 1;k <= len;k *= 2)
	{
		p = 0;
		for(int i = len - k + 1;i <= len;i++) y[++p] = i;
		for(int i = 1;i <= len;i++) if (sa[i] - k > 0) y[++p] = sa[i] - k;
		for(int i = 0;i <= len;i++) buc[i] = 0;
		for(int i = 1;i <= len;i++) buc[x[y[i]]]++;
		for(int i = 1;i <= len;i++) buc[i] += buc[i - 1];
		for(int i = len;i >= 1;i--) sa[buc[x[y[i]]]--] = y[i];
		swap(x, y);
		x[sa[1]] = p = 1;
		for(int i = 2;i <= len;i++)
			if (cmp(y, sa[i], sa[i - 1], k))
				x[sa[i]] = p;
			else
				x[sa[i]] = ++p;
	}
	for(int i = 1;i <= len;i++)
		rank[sa[i]] = i;
	int k = 0;
	for(int i = 1;i <= len;i++)
	{
		if (k) k--;
		if (rank[i] - 1 == 0)
			continue;
		int j = sa[rank[i] - 1];
		while(i + k <= len && j + k <= len && str[i + k] == str[j + k])
			k++;
		h[rank[i]] = k;
	}
	for(int i = 1;i <= len;i++)
		lp[i][0] = h[i];
	for(int i = 1;i <= 20;i++)
		for(int j = 1;j <= len;j++)
		{
			lp[j][i] = lp[j][i - 1];
			if (j + (1 << (i - 1)) <= len)
				lp[j][i] = min(lp[j][i], lp[j + (1 << (i - 1))][i - 1]);
		}
	int cnt = 0;
	for(int i = 0;i <= len;i++)
	{
		if (i >= (1 << (cnt + 1)))
			cnt++;
		mi[i] = cnt;
	}
}

void Work()
{
	for(int i = 1;i <= len;i++)
	{
		
	}
}

int main()
{
	Init();
	ArraySuffix(str, len);
	Work();
	return 0;
}
