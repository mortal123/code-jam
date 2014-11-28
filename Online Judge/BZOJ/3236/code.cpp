#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 100005, MAXM = 1000005;

int slang;

struct node
{
	int l, r, a, b, ans1, ans2, id;
	friend int operator <(node a, node b) {
		if (a.l / slang != b.l / slang)
			return a.l / slang < b.l / slang;
		return a.r < b.r;
	}
}q[MAXM];

int cmpid(node a, node b) {
	return a.id < b.id;
}
int top = 0;
int n, m, a[MAXN], hash[MAXM], h[MAXN], hh[MAXN];

inline int lowbit(int x) {
	return (-x) & x;
}

int ask(int h[], int pos) {
	int res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

int ins(int h[], int pos, int val) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		h[i] += val;
	}
}

int add(int x) {
	ins(h, x, 1);
	if (++hash[x] == 1)	
		ins(hh, x, 1);
}

int dec(int x) {
	ins(h, x, -1);
	if (--hash[x] == 0)
		ins(hh, x, -1);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	int top = 0;
	for(int i = 1; i <= n; i++)	{
		scanf("%d", &a[i]);
	}
	slang = max(10, (int)sqrt(n));
	for(int i = 1; i <= m; i++) {
		scanf("%d %d %d %d", &q[i].l, &q[i].r, &q[i].a, &q[i].b);
		q[i].id = i;
		q[i].ans1 = 0; q[i].ans2 = 0;
	}
	sort(q + 1, q + m + 1);
	int L = 1, R = 0;
	for(int i = 1; i <= m; i++) {
		while(R < q[i].r) ++R, add(a[R]);
		while(R > q[i].r) dec(a[R]), R--;
		while(L < q[i].l) dec(a[L]), L++;
		while(L > q[i].l) --L, add(a[L]);
		int a = q[i].a, b = q[i].b; a--;
		if (a < 0) a = 0;
		if (b > n) b = n;
		q[i].ans1 = ask(h, b) - ask(h, a);
		q[i].ans2 = ask(hh, b) - ask(hh, a);
	}
	sort(q + 1, q + m + 1, cmpid);
	for(int i = 1; i <= m; i++)
		printf("%d %d\n", q[i].ans1, q[i].ans2);
	return 0;
}
