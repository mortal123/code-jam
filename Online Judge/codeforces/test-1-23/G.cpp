#include <cstdio>
#include <cstdlib>

const int MAXN = 20000;

long long n, res = 0;
int k, a[MAXN];

int main()
{
	freopen("great.in", "r", stdin);
	freopen("great.out", "w", stdout);
	scanf("%I64d %d", &n, &k);
	long long bn = n;
	int len = 0;
	while(bn)
	{
		a[++len] = bn % k;
		bn /= k;
	}
	int flag = 0;
	//printf("%d\n", len);
	for(int i = len; i >= 1; i--)
	{
		if (i % 2 == 0)
		{
			if (a[i])
			{
				for(int j = i - 1; j >= 1; j--)
					a[j] = k - 1;
			}
			continue;
		}
		if (!flag && a[i] == 0)
			continue;
		long long tmp = a[i];
		for(int j = i - 1; j >= 1; j--)
		{
			if (j % 2 == 1)
				tmp = tmp * k;
		}
		res += tmp;
		//printf("%I64d\n", tmp);
		if (a[i])
			flag = 1;
	}
	printf("%I64d\n", res + 1);
	return 0;
}
