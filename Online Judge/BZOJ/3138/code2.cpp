#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 70000;
const int inf = 200000;
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

int cmp(node a, node b)
{
	return a.pos < b.pos;
}

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
	for(int i = 0; i < MAXM; i++)
		hash[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < MAXM; j++)
		{
			pre[i][j].pos = hash[j], pre[i][j].val = j;
			if (j == 'e' - 'a')
				pre[i][j].pos = i, pre[i][j].val = str[i] - 'a';
		}
		hash[str[i] - 'a'] = i;
		sort(pre[i], pre[i] + MAXM, cmp);
	}
	/* first is 'e'
	int s = 1;
	while(str[s] == 'e' && s <= n)
		s++;
	for(int i = s; i <= n; i++)
		str[i - s + 1] = str[i];
	n -= s - 1;
	*/
	for(int i = 0; i < MAXN; i++)
		next[n + 1][i] = n + 1;
	/*
	int laste = -1;
	for(int i = n; i >= 1; i--)
		if (str[i] == 'e')
		{
			laste = i;
			break;
		}
	if (laste == -1)
	{
		printf("0\n");
		exit(0);
	}
	for(int i = 1; i <= n; i++)
		dis[i] = inf;
	for(int i = laste + 1; i <= n; i++)
		dis[i] = i;
	for(int i = laste; i >= 1; i--)
		if (str[i] != 'e')
		{
			for(int j = 0; j < MAXM; j++)
				if (j != 'e' - 'a')
				{
					dis[i] = min(dis[i], dis[next[i][j]] + 2);
				}
		}
	*/
}

int cut[20], ep = 0;

void Work()
{
	ans2 = inf;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= MAXM; j++)
			f[i][j] = inf;
	f[1][MAXM] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int s = 0; s <= MAXM; s++)
		if (f[i][s] < inf)
		{
			//f[i][MAXM - 1] = min(f[i][MAXM - 1], f[i][s] + 2);
			int ne = next[i]['e' - 'a'];
			if (ne == i)
			{
				ans2 = min(ans2, f[i][s]);
				continue;
			}
			for(int j = 0; j < s; j++)
			{
				if (pre[i][j].pos != i && pre[i][j].val == str[i] - 'a')
				{
					f[i][MAXM] = min(f[i][MAXM], f[i][s] + 2);
					continue;
				}
				int nj = pre[i][j].val;
				int npos = next[i][nj];
				//ans2 = min(ans2, f[i][s] + 2 + dis[npos] - ne);
				if (ne > npos)
				{
					f[npos][MAXM] = min(f[npos][MAXM], f[i][s] + 2);
				} else
				{
					int t = 0, me = mext[ne];
					while((t + 1) <= MAXM && me >= pre[npos][t].pos)
						t++;
					f[npos][t] = min(f[npos][t], f[i][s] + 2 + npos - ne);
				}
			}
			for(int j = 0; j < MAXM; j++)
			if (j != 'e' - 'a')
			{
				int npos = next[i][j];
				++ep;
				for(int k = s; k < MAXM; k++)
				{
					if (pre[i][k].val == str[i] - 'a' && pre[i][k].pos != i)
						continue;
					int x = pre[i][k].val;
					cut[x] = ep;
				}
				int t = 0;
				while((t + 1) <= MAXM && i >= pre[npos][t].pos && cut[pre[npos][t].val] != ep)
					t++;
				f[npos][t] = min(f[npos][t], f[i][s] + 2 + npos - i);
			}
		}
	}
//	for(int i = 1; i <= n; i++)
//		printf("%d ", f[i]);
//	printf("\n");
//	for(int i = 1; i <= n; i++)
//		printf("%d ", mext[i]);
//	printf("\n");
}

int main()
{
	freopen("vim.in", "r", stdin);
	freopen("vim.out", "w", stdout);
	scanf("%d\n", &n);
	gets(str + 1);
	Pre();
	Work();
	printf("%d\n", ans + ans2);
	return 0;
} 
