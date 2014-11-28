#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<string>
#include<algorithm>
using namespace std;

#define sqr(x) ((x)*(x))

const int MAXN = 100010;

int n,m;
double L;
double sum,a[MAXN],ans;
int b[MAXN];
int heap[MAXN];

double delta(int i)
{
	return sqr(a[i]/(b[i]+2)-L)*(b[i]+2) - sqr(a[i]/(b[i]+1)-L)*(b[i]+1);
}

void down(int i)
{
	int j = i;
	if (i*2<=n && delta(heap[i*2]) < delta(heap[j])) j=i*2;
	if (i*2+1<=n && delta(heap[i*2+1]) < delta(heap[j])) j=i*2+1;
	if (j>i)
	{
		swap(heap[i],heap[j]);
		down(j);
	}
}

void work(string s)
{
	freopen((s+".in").c_str(), "r", stdin);
	freopen((s+".out").c_str(), "w", stdout);
	scanf("%d%d%lf",&n,&m,&L);
	for (int i=1;i<=n;i++) scanf("%lf",a+i);
	for (int i=1;i<n;i++) a[i] = a[i+1] - a[i];
	n--;
	sum = 0;
	for (int i=1;i<=n;i++) sum += fabs(a[i]);
	for (int i=1;i<=n;i++)
	{
		b[i] = (int) (m/sum*fabs(a[i])) - 1;
		if (b[i]>fabs(a[i]/L)-1) b[i] = int(fabs(a[i]/L))-1;
		if (b[i]<0) b[i] = 0;
	}
	for (int i=1;i<=n;i++) m -= b[i];
//	printf("a: "); for (int i=1;i<=n;i++) printf("%7d ",(int)a[i]); printf("\n");
//	printf("b: "); for (int i=1;i<=n;i++) printf("%7d ",b[i]); printf("\n");
	
	for (int i=1;i<=n;i++) heap[i] = i;
	for (int i=n;i>=1;i--) down(i);
	
	while (m--)
	{
		if (delta(heap[1])<0) b[heap[1]]++;
		else break;
		down(1);
	}
	
//	printf("b: "); for (int i=1;i<=n;i++) printf("%7d ",b[i]); printf("\n");
	
	double ans = 0;
	for (int i=1;i<=n;i++)
		ans += sqr(a[i]/(b[i]+1)-L)*(b[i]+1);
	printf("%.3lf\n",ans);
}

void MakeData(string s, int n, int m, double L, int max)
{
	freopen((s+".in").c_str(), "w", stdout);
	printf("%d %d %.3lf\n",n,m,L);
	for (int i=0;i<n;i++) printf("%.3lf ",(rand()%200001-100000)/1000.0);
	printf("%d\n");
	work(s);
}

int main()
{
	srand(time(0));
	//        name            n          m      L  max
	MakeData( "seq1",         5,         5,     0, 100);
	MakeData( "seq2",        10,       100,     0, 100);
	MakeData( "seq3",        50,       200,    -1, 100);
	MakeData( "seq4",       100,        10,     8, 100);
	MakeData( "seq5",       300,       200,     0, 100);
	MakeData( "seq6",       500,       200,    88, 100); //

	MakeData( "seq7",      1000,      2000,     0, 100);
	MakeData( "seq8",      2000,     10000,     1, 100);
	MakeData( "seq9",      3000,    100000,   0.1, 100);
	MakeData("seq10",      5000,    100000,     0, 100);
	MakeData("seq11",      8000,      1000,     0, 100);
	MakeData("seq12",     10000,    100000,    25, 100); //
	MakeData("seq13",     15000,    100000,    10, 100); //
	MakeData("seq14",     20000,    100000,     0, 100);

	MakeData("seq15",        10, 100000000,     0, 100);
	MakeData("seq16",       100, 100000000,     0, 100);
	MakeData("seq17",      1000, 100000000,     0, 100);
	MakeData("seq18",     30000, 100000000,  -0.2, 100); //
	MakeData("seq19",     40000, 100000000,-0.003, 100);
	MakeData("seq20",     50000, 100000000, 0.004, 100);
}
