#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1100, ep = 100000000;
/*
struct node
{
	int dat[100];
	node()
	{
		memset(dat, 0, sizeof(dat));
		dat[0] = 1;
	}
	void clear()
	{
		for(int i = 1;i <= dat[0];i++)
			dat[i] = 0;
		dat[0] = 1;
	}
	void operator +=(node b)
	{
		dat[0] = max(dat[0], b.dat[0]);
		for(int i = 1;i <= dat[0];i++)
		{
			dat[i] += b.dat[i];
			if (dat[i] >= ep)
			{
				if (i == dat[0])
					dat[0]++;
				dat[i + 1]++, dat[i] -= ep;
			}
		}
	}
	void print()
	{
		printf("%d", dat[dat[0]]);
		for(int i = dat[0] - 1;i >= 1;i--)
			printf("%08d", dat[i]);
		printf("\n");
	}
}*/
long long Ans, f[MAXN][2][2];

char str[MAXN];
int a[MAXN], N;

void Init()
{
	N = strlen(str + 1);
	for(int i = 1;i <= N;i++)
		a[i] = str[i] - '0';
	for(int i = 1;i <= N / 2;i++)
		swap(a[i], a[N - i + 1]);
}

void DP()
{	
	for(int i = 0;i <= N / 2;i++)
		for(int j = 0;j <= 1;j++)
			for(int k = 0;k <= 1;k++)
				if (f[i][j][k])
				{
					for(int p = 0;p <= 9;p++) // i + 1
						for(int q = 0;q <= 9;q++) // N - i
						{
							if (i == 0 && q == 0)
								continue;
							if ((p + q + j) % 10 != a[i + 1])
								continue;
							int jj = ((p + q + j) >= 10), kk;
							int tmp = (p + q - k * 10);							
							if (tmp == a[N - i])
								kk = 0;
							else
							if (tmp == a[N - i] - 1)
								kk = 1;
							else
								continue;
							f[i + 1][jj][kk] += f[i][j][k];
						}
				}
}

void Work()
{
	Ans = 0;
//	if (a[N] != 1)
//	{
		for(int i = 0;i <= N;i++)
			for(int j = 0;j <= 1;j++)
				for(int k = 0;k <= 1;k++)
					f[i][j][k] = 0;
		f[0][0][0] = 1;
		DP();
		if (N % 2 == 0)
			Ans += f[N / 2][1][1], Ans += f[N / 2][0][0];
		else
		{
			int i = N / 2;
			for(int j = 0;j <= 1;j++)
				for(int k = 0;k <= 1;k++)
				{
					for(int p = 0;p <= 9;p++)
					{
						int tmp = p + p - k * 10 + j;
						if (tmp == a[N / 2 + 1])
							Ans += f[i][j][k];
					}
				}
		}
//	}
//	else
//	{
		N--;
		for(int i = 0;i <= N;i++)
			for(int j = 0;j <= 1;j++)
				for(int k = 0;k <= 1;k++)
					f[i][j][k] = 0;
		f[0][0][1] =  1;
		DP();
		if (N % 2 == 0)
			Ans += f[N / 2][1][1], Ans += f[N / 2][0][0];
		else
		{
			int i = N / 2;
			for(int j = 0;j <= 1;j++)
				for(int k = 0;k <= 1;k++)
				{
					for(int p = 0;p <= 9;p++)
					{
						int tmp = p + p - k * 10 + j;
						if (tmp == a[N / 2 + 1])
							Ans += f[i][j][k];
					}
				}
		}
//	}
	printf("%I64d\n", Ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(1)
	{
		gets(str + 1);
		if (str[1] == '0')
			break;
		Init();
		Work();
	}
	return 0;
}
