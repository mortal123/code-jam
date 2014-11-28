#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 1100000;

int n;
long long f[MAXN + 10], cost[MAXN + 10];
int sec[MAXN + 10], bot, top, pos[MAXN + 10];

inline long long Calc(int a, int b) 
{
	long long bb = b, aa = a;
	return cost[b] + (bb - aa) * (bb - aa - 1) / 2 + f[a];
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &cost[i]);
	}
	f[0] = 0;
	bot = 1, top = 0;
	//sec[top] = n + 1;
	pos[++top] = 0;
	sec[top] = n;
	for(int i = 1; i <= n; i++) {
		while(sec[bot] < i)
			bot++;
		f[i] = Calc(pos[bot], i);
		while(bot <= top) {
			if (Calc(i, n) < Calc(pos[top], n)) {
				int tt = i + 1;
				if (bot < top)
					tt = sec[top - 1] + 1;
				if (Calc(i, tt) <= Calc(pos[top], tt)) {
					top--;
					continue;
				} else {
					int l = tt, r = n, mid;
					while(l < r) {
						mid = (l + r) / 2 + 1;
						if (Calc(i, mid) > Calc(pos[top], mid))
							l = mid;
						else
							r = mid - 1;
					}
					sec[top] = l;
					sec[++top] = n; pos[top] = i;
					break;
				}
			} else {
				break;
			}
		}
		if (bot > top) {
			sec[++top] = n, pos[top] = i;
		}
	}
	printf("%lld\n", f[n]);
	return 0;
} 
