#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
long long M, L, R, K;
struct mat
{
	long long dat[2][2];
	friend mat operator *(mat a, mat b)
	{
		mat c;
		for(int i = 0;i <= 1;i++)
			for(int j = 0;j <= 1;j++)
			{
				c.dat[i][j] = 0;
				for(int k = 0;k <= 1;k++)
					c.dat[i][j] = (c.dat[i][j] + a.dat[i][k] * b.dat[k][j]) % M;
			}
		return c;
	}
}a, b;

long long Calc(long long N)
{
	N--;
	a.dat[0][0] = 1; a.dat[1][0] = 0;
	b.dat[0][0] = 1, b.dat[0][1] = 1;
	b.dat[1][0] = 1, b.dat[1][1] = 0;
	while(N)
	{
		if (N % 2 == 1)
			a = b * a;
		N /= 2;
		b = b * b;
	}
	return a.dat[0][0];
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%I64d %I64d %I64d %I64d", &M, &L, &R, &K);
	L--;
	long long a = 1, ans = 1;
	for(;a <= R;a++)
	{
		long long tmp = R / (R / a);
		if (a <= L && L / (L / a) < tmp)
			tmp = L / (L / a);
		a = tmp;
		if (a == R)
		a = R;		
		if (R / a - L / a >= K)
			ans = a;
	}
	printf("%I64d", Calc(ans) % M);
	return 0;
}
