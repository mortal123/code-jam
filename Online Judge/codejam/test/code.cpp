#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 2000, inf = 20000000;
const double eps = 1e-8;

struct Rec
{
	double v;
	int num;
	friend int operator<(Rec a, Rec b) {
		if (fabs(a.v - b.v) >	 eps)
			return a.v < b.v;
		return a.num < b.num;
	}
}rec[MAXN + 10];

int p[MAXN], l[MAXN];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &l[i]);
		}
		for(int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
			p[i] = 100 - p[i];
		}
		for(int i = 1; i <= n; i++) {
			if (p[i] == 100) {
				rec[i].v = inf;
			} else {
				rec[i].v = (double)l[i] / (100 - p[i]);
			}
			rec[i].num = i - 1;
		}
		sort(rec + 1, rec + n + 1);
	///	for(int i = 1; i <= n; i++) {
	//		printf("%d %lf\n", rec[i].num, rec[i].v);
	//	}
		printf("Case #%d:", t);
		for(int i = 1; i <= n; i++) {
			printf(" %d", rec[i].num);
		}
		printf("\n");
	}
	return 0;
} 
