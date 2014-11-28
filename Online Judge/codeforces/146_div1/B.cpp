#include <cstdio>
#include <cstdlib>

const int MAXN = 200000;

double p[MAXN], f[MAXN], h[MAXN], fp[MAXN], hp[MAXN];

int N;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &N);
	for(int i = 1;i <= N;i++)
		scanf("%lf", &p[i]);
	hp[0] = 1; hp[1] = (1 - p[1]);
	double a = 0, b = 1, c = 0, d = 0;
	for(int i = 1;i <= N;i++)
	{
		a = a * p[i]; 
		b = b * p[i]; 
		c = c * p[i]; 
		d = d * p[i];
		f[i] = a + b * i * i + c - i * d;
		fp[i] = b;
		h[i + 1] = (h[i] + f[i]) * (1 - p[i + 1]);
		hp[i + 1] = (hp[i] + fp[i]) * (1 - p[i + 1]);
		a += h[i];
		b += hp[i] * 1;
		c += hp[i] * i * i;
		d += hp[i] * 2 * i;
	}
	double ans = 0;
	//for(int i = 1;i <= N;i++)
		ans += h[N] + f[N];
	printf("%.10f\n", ans);
	return 0;
}
