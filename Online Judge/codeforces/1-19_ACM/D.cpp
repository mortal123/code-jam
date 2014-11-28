#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int MAXN = 200000;

struct node
{
	long long time, num;
}p[MAXN];

struct nd
{
	long long x, y;
	friend int operator <(nd a, nd b)
	{
		return a.x < b.x;
	}
}a[MAXN];

int n, m;
long long A, B;

int main()
{
	freopen("millenium.in", "r", stdin);
	freopen("millenium.out", "w", stdout);
	scanf("%d %I64d %I64d", &n, &A, &B);
	for(int i = 1; i <= n; i++)
		scanf("%I64d %I64d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1);
	m = 0;
	for(int i = 1; i <= n; i++)
	if (a[i].x != a[i - 1].x)
		p[++m].time = a[i].x, p[m].num = 1;
	else
		p[m].num++;
	for(int i = 1; i <= m-1; i++)
	{
		long long tmp = p[i + 1].time - p[i].time;
		p[i].num = max(0ll, p[i].num - B * tmp);
		p[i + 1].num += p[i].num;
	}
	long long ans = p[m].time + p[m].num / B + (p[m].num % B > 0) - 1;
	printf("%I64d\n", ans);
	return 0;
}
