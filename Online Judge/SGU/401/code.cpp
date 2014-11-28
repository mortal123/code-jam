#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 52;
const double eps = 1e-12;

int N;
double u, t, w[MAXN], v[MAXN], tc[MAXN];

void Init()
{
	scanf("%d %lf %lf", &N, &u, &t);
	for(int i = 1;i <= N;i++)
		scanf("%lf %lf", &w[i], &v[i]);
}

double Calc(double st)
{
	double res = 0;
	for(int i = 1;i <= N;i++)
	{
		if (st <= v[i])
			return t + 10;
		double a = u * u, b = w[i] * w[i], c = v[i];
		double tmp = a / (st - c);
		tmp = a - tmp * tmp;
		
		tmp = w[i] / sqrt(tmp);
		tc[i] = tmp;
		res += tc[i];
	}
	return res;
}
/*
double Calc(double mid)
{
   double s=0;
   for (int i=1;i<=N;i++)
      if (mid<=v[i])
         return 100000000000.0;
      else
         s+=w[i]/sqrt(u*u-(u*u/(mid-v[i]))*(u*u/(mid-v[i])));
   return s;
}*/
void Work()
{
	double cs = 0;
	for(int i = 1;i <= N;i++)
		cs += w[i] / u;
	if (cs > t + 1e-10)
	{
		printf("-1\n");
		return;
	}
	
	double l = 0, r = 100000000000000.0, mid;
	for(int i = 1;i <= 100000;i++)
	{
		mid = (l + r) / 2;
		double cost = Calc(mid);
		if (cost <= t)
			r = mid;
		else
			l = mid;
	}
	Calc(r);
	double sr = 0, sw = 0;
	for(int i = 1;i <= N;i++)
	{
		tc[i]=w[i]/sqrt(u*u-(u*u/(r-v[i]))*(u*u/(r-v[i])));
		sr += tc[i] *(sqrt(u * u - w[i] * w[i] / tc[i] / tc[i]) + v[i]);
		sw += w[i];
	}
	printf("%.10lf\n", sqrt(sr * sr + sw * sw));
	for(int i = 1;i <= N;i++)
		printf("%.10lf ", tc[i]);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
