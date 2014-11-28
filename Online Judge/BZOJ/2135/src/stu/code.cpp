#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100000;

int N, M;
int get[MAXN];
double L, a[MAXN], sum;
struct block
{
	int num, cnt;
	double delta;
}p[MAXN];
int top = 0;

inline double sqr(double x)
{
	return x * x;
}

void Init()
{
	scanf("%d %d %lf", &N, &M, &L);
	L += 1e-12;
	for(int i = 1;i <= N;i++)
		scanf("%lf", &a[i]);
	for(int i = 1;i < N;i++)
		a[i] = a[i + 1] - a[i], sum += fabs(a[i]);
	N--;
	for(int i = 1;i <= N;i++)
	{
		get[i] = (int)(fabs(a[i] / sum) * M) - 1;
		if ((double)get[i] > (fabs(a[i] / L) - 1))
			get[i] = (int)(fabs(a[i] / L) - 1);
		if (get[i] < 0)
			get[i] = 0;
	}
	for(int i = 1;i <= N;i++)
		M -= get[i];
}

inline double calc(int x, int y)
{
	return sqr(a[x] / (y + 1) - L) * (y + 1);
}

void Insert(int num, int cnt)
{
	p[++top] = (block){num, cnt, calc(num, cnt + 1) - calc(num, cnt)};
	int i = top;
	while(i / 2)
	{
		int j = i / 2;
		if (p[i].delta < p[j].delta)
		{
			swap(p[i], p[j]);
			i = j;
		}
		else
			break;
	}
}

void delet()
{
	p[1] = p[top];
	top--;
	int i = 1;
	while(i * 2 <= top)
	{
		int j = i * 2;
		if (j + 1 <= top && p[j + 1].delta < p[j].delta)
			j++;
		if (p[j].delta < p[i].delta)
		{
			swap(p[i], p[j]);
			i = j;
		}
		else
			break;
	}
}

void Work()
{
	for(int i = 1;i <= N;i++)
		Insert(i, get[i]);
	for(int i = 1;i <= M && p[1].delta < 0;i++)
	{
		block tmp = p[1];
		delet();
		Insert(tmp.num, tmp.cnt + 1);
	}
	double Ans = 0;
	for(int i = 1;i <= top;i++)
	{
		Ans += calc(p[i].num, p[i].cnt);
	}
	printf("%.3lf\n", Ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Init();
	Work();
	return 0;
}
