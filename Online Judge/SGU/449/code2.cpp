#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 400000;

int fa[MAXN], idx[MAXN], sa[MAXN], MinNum[MAXN], hash[MAXN], idxx[MAXN], bak[MAXN];
struct Hor
{
	vector<int> vert;
	int high;
	friend int operator <(Hor a, Hor b)
	{
		return a.high < b.high;
	}
}hor[MAXN];
class Combin
{
	public:
		int fa[MAXN];
		void clear(int n)
		{
			for(int i = 1; i <= n; i++)
				fa[i] = i;
		}
		int find(int x)
		{
			int p = x, t;
			while(fa[p] != p)
				p = fa[p];
			while(x != p)
			{
				t = fa[x];
				fa[x] = p;
				x = t;
			}
			return x;
		}
		void Comb(int x, int y)
		{
			x = find(x);
			y = find(y);
			if (x != y)
				fa[y] = x;
		}
}C;
vector<int> e[MAXN];

int n, m, q;

int cmp(int a, int b)
{
	return hor[a] < hor[b];
}

int cmp2(int a, int b)
{
	return MinNum[a] < MinNum[b];
}

int StackN[MAXN], StackE[MAXN], top;
vector <int> queue[MAXN];
vector<pair<int, int> > compare;

void Dfs(int num, int root)
{
	StackN[top = 1] = root;
	StackE[top] = 0;
	hash[root] = 1;
	if (root <= n)
		queue[num].push_back(root);
	while(top)
	{
		int x = StackN[top];
		if (StackE[top] == e[x].size())
		{
			top--;
			continue;	
		}
		int y = e[x][StackE[top]];
		StackE[top]++;
		StackN[++top] = y; StackE[top] = 0;
		if (y <= n)
			queue[num].push_back(y);
		hash[y] = 1;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &hor[i].high);
		int l;
		hor[i].vert.clear();
		scanf("%d", &l);
		for(int j = 1; j <= l; j++)
		{
			int x;
			scanf("%d", &x);
			hor[i].vert.push_back(x);
		}
		sa[i] = i;
	}
	sort(sa + 1, sa + m + 1, cmp);
	
	C.clear(n + m);
	for(int i = 1; i <= n + m; i++)
		e[i].clear();
	for(int i = 1; i <= n; i++)
		MinNum[i] = i;
	for(int i = n + 1; i <= n + m; i++)
		MinNum[i] = n + 10;
	for(int i = m; i >= 1; i--)
	{
		int pos = sa[i];
		for(int j = 0; j < hor[pos].vert.size(); j++)
		{
			int x = hor[pos].vert[j]; x = C.find(x);
			C.Comb(pos + n, x);
			MinNum[pos + n] = min(MinNum[pos + n], MinNum[x]);
			e[pos + n].push_back(x);
			//printf("%d %d\n", pos + n, x);
		}
	}
	//return 0;
	for(int i = 1; i <= n + m; i++)
		sort(e[i].begin(), e[i].end(), cmp2);
	int num = 0;
	memset(hash, 0, sizeof(hash));
	for(int i = 1; i <= m; i++)
		if (!hash[sa[i] + n])
			Dfs(++num, sa[i] + n);
	for(int i = 1; i <= n; i++)
		if (!hash[i])
			Dfs(++num, i);
	compare.clear();
	for(int i = 1; i <= num; i++)
		compare.push_back(make_pair(queue[i][0], i));
	sort(compare.begin(), compare.end());
	int top = 0;
	for(int i = 0; i < compare.size(); i++)
	{
		int pos = compare[i].second;
		for(int j = 0; j < queue[pos].size(); j++)
			idx[++top] = queue[pos][j];
	}
	for(int i = 1; i <= q; i++)
	{
		int qx;
		scanf("%d", &qx);
		printf("%d\n", idx[qx]);
	}
	return 0;
}
