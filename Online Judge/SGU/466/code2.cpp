#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
const int MAXN = 410000;
int n, m;
int al, ar;

struct case1
{
	int l, r, len;
	friend int operator <(case1 a, case1 b)
	{
		if (a.len != b.len)
			return a.len < b.len;
		return a.l < b.l;
	}
	case1(){}
	case1(int _l, int _r)
	{
		l = (_l > n) ? _l - n : _l;
		r = (_r > n) ? _r - n : _r;
		if (l > r)
			len = n - r + 1 + l;
		else
			len = r - l + 1;
	}
};

struct case2
{
	int l, r, len;
	friend int operator <(case2 a, case2 b)
	{
		if (a.l != b.l)
			return a.l < b.l;
		return a.r < b.r;
	}
	case2(){}
	case2(int _l, int _r)
	{
		l = (_l > n) ? _l - n : _l;
		r = (_r > n) ? _r - n : _r;
		if (l > r)
			len = n - r + 1 + l;
		else
			len = r - l + 1;
	}
};

struct quer
{
	int key;
	int l, r;
}q[MAXN];

set<case1> prior;
set<case2> sec;
char str[MAXN];
int path[MAXN];
int debug = 0;
void ins(int l, int r)
{
	if (l > n) l -= n;
	if (r > n) r -= n;
	if (debug)
		printf("ins %d %d\n", l, r);
	prior.insert(case1(l, r));
	sec.insert(case2(l, r));
}

void del(int l, int r)
{
	if (l > n) l -= n;
	if (r > n) r -= n;
	if (debug)
		printf("del %d %d\n", l, r);
	prior.erase(case1(l, r));
	sec.erase(case2(l, r));
}

void init(int n, char *str)
{
	prior.clear();
	sec.clear();
	int cnt_dot = 0;
	for(int i = 1; i <= n; i++)
		cnt_dot += (str[i] == '.'), path[i] = (str[i] == 'X');
	if (cnt_dot == n)
	{
		ins(1, n);
		return;
	}
	
	for(int i = n + 1; i <= 2 * n; i++)
		str[i] = str[i - n];
	int l, r = n;
	while(str[r] == '.')
		r--;
	int cnt = 0, last;
	for(int i = r; i <= n + r; i++)
	{
		if (str[i] == 'X')
		{
			if (cnt)
				ins(last, i - 1);
			cnt = 0, last = i + 1;
		}
		else
			cnt++;
	}
}

void ppair(int l, int r)
{
	if (l == r)
		printf("%d", l);
	else
		printf("%d-%d", l, r);
}

void output(int l, int r)
{
	int rr = r;
	if (rr > n)
		rr -= n;
	if (al != l || rr != ar)
	{
		//printf("cmp %d %d vs %d %d\n", l, rr, al, ar);
		//exit(0);
		if (n < 2000)
		for(int i = 5 * n; i; i++)
		{
			path[i]++;
		}
	}
	if (r > n)
	{
		ppair(1, r - n);
		printf(",");
		ppair(l, n);
	} else
	{
		ppair(l, r);
	}
	printf("\n");
}

int dis(int a, int b)
{
	int res = b - a;
	if (res < 0)
		res += n;
	return res;
}

void Insert(int l, int r)
{
	if (l > n) l -= n;
	if (r > n) r -= n;
	set<case2> :: iterator it;
	if (sec.size())
	{
		it = sec.upper_bound(case2(r, n));
		if (it == sec.end())
			it = sec.begin();
		if (dis(r, it->l) == 1)
		{
			r = it->r;
			del(it->l, it->r);
		}
	}
	if (sec.size())
	{
		it = sec.upper_bound(case2(l, 0));
		if (it == sec.begin()) 
			it = sec.end();
		it--;
		if (dis(it->r, l) == 1)
		{
			l = it->l;
			del(it->l, it->r);
		}
	}
	if (l == r + 1)
	{
		//if (sec.size())
		//	while(1);
		l = 1, r = n;
	}
	ins(l, r);
}

void Delete(int l, int r, int sl, int sr)
{
	if (l > n) l -= n;
	if (r > n) r -= n;
	del(sl, sr);
	if (sr != r)
		ins(r % n + 1, sr);
}

void re(int l, int r, int v)
{
	if (l > n) l -= n;
	if (r > n) r -= n;
	if (l <= r)
	for(int i = l; i <= r; i++)
		path[i] = v;
	else
	{
		for(int i = l; i <= n; i++)
			path[i] = v;
		for(int i = 1; i <= r; i++)
			path[i] = v;
	}
}

void Calc(int x)
{
	al = -1;
	if (x > n)
		return ;
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		cnt += 1 - path[i];
	if (cnt == n)
	{
		for(int i = 1; i <= x; i++)
			path[i] = 1;
		al = 1, ar = x;
	} else
	{
		for(int i = n + 1; i <= 2 * n; i++)
			path[i] = path[i - n];
		int r = n, res = n + 1;
		while(path[r] == 0)
			r--;
		int cnt = 0, last;
		for(int i = r; i <= n + r; i++)
		{
			if (path[i])
			{
				if (cnt >= x)
				{
					if (cnt < res)
					{
						res = cnt;
						al = last, ar = last + x - 1;
					}
				}
				cnt = 0, last = i + 1;
			}
			else
				cnt++;
		}
	}
	if (al > n) al -= n;
	if (ar > n) ar -= n;
	re(al, ar, 1);
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);

	scanf("%d %d\n", &n, &m);
	gets(str + 1);
	init(n, str);
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%s %d%*c", str + 1, &x);
		q[i].key = x;
		q[i].l = -1;
		if (str[1] == 'P')
		{
			Calc(x);
			set<case1>::iterator it;
			it = prior.lower_bound(case1(1, x));
			if (it == prior.end())
			{
				printf("NO ROOM\n");
				//if (al != -1)
				//	while(1);
				continue;
			}
			q[i].l = it->l;
			q[i].r = it->l + x - 1;
			output(q[i].l, q[i].r);
			Delete(it->l, it->l + x - 1, it->l, it->r);
		} else
		{
			if (q[x].l != -1)
			{
				re(q[x].l, q[x].r, 0);
				Insert(q[x].l, q[x].r);
			}
		}/*
		for(int j = 1; j <= n; j++)
			printf("%d", path[j]);
		printf("\n");*/
	}
	return 0;
}
