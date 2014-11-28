#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const long long inf = 1e17;
const int MAXN = 200;

long long dis[MAXN][MAXN];
int n, m, r;
long long pro[MAXN];
vector<int> other[MAXN], length[MAXN];
struct node
{
	long long time, fix;
	node(){}
	node(long long _fix, long long _time) : fix(_fix), time(_time) {}
	friend int operator<(node a, node b)
	{
		return a.time < b.time;
	}
};
vector<node> buc;
long long ans = inf;

long long aabs(long long a)
{
	if (a > 0)
		return a;
	return -a;
}

void solve(int a, int b, int c)
{
	if (c < 2 * r)
		return ;
	buc.clear();
	long long now = 0, fix = 0;
	for(int i = 1; i <= n; i++)
	{
		now += (long long)pro[i] * min(dis[a][i] + r, dis[b][i] + (c - r));			
		long long t = (dis[a][i] + dis[b][i] + c) / 2 - dis[a][i];
		if (t <= r)
			fix -= pro[i];
		else
		if (t >= c - r)
			fix += pro[i];
		else
		{
			buc.push_back(node(-pro[i] * 2, t));
			fix += pro[i];
		}
	}
	buc.push_back(node(0, c - r));
	sort(buc.begin(), buc.end());	
	if (now < ans)
		ans = now;
	for(int i = 0; i < buc.size(); i++)
	{
		long long len = buc[i].time - (i == 0 ? r : buc[i - 1].time);
		now += (long long)fix * len;
		fix += buc[i].fix;		
		if (now < ans)
			ans = now;
	}
	long long pp = 0;
	for(int i = 1; i <= n; i++)
		pp += (long long)pro[i] * min(dis[b][i] + r, dis[a][i] + (c - r));	
	if (now != pp)
		while(1);
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &r); r *= 10;
	for(int i = 1; i <= n; i++)
		scanf("%I64d", &pro[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dis[i][j] = ((i == j) ? 0 : inf);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c); c *= 10;
		other[a].push_back(b); 
		length[a].push_back(c);
		dis[a][b] = min(dis[a][b], (long long)c);
		dis[b][a] = dis[a][b];
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= n; k++)
				dis[j][k] = min(dis[j][i] + dis[i][k], dis[j][k]);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < other[i].size(); j++)
			solve(i, other[i][j], length[i][j]);
	if (n == 1 && r == 0)
		printf("0\n");
	else
	if (ans >= inf / 2)
		printf("-1\n");
	else
		printf("%I64d.%05I64d\n", ans / 100000, ans % 100000);
	return 0;
} 
