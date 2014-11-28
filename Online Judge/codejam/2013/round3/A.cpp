#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 40;
const long long inf = 1000000000000ll;

int N = 37, n;
long long C;
long long bet[MAXN], b[MAXN];
double ans = 0;

struct node
{
	long long o, i;
	int num;
	friend int operator<(node a, node b) {
		return a.i < b.i;
	}
}W[MAXN]; int top;

long long Need(long long r) 
{
	long long res = 0;
	for(int i = 1; i <= N; i++)
		if (bet[i] < r)
			res += r - bet[i];
	return res;
}

double calc(long long bet[], long long b[], int N) {
	long long low = inf;
	/*
	printf("bet: ");
	for(int i = 1; i <= N; i++)
		printf("%I64d ", bet[i]);
	printf("\nb: ");
	for(int i = 1; i <= N; i++)
		printf("%I64d ", b[i]);
	printf("\n");
	*/
	for(int i = 1; i <= N; i++)
		low = min(low, b[i]);
	double res = 0, cnt = 0;
	for(int i = 1; i <= N; i++)
		if (b[i] == low)
			cnt = cnt+1;
	for(int i = 1; i <= N; i++)
		if (b[i] == low && b[i] > bet[i]) {
			res += 36 * (b[i] - bet[i]) / cnt;
		}
	return res;
}

void check(long long p)
{
	if (p <= 0)
		return;
	if (Need(p) > C)
		return;
	long long Tmp = C;
	for(int i = 1; i <= N; i++)
		b[i] = bet[i];
	top = 0;
	for(int i = 1; i <= N; i++) {
		if (b[i] <= p) {
			Tmp -= p - b[i];
			W[++top].o = b[i];
			W[top].i = p - b[i];
			W[top].num = i;
			b[i] = p;
		}
	}
	sort(W + 1, W + top + 1);
	ans = max(calc(bet, b, N) - (C - Tmp), ans);
	//printf("ans = %.14lf\n", ans);
	for(int i = 1; i <= top && i <= Tmp; i++) {
		b[W[i].num]++;
		ans = max(calc(bet, b, N) - (C - Tmp) - i, ans);
	//	printf("ans = %.14lf\n", ans);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		scanf("%I64d %d", &C, &n);
		for(int i = 1; i <= N; i++)
			bet[i] = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%I64d ", &bet[i]);
		}
		ans = 0;
		
		for(int i = 1; i <= n; i++) {
			check(bet[i] + 1);
			check(bet[i] - 1);
			check(bet[i]);
		}
		check(1);
		long long l = 0, mid, r = inf;
		while(l < r) {
			mid = (l + r) / 2 + 1;
			if (Need(mid) <= C)
				l = mid;
			else
				r = mid - 1;
		}
		check(l);
		check(l + 1);
		check(l - 1);
		printf("Case #%d: %.10lf\n", t, ans);
	}
	return 0;
}
