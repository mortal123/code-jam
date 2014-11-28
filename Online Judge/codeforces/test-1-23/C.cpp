#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 200000;

struct node 
{
	long long x, y;
	friend int operator <(node a, node b)
	{
		return a.x < b.x;
	}
}p[MAXN], sec[MAXN], ans;
int n, top;

long long cross(node a, node b, node c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

void ins(long long x, long long y)
{
	node tmp;
	//printf("ins : %I64d %I64d\n", x, y);
	tmp.x = x; tmp.y = y;
	while(top > 1 && cross(p[top - 1], p[top], tmp) <= 0)
		top--;
	p[++top] = tmp;
}

int good(node a, node b)
{
	return a.x * b.y < a.y * b.x;
}

long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void fresh(long long u, long long d)
{
	long long tmp = gcd(u, d);
	u /= tmp;
	d /= tmp;
	node bck;
	bck.x = u, bck.y = d;
	if (good(bck, ans))
		ans = bck;
}

void calc(long long x, long long y)
{
	node tmp;
	tmp.x = x; tmp.y = y;
	int l = 1, r = top, mid1, mid2;
	while(l + 10 < r)
	{
		mid1 = (2 * l + r) / 3;
		mid2 = (l + 2 * r) / 3;
		if ((double)(p[mid1].y - tmp.y) / (tmp.x - p[mid1].x) < (double)(p[mid2].y - tmp.y) / (tmp.x - p[mid2].x))
			r = mid2;
		else
			l = mid1;
	}
	for(int i = l; i <= r; i++)
	{
		fresh(p[i].y - tmp.y, tmp.x - p[i].x);
	}
}

int main()
{
	freopen("caravan.in", "r", stdin);
	freopen("caravan.out", "w", stdout);
	scanf("%d", &n);
	ans.y = 1; ans.x = 100000000000ll;
	for(int i = 1; i <= n; i++)
		scanf("%I64d %I64d", &sec[i].x, &sec[i].y), ans.x = min(ans.x, sec[i].y - sec[i].x);
	sort(sec + 1, sec + n + 1);
	ins(0, 0);
	long long base = 0;
	for(int i = 1; i <= n; i++)
	{
		//if (top)
		calc(i, -(sec[i].y - sec[i].x) - base);
		if (i < n)
		{
			base += sec[i + 1].x - sec[i].x;
			ins(i, -base);
		}
	}
	printf("%I64d/%I64d\n", ans.x, ans.y);
	return 0;
}
