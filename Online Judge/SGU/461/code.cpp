#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

char str[1010][1100];
int n = 0, size[1100];

void Dfs(int l, int r, int s, int inher)
{
	if (l > r)
		return;
	if (l == r)
	{
		if (inher)
			printf("<li>\n");
		for(int i = s; i < size[l]; i++)
			printf("%c", str[l][i]);
		printf("\n");
		if (inher)
			printf("</li>\n");
		return;
	}
	int flag = 1;
	char ch = str[l][s];
	for(int i = l + 1; i <= r; i++)
	{
		if (str[i][s] != ch)
			flag = 0;
	}			
	int away = 0;
	if (flag && inher && (ch == '*' || ch == '#'))
		printf("<li>\n");
	if (flag && ch == '*')
	{
		printf("<ul>\n");
		Dfs(l, r, s + 1, 1);
		printf("</ul>\n");
		away = 1;
	} else
	if (flag && ch == '#')
	{
		printf("<ol>\n");
		Dfs(l, r, s + 1, 1);
		printf("</ol>\n");
		away = 1;
	}		
	if (flag && inher && (ch == '*' || ch == '#'))
		printf("</li>\n");
	if (away)
		return;
	int last = l;
	for(int i = l; i <= r; i++)
	{
		if (str[i][s] != '*' && str[i][s] != '#' || i != l && str[i][s] != str[i - 1][s])
		{
			Dfs(last, i - 1, s, inher);
			last = i;
		}
	}
	Dfs(last, r, s, inher);
}

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	++n;
	while(gets(str[n]))
	{
		size[n] = strlen(str[n]);
		n++;
	}
	n--;
	Dfs(1, n, 0, 0);
	return 0;
}
