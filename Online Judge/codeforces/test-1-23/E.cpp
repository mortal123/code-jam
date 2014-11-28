#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 20000, base = 26;
int n;
struct eglist
{
	int other[MAXM * 2], succ[MAXM * 2], last[MAXM * 2], sum;
	void clear()
	{
		for(int i = 0; i <= n + base + 1; i++)
			last[i] = 0;
		sum = 1;
	}
	void AddEdge(int a, int b, int c)
	{
		other[++sum] = b, succ[sum] = last[a], last[a] = sum, G[sum] = c;
		other[++sum] = a, succ[sum] = last[b], last[b] = sum, G[sum] = 0; 
	}
}e;

char str[MAXN], cstr[MAXN][10];
int count[30], S, T;

int calc(int pos, char val)
{
	e.clear();
	S = 0, T = n + base + 1;
	count[val - 'a']--;
	for(int i = 1; i <= 26; i++)
		e.AddEdge(S, i, count[i - 1]);
	for(int i = pos + 1; i <= n; i++)
	{
		int m = strlen(cstr[i] + 1);
		for(int j = 1; j <= m; j++)
			e.AddEdge(cstr[i][j] - 'a' + 1, i + 26, 1);
		e.AddEdge(i + 26, T, 1);
	}
	count[val - 'a']++;
}

int main()
{
	gets(str + 1);
	n = strlen(str + 1);
	for(int i = 1; i <= n; i++)
		count[str[i] - 'a']++;
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
			count[choose - 'a']--;
		}
	}
	return ;
}
