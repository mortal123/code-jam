#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MAXN = 30;
map<int, map<int, int> > dp;	

int src[MAXN], tar[MAXN], n;
vector<int> vecA, vecB;
vector<pair<int, int> > vpa, vpb;
	
int CalcDight(int x)
{
	int res = 0;
	for(; x; x >>= 1)
		res += ((x & 1) > 0);
	return res;
}

void Calc(int x, int y)
{
	int res = CalcDight(vpa[x].second) + CalcDight(vpb[y].second) - 1;
	for(int i = 0; i < x; i++)
	{
		if ((vpa[i].second & vpa[x].second) != vpa[i].second)
			continue;
		map<int, map<int, int> >::iterator be = dp.find(vpa[i].second);
		if (be == dp.end())
			continue;
		for(map<int, int>::iterator it = (be->second).begin(); it != (be->second).end(); ++it)
		{
			int now = it->first;
			if ((now & vpb[y].second) != now)
				continue;
			res = min(res, dp[vpa[i].second][now] + dp[vpa[x].second ^ vpa[i].second][vpb[y].second ^ now]);
		}
	}
	dp[vpa[x].second][vpb[y].second] = res;
	//printf("%d %d   %d %d   %d\n", vpa[x].second, vpb[y].second, vpa.size(), vpb.size(), dp[7][7]);
}
	
int Solve()
{
	dp.clear();
	for(int i = 0; i < (1 << vecA.size()); i++)
	{
		int val = 0;
		for(int j = 0; j < vecA.size(); j++)
			if (i & (1 << j))
				val += vecA[j];
		vpa.push_back(make_pair(val, i));
	}
	for(int i = 0; i < (1 << vecB.size()); i++)
	{
		int val = 0;
		for(int j = 0; j < vecB.size(); j++)
			if (i & (1 << j))
				val += vecB[j];
		vpb.push_back(make_pair(val, i));
	}
	sort(vpa.begin(), vpa.end());
	sort(vpb.begin(), vpb.end());
	int pt = 1;
	for(int i = 0; i < vpa.size(); i++)
	{
		while(pt < vpb.size() && vpb[pt].first < vpa[i].first)
			pt++;
		if (pt == vpb.size())
			break;
		for(int j = pt; j < vpb.size() && vpb[j].first == vpa[i].first; j++)
			Calc(i, j);
	}
	return dp[(1 << vecA.size()) - 1][(1 << vecB.size()) - 1];
}	

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &src[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &tar[i]);
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		int now = tar[i] - src[i];
		if (now > 0)
			vecA.push_back(now);
		if (now < 0)
			vecB.push_back(-now);
		sum += now;
	}
	if (!sum)
		printf("%d\n", Solve());
	else
		printf("-1\n");
	return 0;
}
