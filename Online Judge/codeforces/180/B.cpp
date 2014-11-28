#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 200000;
const int inf = 2000000000;

int a[MAXN], b[MAXN];
int n, m, k;

struct Rec
{
	int val, pos, pos2;
}rec[MAXN * 2];
int top, tot, t2;
int hash[MAXN], h[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen(")
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	if (n == m)
	{
		int flag = 1;
		for(int i = 1; i <= n; i++)
			if (a[i] != b[i])
				flag = 0;
		if (flag)
		{
			printf("NO\n");
			return 0;
		}
	}
	tot = 0;
	for(int i = 1, j = 1; i <= n || j <= m;)
	{
		++tot;
		int mm = inf;
		if (i <= n && a[i] < mm)
			mm = a[i];
		if (j <= m && b[j] < mm)
			mm = b[j];
		while(i <= n && a[i] == mm)
			a[i] = tot, i++;
		while(j <= m && b[j] == mm)
			b[j] = tot, j++;
	}
	for(int i = 1; i <= n; i++)
		hash[a[i]]++;
	for(int i = 1; i <= m; i++)
		hash[b[i]]--;
	t2 = 0;
	for(int i = 1; i <= tot; i++)
		if (hash[i] != 0)
			h[++t2] = hash[i];
	for(int i = t2; i >= t2; i--)
	{
		if (h[i] > 0)
		{
			printf("YES\n");
			return 0;
		}
		if (h[i] < 0 && i > 1 && h[i - 1] > 0 && h[i - 1] > (-h[i]))
		{
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	/*
	int i = n, j = m;
	while(i && j && a[i] == b[j])
		i--, j--;
	if (i == 0){
		printf("NO\n");
	} else
	if (j == 0){
		printf("YES\n");
	} else
	{
		if (a[i] > b[j])
			printf("YES\n");
		else
			printf("NO\n");
	}
	*/
	//for()
	return 0;
}
