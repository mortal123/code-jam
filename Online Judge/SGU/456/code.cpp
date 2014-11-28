#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

int p, m, s;
const double eps = 1e-8;

int calc(double x, double s, double m, double p)
{
	for(int i = 1; i <= m; i++)
	{
		double a = s * p / 100;
		double re = x - a;
		s -= re;
		if (s < -eps)
			return -1;
	}
	return 1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> s >> m >> p;
	double l = 0, r = s * (100 + p) / 100.0, mid;
	while(l + 1e-8 < r)
	{
		mid = (l + r) / 2;
		double remains = calc(mid, s, m, p);
		if (remains < 0)
			r = mid;
		else
			l = mid;
	}
	printf("%.8f\n", (l + r) / 2);
	return 0;
}
