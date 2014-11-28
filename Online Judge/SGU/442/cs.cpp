#include <cstdio>
#include <cstdlib>
#include <cstring>
char str[20];
int a[20], N, cnt;
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w" , stdout);
	scanf("%d", &N);
	for(int i = 0;i <= N;i++)
	{
		int tmp = i, len = 0, res = 0;
		while(tmp)
		{
			a[++len] = tmp % 10;
			tmp /= 10;
		}
		for(int j = 1;j <= len;j++)
			res = res * 10 + a[j];
		res += i;
		if (res == N)
			printf("%d\n", i), cnt++;
	}
	printf("%d\n", cnt);
	//system("pause");
	return 0;
}
