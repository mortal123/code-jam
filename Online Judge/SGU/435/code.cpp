/*
	ans[i] 存储了覆盖i次以上的面积
	n^2logn 带有手写 complex 
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
using namespace std;

const int MAXN = 1012;
const double eps = 1e-9;
const double pi = acos(-1.0);

typedef complex<double> Complex;
/* 
struct Complex
{
	double real, imag;
	Complex(){}
	Complex(double _real, double _imag) : real(_real), imag(_imag) {}
};

inline Complex operator *(const Complex &a, const Complex &b)
{
	return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}

inline Complex operator /(const Complex &a, double t)
{
	return Complex(a.real / t, a.imag / t);
}

inline Complex operator *(const Complex &a, double t)
{
	return Complex(a.real * t, a.imag * t);
}

inline double abs(Complex a)
{
	return sqrt(a.real * a.real + a.imag * a.imag);
}
*/
struct cir
{
	double x, y, r, angle;
	int d;
	cir(){}
	cir(double _x, double _y) : x(_x), y(_y) {}
}p[MAXN], rec[MAXN * 8];

int n, top;

double ans[MAXN];

inline double modify(double p)
{
	if (p > 2 * pi)
		return p - 2 * pi;
	if (p < 0)
		return p + 2 * pi;
	return p;
}

inline double Cross(cir a, cir &b, cir &c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

inline double dis(cir &a, cir &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool cmp(const cir &a, const cir &b)
{
	if (fabs(a.angle - b.angle) < eps)
		return a.d > b.d;
	return a.angle < b.angle;
}

inline int CirCrossCir(cir &c1, cir &c2, cir &cp1, cir &cp2)
{
	double a = c1.r, b = c2.r, c = dis(c1, c2);
	if (a + b < c + eps || c + b < a + eps || a + c < b + eps)
		return 0;
	double cosd = (a * a + c * c - b * b) / (2 * a * c);
	double sind = sqrt(max(0.0, 1 - cosd * cosd)); // 由于角度不会大于180 所以sin为正 
	Complex mid, cpp;
	mid = Complex(c2.x - c1.x, c2.y - c1.y);
	mid = mid / abs(mid) * c1.r;
	cpp = mid * Complex(cosd, sind);
	cp2 = cir(cpp.real() + c1.x, cpp.imag() + c1.y);
	cpp = mid * Complex(cosd, -sind);
	cp1 = cir(cpp.real() + c1.x, cpp.imag() + c1.y);
	return 1;
}
void solve(int w)
{
	cir lp = cir(p[w].x + p[w].r, p[w].y);
	top = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	if (i != w)
	{
		cir cp1, cp2;
		if (!CirCrossCir(p[w], p[i], cp1, cp2))
			continue;
		cp1.d = 1;  cp1.angle = modify(atan2(cp1.y - p[w].y, cp1.x - p[w].x)); rec[++top] = cp1; 
		cp2.d = -1; cp2.angle = modify(atan2(cp2.y - p[w].y, cp2.x - p[w].x)); rec[++top] = cp2;
		if (cp1.angle > cp2.angle + eps)
			cnt++;
	}
	rec[0] = lp; rec[0].angle = 0; rec[0].d = cnt;
	rec[++top] = lp; rec[top].angle = 2 * pi; rec[top].d = -cnt;
	sort(rec + 1, rec + top + 1, cmp);
	cnt = rec[0].d + p[w].d;
	for(int i = 1; i <= top; ++i)
	{
		//if (cnt == 1) { // 如果只要求某一个覆盖次数，可以加限制，使程序效率提高 
			ans[cnt] += (
						 p[w].r * p[w].r * (rec[i].angle - rec[i - 1].angle) 
					 -   Cross(p[w], rec[i - 1], rec[i])
					 +   Cross(cir(0, 0), rec[i - 1], rec[i])
					 	) / 2;
		//}
		cnt += rec[i].d;
	}	
}

int cmpr(cir a, cir b)
{
	return a.r > b.r;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].r), ans[i] = 0;
		//if (p[i].r < eps)
		//	i--, n--;
	}
	ans[n + 1] = 0;
	sort(p + 1, p + n + 1, cmpr);
	for(int i = 1; i <= n; ++i)
	{
		p[i].d = 1;
		for(int j = 1; j < i; ++j)
			{
				if (dis(p[i], p[j]) + p[i].r < p[j].r + eps)
					p[i].d++;
			}
		//if (p[i].d == 1) // 可以加限制提高速度 
			solve(i);
	}
	double ans1, ans2;
	for(int i = 1;i <= n;i++)
	{
		if (i & 1)
			ans1 += ans[i] - ans[i + 1];
		else
			ans2 += ans[i] - ans[i + 1];
	}
	printf("%.4lf %.4lf\n", ans1, ans2);
	//printf("%.5f\n", ans[1]);
	return 0;
}
