#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

const int MAXN = 110000;
const int inf = 200000000;

int n, v;

struct node
{
	int x, t, idx;
}event[MAXN];

pair<int, int> rec[MAXN];

int begin[MAXN], len;

set<pair<long long, int> > pre[MAXN], last[MAXN];

void PreTask()
{
	len = 0;
	for(int i = 1; i <= n; i++)
		rec[i].first = event[i].x, rec[i].second = i;
	sort(rec + 1, rec + n + 1);
	for(int i = 1; i <= n; i++)
	{
		if (i == 1 || rec[i].first != rec[i - 1].first)
			++len;
		event[rec[i].second].idx = len;
	}
}

int aabs(int x)
{
	if (x < 0)
		return -x;
	return x;
}

int cmp(node a, node b)
{
	return a.t < b.t;
}

inline int lowbit(int x)
{
	return x & (-x);
}

void insPre(set<pair<long long, int> > h[], int pos, long long key, int val)
{
	set<pair<long long, int> > :: iterator it, it2, it3;
	for(int i = pos; i <= len; i += lowbit(i))
	{
		h[i].insert(make_pair(key, val));
		it3 = it = h[i].lower_bound(make_pair(key, val));
		while(1)
		{
			it2 = it;
			it++;
			if (it == h[i].end())
				break;
			if (it2->second >= it->second)
			{
				h[i].erase(it);
				it = it2;
			} else
				break;
		}
		it2 = it = it3;
		if (it != h[i].begin())
		{
			it--;
			if (it->second >= it2->second)
				h[i].erase(it2);
		}
	}
}

void insLast(set<pair<long long, int> > h[], int pos, long long key, int val)
{
	set<pair<long long, int> > :: iterator it, it2, it3;
	for(int i = pos; i <= len; i += lowbit(i))
	{
		h[i].insert(make_pair(key, val));
		it3 = it = h[i].lower_bound(make_pair(key, val));
		while(1)
		{
			it2 = it;
			if (it == h[i].begin())
				break;
			it--;
			if (it2->second >= it->second)
			{
				h[i].erase(it);
				it = it2;
				
			} else
				break;
		}
		it2 = it = it3;
		it++;
		if (it != h[i].end())
		{
			if (it->second >= it2->second)
				h[i].erase(it2);
		}
	}
}

int askPre(int pos, long long P)
{
	int res = -inf;
	set<pair<long long, int> > :: iterator it;
	for(int i = pos; i; i -= lowbit(i))
	{
		it = pre[i].upper_bound(make_pair(P, inf));
		if (it == pre[i].begin())
			continue;
		it--;
		res = max(res, it->second);
	}
	return res;
}

int askLast(int pos, long long P)
{
	int res = -inf;
	set<pair<long long, int> > :: iterator it;
	for(int i = pos; i; i -= lowbit(i))
	{
		it = last[i].lower_bound(make_pair(P, -1));
		if (it == last[i].end())
			continue;
		res = max(res, it->second);
	}
	return res;
}

int Solve(int begin[])
{
	int res = 0;
	for(int i = 1; i <= len; i++)
		pre[i].clear(), last[i].clear();
	for(int i = 1; i <= n; i++)
	{
		int val = -1, idx = event[i].idx, xi = event[i].x, ti = event[i].t;
		val = max(begin[i], 1 + max(askPre(len + 1 - idx, (long long)xi + v * ti), askLast(idx, (long long)xi - v * ti)));
		res = max(res, val);
		if (val <= 0)
			continue;
		insPre(pre, len + 1 - idx, (long long)xi + v * ti, val);
		insLast(last, idx, (long long)xi - v * ti, val);
	}
	return res;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d %d", &event[i].x, &event[i].t);
	}
	scanf("%d", &v);
	PreTask();
	sort(event + 1, event + n + 1, cmp);
	// begin at 0
	//return 0;
	memset(begin, 0, sizeof(begin));
	for(int i = 1; i <= n; i++)
		if (v * event[i].t >= aabs(event[i].x))
			begin[i] = 1;
	printf("%d ", Solve(begin));
	for(int i = 1; i <= n; i++)
		begin[i] = 1;
	printf("%d\n", Solve(begin));
	
	return 0;
}
