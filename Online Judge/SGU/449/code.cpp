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

void Dfs(int root)
{
	StackN[top = 1] = root;
	StackE[top] = 0;
	int num = 0, cnt = 0;
	if (root <= n)
		idx[++num] = root;
	else
		cnt++;
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
			idx[++num] = y;
		else
			cnt++;
	}
	if (cnt != m)
		while(1);
	if (num != n)
	{
		int len = 0;
		idxx[++len] = idx[1];
		memset(hash, 0, sizeof(hash));
		for(int i = 1; i <= num; i++)
			hash[idx[i]] = 1;
		for(int i = 1; i <= n; i++)
			if (!hash[i])
				idxx[++len] = i;
		sort(idxx + 1, idxx + len + 1);
		int top = 0;
		for(int i = 1; i <= len; i++)
		{
			if (idxx[i] == idx[1])
			{
				for(int j = 1; j <= num; j++)
					bak[++top] = idx[j];
			} else
				bak[++top] = idxx[i];
		}
		for(int i = 1; i <= n; i++)
			idx[i] = bak[i];
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
	if (m)
		Dfs(sa[1] + n);
	else
		Dfs(1);
	for(int i = 1; i <= q; i++)
	{
		int qx;
		scanf("%d", &qx);
		printf("%d\n", idx[qx]);
	}
	return 0;
}
