#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2000000;

struct node
{
	double pos;
	int num;
	friend int operator <(node a, node b)
	{
		return a.pos < b.pos;
	}
}p[MAXN];
int n;
char str[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	gets(str + 1);
	n = strlen(str + 1);
	double l = 0, r = 1;
	for(int i = 1; i <= n; i++)
	{
		if (str[i] == 'l')
		{
			p[i].pos = (l + r) / 2;
			p[i].num = i;
			r = (l + r) / 2;
		} else
		{
			p[i].pos = (l + r) / 2;
			p[i].num = i;
			l = (l + r) / 2;
		}
	}
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; i++)
		printf("%d\n", p[i].num);
	return 0;
}
