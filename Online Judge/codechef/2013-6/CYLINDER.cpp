#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

double W, H;
double pi = acos(-1);
const double eps = 1e-12;

double Calc(double W, double H)
{
	double res = 0, R, L, c1, c2, c3;
	//(1)
	//R = min(a / 2, h / 4, b / 2 / pi);
	R = min(H / 4, W / (pi + 1) / 2);
	res = max(res, R * R * pi * H);
	
	//(2)
	//R = min(a / 2, h / 2 / pi)
		//#1 0 <= a / 2 <= h / 2 / pi ==>  0 <= a <= h / pi
		// V = -a^3(pi / 4) + a^2 * (W * pi / 4)
		// V' = -a^2(3 * pi / 4) + a * (W * pi / 2)
		c1 = -(3.0 * pi / 4.0), c2 = W * pi / 2.0;
		R = min(H / pi, -c2 / c1); R = max(R, 0.0);
		res = max(res, (R / 2) * (R / 2) * pi * (W - R));
		R = H / pi;
		res = max(res, (R / 2) * (R / 2) * pi * (W - R));
		
		//#2 h / 2 / pi <= a / 2 ==> h / pi <= a
		// V = (h / 2 / pi)^2 * pi * (W - a)
		// a --> min ====> a = h / pi   same up;
	
	//(3)
	//R = min(H / 2, a / 4, b / 2 / pi);
	R = min(H / 2, 2 * W / (2 + pi) / 4);
	res = max(res, R * R * pi * H);
	
	//(4)
	//R = min(a / 4, h / 2 / pi)
		//#1 a / 4 <= h / 2 / pi ==> a < 2 * h / pi
		// V = -a^3(pi / 16) + a^2 * (W * pi / 16)
		// V' = -a^2(3 * pi / 16) + a * (W * pi / 8)
		c1 = -(3 * pi / 16.0), c2 = (W * pi / 8.0);
		R = min(2 * H / pi, -c2 / c1); R = max(0., R);
		res = max(res, (R / 4) * (R / 4) * pi * (W - R));
		R = 2 * H / pi;
		res = max(res, (R / 4) * (R / 4) * pi * (W - R));
		
		//#2 h / 2 / pi <= a / 4
		// V = (h / 2 / pi)^2 * pi * (W - a)
		// a = 2 * h / pi;
		// same up;
	
	//(5)
	//(a - D)^2 + (h - D)^2 = D^2;
	double D;
	c1 = (pi + 1) * (pi + 1), c2 = -2 * (W * (pi + 1) + H), c3 = W * W + H * H;
	if (c2 * c2 - 4 * c1 * c3 > -eps)
	{
		R = max((-c2 - sqrt(c2 * c2 - 4 * c1 * c3)) / 2.0 / c1, 0.0); 
		D = R, R /= 2;
		if (D < W - D * pi + eps && D < W + eps && D < H + eps)
			res = max(res, R * R * pi * H);// printf("%.5f %.5f\n", R, H);
		R = max((-c2 + sqrt(c2 * c2 - 4 * c1 * c3)) / 2.0 / c1, 0.0); 
		D = R, R /= 2;
		if (D < W - D * pi + eps && D < W + eps && D < H + eps)
			res = max(res, R * R * pi * H);//, printf("%.5f %.5f\n", R, H);
	}
	 
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lf %lf", &W, &H);
		double ans = max(Calc(W, H), Calc(H, W));
		printf("%.12f\n", ans);
	}
	return 0;
} 
