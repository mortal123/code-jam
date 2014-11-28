#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 1100000, MV = 1100000;

int tree[MAXN * 4], f[MAXN], n, ans = -1, ansp, fr[MAXN], next[MAXN], p[MAXN];

void insert(int v, int pos)
{
	int root = 1, l = 0, r = MV;
	while(l < r)
	{
		int mid = (l + r) / 2;
		root *= 2;
		if (pos <= mid)
			r = mid;
		else
			l = mid + 1, root++;
	}
	while(root)
	{
		if (f[v] > f[tree[root]])
			tree[root] = v;
		root >>= 1;
	}
}

int ask(int root, int l, int r, int al, int ar)
{
	
	if (al == 4 && ar == MV && l == 0 && r == 4)
		al = 4;
	if (ar < al)
		return 0;
	if (al <= l && ar >= r)
		return tree[root];
	int mid = (l + r) / 2;
	int ch = 0;
	if (al <= mid)
		ch = ask(root * 2, l, mid, al, ar);
	if (ar > mid)
	{
		int c = ask(root * 2 + 1, mid + 1, r, al, ar);
		if (f[c] > f[ch])
			ch = c;
	}
	return ch;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x); 
		p[i] = x;
		int pos = ask(1, 0, MV, 0, x - 2);
		int posb = ask(1, 0, MV, x + 2, MV);
		if (f[posb] > f[pos])
			pos = posb;
		posb = ask(1, 0, MV, x, x);
		if (f[posb] > f[pos])
			pos = posb;
		fr[i] = pos;
		f[i] = f[pos] + 1;
		if (f[i] > ans)
			ans = f[i], ansp = i;
		insert(i, x);
	}
	while(ansp)
		next[fr[ansp]] = ansp, ansp = fr[ansp];
	printf("%d\n", n - ans);
	for(int i = 1; i <= ans; i++)
	{
		ansp = next[ansp];
		printf("%d%c", p[ansp], i == ans ? '\n' : ' ');
	}
	return 0;
} 
