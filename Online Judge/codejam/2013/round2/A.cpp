#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1000;
const long long mod = 1000002013;

struct node
{
	int s;
	long long p;
}buc[MAXN + 10];
struct event
{
	int e, t;
}e[MAXN * 2 + 10];
int s, t, top = 0;
int n, m;

int cmp(event a, event b)
{
	if (a.t != b.t)
		return a.t < b.t;
	return a.e > b.e;
}

long long calc(int a, int b, int c)
{
	//printf("%d %d %d\n", a, b, c);
	long long l = n - (b - a), r = n - (c - a) + 1, mid = c - b;
	l += r;
	if (l % 2 == 0)
		l /= 2;
	else
		mid /= 2;
	l %= mod; mid %= mod;
	return l * mid % mod;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	int test = 0;
	while(T--)
	{
		++test;
		scanf("%d %d", &n, &m);
		long long tot = 0; top = 0;
		for(int i = 1; i <= m; i++)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			e[++top].e = c, e[top].t = a;
			e[++top].e = -c, e[top].t = b;
			tot += (long long)c * calc(a, a, b) % mod;
			//cout << calc(a, a, b) << endl;
			tot %= mod;
		}
		sort(e + 1, e + top + 1, cmp);
		long long sum = 0, ans = 0;
		t = 0;
		for(int i = 1; i <= top; i++) {
			if (e[i].e > 0) {
				sum += e[i].e;
				buc[++t].s = e[i].t;
				buc[t].p = e[i].e;
			} else {
				long long tmp = -e[i].e;
				sum -= tmp;
				while(tmp) {
					if (tmp >= buc[t].p) {
						ans += buc[t].p % mod * (calc(buc[t].s, buc[t].s, e[i].t));
						ans %= mod;
						tmp -= buc[t].p;
						t--;
					} else {
						ans += tmp % mod * (calc(buc[t].s, buc[t].s, e[i].t));
						buc[t].p -= tmp;
						break;
					}
				}
			}
		}
		//cout << tot << ' ' << ans << endl;
		tot -= ans;
		if (tot < 0) 
			tot += mod;
		cout << "Case #" << test << ": " << tot << endl;
	}
	return 0;
} 
