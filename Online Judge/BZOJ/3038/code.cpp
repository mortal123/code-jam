#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 100000;

long long h[MAXN + 10];
int n, m;
long long a[MAXN + 10];
int fa[MAXN + 10];

inline int lowbit(int x)
{
	return x & (-x);
}

inline long long ask(int pos)
{
	long long res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

inline void ins(int pos, long long val)
{
	for(int i = pos; i <= n; i += lowbit(i)) {
		h[i] += val;
	}
}

int find(int x)
{
	int p = x, t;
	while(p != fa[p]) {
		p = fa[p];
	}
	while(x != p) {
		t = fa[x];
		fa[x] = p;
		x = t;
	}
	return x;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	fa[0] = 0;
	memset(h, 0, sizeof(h));
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		ins(i, a[i]);
		fa[i] = i;
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int opt, l, r;
		scanf("%d %d %d", &opt, &l, &r);
		if (l > r)
			swap(l, r);
		if (l <= 0)
			l = 1;
		if (opt == 0) {
			while(1) {
				r = find(r);
				if (r < l)
					break;
				long long tmp = sqrt(a[r]);
				ins(r, tmp - a[r]);
				a[r] = tmp;
				if (a[r] == 1)
					fa[r] = r - 1;
				r--;
			}
		} else {
			printf("%lld\n", ask(r) - ask(l - 1));
		}
	}
	return 0;
}
