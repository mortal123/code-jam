#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
const int MAXM = 10;
const int inf = 2000000;
char str[MAXN];

int mext[MAXN], next[MAXN][12], f[MAXN];
int ans, ans2, n, fr[MAXN];

void Pre()
{
	ans = 0;
	int hash[MAXM + 10];
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
}

int step[MAXN];

void check(int final)
{
	int top = 0;
	while(final != 1)
	{
		step[++top] = final;
		final = fr[final];
	}
	int last = 1, cnt = 0;
	for(int i = top; i >= 1; i--)
	{
		int now = step[i];
		printf("f%c", str[now]); cnt += 2; 
		int ne = next[last]['e' - 'a'];
		if (ne < now)
			for(int j = now; j >= ne; j--)
			{
				printf("h"); cnt++;
				if (str[j] == 'e')
					printf("x"), cnt++;
			}
	}
}

int main()
{
	freopen("vim.in", "r", stdin);
	scanf("%d\n", &n);
	gets(str + 1);
	Pre();
	for(int i = 1; i <= n; i++)
		f[i] = inf;
	f[1] = 0;
	ans2 = inf;
	int final = 0;
	for(int i = 1; i <= n; i++)
	{
		if (next[i]['e' - 'a'] == i)
			if (f[i] < ans2)
				ans2 = min(ans2, f[i]), final = i;
		for(int j = 0; j < MAXM; j++)
			if (j != 'e' - 'a')
			{
				int npos = next[i][j];
				int ne = next[i]['e' - 'a'];
				if (npos < ne)
				{
					if (f[i] + 2 < f[npos])
						fr[npos] = i, f[npos] = min(f[npos], f[i] + 2);
				}
				else
				{
					if (f[i] + 2 + npos - ne < f[npos])
						fr[npos] = i, f[npos] = min(f[npos], f[i] + 2 + npos - ne);
			}
	}
	printf("%d\n", ans + ans2);
	check(final);
	return 0;	
} 
