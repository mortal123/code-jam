#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 100000;

int n, m;
long long a[MAXN + 10], h[MAXN + 10], g[MAXN + 10];
char str[MAXN];

int lowbit(int x) {
	return x & (-x);
}

long long ask(long long r[], int pos) {
	long long res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += r[i];
	}
	return res;
}

void ins(long long r[], int pos, long long x) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		r[i] += x;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		ins(h, i, a[i]);
		ins(g, i, a[i] * i);
	}
	//scanf("\n");
	for(int i = 1; i <= m; i++) {
		long long x, y;
		scanf("%s", str);
		if (str[0] == 'M') {
			scanf("%lld %lld\n", &x, &y); //printf("M %lld %lld\n", x, y);
			ins(h, x, y - a[x]);
			ins(g, x, (y - a[x]) * x);
			a[x] = y;
		} else {
			scanf("%lld\n", &x); //printf("Q %lld\n", x);
			printf("%lld\n", ask(h, x) * (x + 1) - ask(g, x));
		}
	}
	return 0;
} 
