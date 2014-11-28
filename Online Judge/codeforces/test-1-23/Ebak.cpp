#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 20000, base = 26, MAXM = MAXN;
int n;
struct eglist
{
	int other[MAXM * 2], succ[MAXM * 2], last[MAXM * 2], sum;
	void clear()
	{
		for(int i = 0; i <= n; i++)
			last[i] = 0;
		sum = 1;
	}
	void AddEdge(int a, int b)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum;
	}
}e;

char str[MAXN], cstr[MAXN][10];
int cnt[30], S, T, m, vis[MAXN], next[MAXN];
char ss[MAXN], ans[MAXN];

int find(int x)
{
	for(int i = e.last[x]; i; i = e.succ[i])
	{
		int y = e.other[i];
		if (vis[y])
			continue;
		vis[y] = 1;
		if (next[y] == 0 || find(next[y]))
		{
			next[y] = x;
			return 1;
		}
	}
	return 0;
}

int calc(int pos, char val)
{
	e.clear();
	m = 0;
	for(int i = 0; i < 26; i++)
		for(int j = 1; j <= cnt[i]; j++)
			ss[++m] = i + 'a';
	ans[pos] = val;
	for(int i = 1; i <= pos; i++)
	{
		for(int j = 1; j <= m; j++)
			if (ans[i] == ss[j])
				e.AddEdge(i, j);
	}
	for(int i = pos + 1; i <= n; i++)
	{
		int len = strlen(cstr[i] + 1);
		for(int j = 1; j <= len; j++)
			for(int k = 1; k <= m; k++)
				if (cstr[i][j] == ss[k])
					e.AddEdge(i, k);
	}
	for(int i = 1; i <= n; i++)
		next[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			vis[j] = 0;
		if (!find(i))
			return 0;
	}
	return 1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	gets(str + 1);
	n = strlen(str + 1);
	for(int i = 1; i <= n; i++)
		cnt[str[i] - 'a']++;
	for(int i = 1; i <= n; i++)
	{
		gets(cstr[i] + 1);
		sort(cstr[i] + 1, cstr[i] + strlen(cstr[i] + 1) + 1);
	}
	for(int i = 1; i <= n; i++)
	{
		int len = strlen(cstr[i] + 1);
		int flag = 0;
		char choose;
		for(int j = 1; j <= len; j++)
		{
			if (calc(i, cstr[i][j]))
			{
				flag = 1;
				choose = cstr[i][j];
				break;
			}
		}
		if (!flag)
		{
			printf("NO SOLUTION\n");
			exit(0);
		} else
		{
			ans[i] = choose;
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%c", ans[i]);
	printf("\n");
	return 0;
}
