#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 70000;
const int inf = 200000;
const int iif = 20000;
const int MAXM = 10;

int n;
int next[MAXN + 10][MAXM + 2], mext[MAXN + 10];
int f[MAXN + 10][MAXM + 2], ans, ans2;
char str[MAXN + 10];
struct node
{
	int pos;
	int val;
}pre[MAXN + 10][MAXM + 3];

int q[MAXN], dis[MAXN], visit[MAXN];

struct eglist
{
	int val[MAXN * 10 * 2], other[MAXN * 10 * 2], succ[MAXN * 10 * 2], last[MAXN * 2], sum;
	void clear()
	{
		memset(last, 0, sizeof(last));
		sum = 0;
	}
	void AddEdge(int a, int b, int v)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum, val[sum] = v; 
	}
}e;

void Pre()
{
	ans = 0;
	int hash[11];
	for(int i = 0; i < MAXM; i++)
		hash[i] = n + 1;
	for(int i = n; i >= 1; i--)
	{
		mext[i] = (str[i] == 'e') ? mext[i + 1] : i;
		for(int j = 0; j < MAXM; j++)
		{
			if (hash[j] <= n)
				next[i][j] = hash[j];
			else
				next[i][j] = i;
		}
		hash[str[i] - 'a'] = i;
		if (str[i] == 'e')
			ans++;
	}
	for(int i = 1; i <= n; i++)
	{
		if (str[i] == 'e')
		{
			e.AddEdge(i, i + n, -iif);
		} else
			e.AddEdge(i, i + n, 0);
		for(int j = 0; j < MAXM; j++)
			if (next[i][j] != i)
				e.AddEdge()
	}
}

void Work()
{
	ans2 = inf;
	
}

int main()
{
	freopen("vim13.in", "r", stdin);
	scanf("%d\n", &n);
	gets(str + 1);
	Pre();
	Work();
	printf("%d\n", ans + ans2);
	return 0;
} 
