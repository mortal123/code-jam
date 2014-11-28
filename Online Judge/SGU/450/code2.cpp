#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 200, MAXC = 200000, inf = 200000000;

typedef pair<int, int> pint;

//pair<int, int> first = time, second = who;
priority_queue<pint, vector<pint>,  greater<pint> > leave, come;

class Customer
{
	public:
		int T, P, W, E;
};
class Value
{
	int sl, sr;
	friend int operator <(Value a, Value b)
	{
		if (min(a.sl, a.sr) != min(b.sl, b.sr))
			return min(a.sl, a.sr) < min(b.sl, b.sr);
		else
			return max(a.sl, a.sr) < max(b.sl, b.sr);
	}
	Value make_val(int a, int b)
	{
		Value res;
		res.sl = a;
		res.sr = b;
		return res;
	}
};
class Counter
{
	public:
		int seat[MAXN], size;
		bool empty;
		Value L, Mid, R;
	void clear()
	{
		for(int i = 1; i <= size; i++)
			seat[i] = 0;
	}
	void update()
	{
		int cnt = 0;
		for(int i = 1; i <= size; i++)
			cnt += seat[i];
		if (cnt == size)
		{
			empty = 1;
			L = Mid = R = size;
		} else
		{
			empty = 0;
			int l = 1, r = size;
			while(!seat[l]) l++;
			while(!seat[r]) r--;
			L = l - 1; R = size - r; 
			for(int i = l, now = 0; i <= r; i++)
				if (seat[i] == 0)
				{
					now++;
					Mid = max(Mid, now);
				} else
				{
					now = 0;
				}
		}
	}
};

int n, m, t;
int c[MAXN];
Customer custom[MAXC];
Counter count[MAXN];
double ans = 0;

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &t);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &count[i].size);
		count[i].clear();
		count[i].update();
	}
	come.clear();
	leave.clear();
	for(int i = 1; i <= m; i++)
	{
		scanf("%d %d %d %d", &custom[i].T, &custom[i].P, &custom[i].W, &custom[i].E);
		come.push(make_pair(custom[i].T, i));
	}
	while(!come.empty() || !leave.empty())
	{
		
	}
	return 0;
}
