#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 200000;

int n, s[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &s[i]);
	printf("YES\n");
	for(int i = 1; i <= n; i++)
	{
		int d = n * 2 / 3;
		if (i <= d)
			printf("0");
		else
			printf("%d", s[i]);
		if (i != n)
			printf(" ");
		else
			printf("\n");
	}
	for(int i = 1; i <= n; i++)
	{
		int d = n * 2 / 3;
		if (i > d)
			printf("0");
		else
			printf("%d", s[i]);
		if (i != n)
			printf(" ");
		else
			printf("\n");
	}
	return 0;
}
