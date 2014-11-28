#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2222;


int n, i, j, x, tag;
int h1[2005], h2[2005];
int a[2005][2005], b[2005][2005], s[2005], tot;

void dfs1(int i);
void dfs2(int i);

int main()
{
	//freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &x);
			if (i == j)
				continue;
			if (x)
				a[i][++a[i][0]] = j, b[j][++b[j][0]] = i;
		}
	for (i = 1; i <= n; i++)
		if (!h1[i])
			dfs1(i);
	while (tot)
	{
		if (!h2[s[tot]])
		{
			++tag;
			if (tag > 1)
			{
				printf("NO\n");
				return 0;
			}
			
			dfs2(s[tot]);
		}
		
		tot--;
	}
	
	printf("YES\n");
	return 0;
}

void dfs1(int i)
{
	int x;
	h1[i] = 1;
	for (x = 1; x <= a[i][0]; x++)	
		if (!h1[a[i][x]])
			dfs1(a[i][x]);
	s[++tot] = i;
}

void dfs2(int i)
{
	int x;
	h2[i] = 1;
	for (x = 1; x <= b[i][0]; x++)
		if (!h2[a[i][x]])
			dfs2(a[i][x]);
}
