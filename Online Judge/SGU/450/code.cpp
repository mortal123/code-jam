#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 200, MAXC = 200000, inf = 200000000;

class Event
{
	public:
		int who, do_what, time; // eat_in : 1 eat_leave : -1  wait_leave : 0
	Event(int _who = 0, int _do_what = 0, int _time = 0) : 
		who(_who), do_what(_do_what), time(_time) {}
	friend bool operator < (Event a, Event b)
	{
		if (a.time != b.time)
			return a.time > b.time;
		return a.do_what > b.do_what;
	}
};

priority_queue<Event> event;
queue<int> Wait;

class Customer
{
	public:
		int T, P, W, E, Counter, Pos;
};
class Value
{
	public:
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
		int L, Mid, R, MidPos;
	void clear(int l = 1, int r = -1, int val = 0)
	{
		if (r == -1)	
			r = size;
		for(int i = l; i <= r; i++)
			seat[i] = val;
	}
	void update()
	{
		int cnt = 0;
		for(int i = 1; i <= size; i++)
			cnt += (!seat[i]);
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
			L = l - 1; R = size - r; Mid = MidPos = 0;
			for(int i = l, now = 0; i <= r; i++)
				if (seat[i] == 0)
				{
					now++;
					if (now > Mid)
						Mid = now, MidPos = i - now + 1;
				} else
				{
					now = 0;
				}
		}
	}
};
int debug = 0;
int n, m, t;
Customer custom[MAXC];
Counter Count[MAXN];
int leave[MAXC];
double ans = 0;

int Find(int who)
{
	int len = custom[who].P, bestl = -1, bestr = -1, wCount = -1;
	Value res, comp;
	res.sl = -1, res.sr = -1;
	for(int i = 1; i <= n; i++)
	if (Count[i].size >= len)
	{
		if (Count[i].empty)
		{
			comp.sl = inf;
			comp.sr = inf;
			if (res < comp)
			{
				res = comp;
				bestl = 1, bestr = len;
				wCount = i;
			}
		} else
		{
			//L  ¿¿Ç½×ø 
			if (Count[i].L >= len)
			{
				comp.sl = inf;
				comp.sr = Count[i].L - len;
				if (res < comp)
				{
					res = comp;
					bestl = 1;
					bestr = len;
					wCount = i;
				}
			} 
			if (Count[i].Mid >= len)
			{
				comp.sl = (Count[i].Mid - len) / 2; comp.sr = Count[i].Mid - len - comp.sl;
				if (res < comp)
				{
					res = comp;
					bestl = Count[i].MidPos + comp.sl;
					bestr = Count[i].MidPos + comp.sl + len - 1;
					wCount = i;
				}
			}
			if (Count[i].R >= len)
			{
				comp.sl = Count[i].R - len;
				comp.sr = inf;
				if (res < comp)
				{
					res = comp;
					bestr = Count[i].size;
					bestl = Count[i].size - len + 1;
					wCount = i;
				}
			}
		}
	}
	if (bestl == -1)
		return 0;
	Count[wCount].clear(bestl, bestr, 1);
	Count[wCount].update();
	custom[who].Pos = bestl;
	custom[who].Counter = wCount;
	if (debug) printf("%d sit at %d~%d in count %d\n",who, bestl, bestr, wCount);
	return 1;
}

void ServeWait(int time)
{
	if (time >= t)
		return;
	if (debug) printf("ServeWait\n");
	while(!Wait.empty())
	{
		int x = Wait.front();
		if (leave[x])
		{
			Wait.pop();
			continue;
		}
		if (Find(x))
		{
			event.push(Event(x, -1, time + custom[x].E));
			Wait.pop();
			ans += custom[x].P * (double)(custom[x].W - (time - custom[x].T)) / custom[x].W;
		} else
			break;
	}
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &t);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &Count[i].size);
		Count[i].clear();
		Count[i].update();
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d %d %d %d", &custom[i].T, &custom[i].P, &custom[i].W, &custom[i].E);
		event.push(Event(i, 1, custom[i].T));
		event.push(Event(i, 0, custom[i].T + custom[i].W));
		custom[i].Pos = 0;
	}
	while(!event.empty())
	{
		Event Tmp = event.top();
		event.pop();
		if (debug) printf("\nevent happen at time : %d\n", Tmp.time);
		//eat
		if (Tmp.do_what == 1)
		{
			if (debug) printf("%d enter\n", Tmp.who);
			Wait.push(Tmp.who);
			ServeWait(Tmp.time);
		} else // eat_leave
		if (Tmp.do_what == -1)
		{
			if (debug) printf("%d eat_leave\n", Tmp.who);
			int who = Tmp.who;
			int cnum = custom[who].Counter;
			Count[cnum].clear(custom[who].Pos, custom[who].Pos + custom[who].P - 1);
			Count[cnum].update();
			if (!event.empty())
			{
				Event Tmp2 = event.top();
				if (Tmp2.do_what == -1 && Tmp.time == Tmp2.time)   // successive leave
					continue;
			}
			ServeWait(Tmp.time);
		} else // wait_leave
		{
			if (!custom[Tmp.who].Pos)
			{
				if (debug) printf("%d wait_leave\n", Tmp.who);
				leave[Tmp.who] = 1, ans -= custom[Tmp.who].P;
			}
			ServeWait(Tmp.time);
		}
	}
	double div_m = 0;
	for(int i = 1; i <= m; i++)
		div_m += custom[i].P;
	printf("%.16lf\n", ans / div_m);
	return 0;
}
