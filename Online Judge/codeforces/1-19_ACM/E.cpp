#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 300000, inf = 200000;

int a[MAXN], b[MAXN], m, c[MAXN], f[MAXN];

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int solve(int tot)
{
	int res = 0;
	for(int i = 1; i <= m; i++)
		res += (c[i] + tot) / m;
	if (res != tot)
		return 0;
	return 1;
}

struct node
{
	int val, num;
	friend int operator <(node a, node b)
	{
		return a.val < b.val;
	}
}st[MAXN];
int top = 0, ans[MAXN], len = 0;

void ins(int val, int num)
{
	st[++top].val = val;
	st[top].num = num;
	int i = top;
	while(i / 2)
	{
		int j = i / 2;
		if (st[i] < st[j])
		{
			swap(st[i], st[j]);
			i = j;
		} else
			break;
	}
}

void del()
{
	st[1] = st[top--];
	int i = 1, j;
	while(i * 2 <= top)
	{
		j = i * 2;
		if (j + 1 <= top && st[j + 1] < st[j])
			j++;
		if (st[j] < st[i])
		{
			swap(st[i], st[j]);
			i = j;
		} else
			break;
	}
}

int main()
{
	freopen("changes.in", "r", stdin);
	freopen("changes.out", "w", stdout);
	scanf("%d", &m);
	int sumc = 0, sumcc = 0;
	for(int i = 1; i <= m; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]), c[i] = b[i] - a[i], sumc += c[i], sumcc += abs(c[i]);
	if (sumc)
	{
		printf("-1\n");
		return 0;
	}			
	int base = 0;
	for(int i = 2; i <= m; i++)
		base = gcd(base, abs(c[i] - c[i - 1]));

	if (base % m != 0)
	{
		printf("-1\n");
		return 0;
	}
	int Mn = inf;
	for(int i = 1; i <= m; i++)
		Mn = min(Mn, c[i]);
	int l = 0, r = inf, mid;
//	if (l * m + Mn < 0) l++;
	while(l < r)
	{
		mid = (l + r) / 2;
		if (solve(m * mid - Mn))
			r = mid;
		else
			l = mid + 1;
	}
	if (l == inf)
	{
		printf("-1\n");
		return 0;
	}
	int tot = m * l - Mn;
	for(int i = 1; i <= m; i++)
		f[i] = (tot + c[i]) / m;
	int dec = 0; len = 0;
	for(int i = 1; i <= m; i++)
		ins(a[i], i);
	for(int i = 1; i <= tot; i++)
	{
		while(top && f[st[1].num] == 0)
			del();
		ans[++len] = st[1].num;
		node tmp = st[1];
		del();
		tmp.val = tmp.val - dec + m;
		f[tmp.num]--;
		ins(tmp.val + dec, tmp.num);
		dec++;
		if (top && st[1].val - dec < 0)
		{
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n", len);
	for(int i = 1; i <= len; i++)
		printf("%d%c", ans[i], i == len ? '\n' : ' ');
	return 0;
}
