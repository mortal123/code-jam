#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 3100;
const double inf = 10000000000000000000.0;

int N;
double t, a[MAXN], b[MAXN];
double f[MAXN];

void Init()
{
	scanf("%d %lf", &N, &t);
	for(int i = 1;i <= N;i++)
		scanf("%lf", &a[i]);
	a[N + 1] = 0;
	for(int i = 1;i <= N + 1;i++)
		b[i] = 1.0 - a[i];
}

/*
f[i] = t + k + (f[i] + k) * a[i + 1] + (f[i + 1] + k - 1) * b[i + 1] * a[i + 2] + f[i + 2] * b[i + 1] * b[i + 2] * a[i + 3] + ...
		+ f[i + k] * b[i + 1] * b[i + 2] * .... * b[i + k];
*/

void Work()
{
	for(int i = 0;i <= N;i++)
	{
		f[i] = inf;
	}
	f[N] = 0; 
	for(int i = N - 1;i >= 0;i--)
	{
		double tmp = 1, sum = t, inc = a[i + 1];
		for(int j = 1;i + j <= N;j++)
		{
			tmp *= b[i + j];
			sum += 1;
			double t2 = sum + tmp * f[i + j] + inc;
			//if (i == 0)
			//	printf("%.6lf\n\n", t2 / b[i + 1]);
			if (t2 < f[i])
				f[i] = t2;
			sum += f[i + j] * tmp * a[i + j + 1] + inc;
			inc += tmp * a[i + j + 1];
		}
		f[i] /= b[i + 1];
	}
	//for(int i = 0;i <= N;i++)
	//	printf("%.8lf\n", f[i]);
	printf("%.6lf", f[0]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
