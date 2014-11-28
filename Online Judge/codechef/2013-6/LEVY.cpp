#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 10000;

int ans[MAXN + 10];
int prim[MAXN + 10], check[MAXN + 10];

int main()
{
	int top = 0;
	for(int i = 2; i <= MAXN; i++)
		if (!check[i])
		{
			prim[++top] = i;
			for(int j = i + i; j <= MAXN; j += i)
				check[j] = 1;
		}
	for(int i = 1; i <= top; i++)
		for(int j = 1; j <= top; j++)
		{
			if (prim[i] + 2 * prim[j] > MAXN)
				break;
			ans[prim[i] + 2 * prim[j]]++;
		}
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
