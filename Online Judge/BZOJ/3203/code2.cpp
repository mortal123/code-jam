#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
typedef long long ll;

const int MAXN = 100000;

ll a[MAXN + 10], x[MAXN + 10], d, sum[MAXN + 10];
int n;
struct node
{
	long long x, y;
}p[MAXN + 10], t;
int top = 0;

double calc(int a, int b)
{
	return (double)(p[a].y - p[b].y) / (p[a].x - p[b].x);
}

int ok(node a, node b, node c)
{
	long long x1 = b.x - a.x, x2 = c.x - a.x, y1 = b.y - a.y, y2 = c.y - a.y;
	return (double)x1 / y1 - 1e-8 < (double)x2 / y2;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d %lld", &n, &d);
	S.clear();
	for(int i = 1; i <= n; i++) {
		scanf("%lld %lld", &a[i], &x[i]);
	}
	for(int i = 1; i <= n; i++)
		sum[i] += sum[i - 1] + a[i];
	double ans = 0;
	p[++top].x = d, p[top].y = 0;
	for(int i = 1; i <= n; i++) {
		int l = 1, r = top, mid1, mid2;
		p[top + 1].x = d * i + x[i]; p[top + 1].y = sum[i];
		while(l + 10 < r)
		{
			int mid1 = (l * 2 + r) / 3;
			int mid2 = (l + r * 2) / 3;
			if (calc(top + 1, mid1) > calc(top + 1, mid2))
				r = mid2;
			else
				l = mid1;
		}
		double mx = calc(top + 1, l);
		for(int j = l; j <= r; j++)
			mx = max(mx, calc(top + 1, j));
		ans += mx;
		t.x = d * i + d, t.y = sum[i];
		while(top > 1 && ok(p[top - 1], p[top], t))
			top--;
		p[++top] = t;
		//cout << mx << endl;
	}
	//long long aans = ans;
	printf("%.0lf\n", ans - 0.5);
	//cout << ans << endl;
	return 0;
} 
