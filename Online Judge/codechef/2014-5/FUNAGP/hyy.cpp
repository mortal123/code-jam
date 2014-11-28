#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int test, n, q, r, ny, p1, p2, type, i;
int x, y, g, ans, a[100005], pos[100005];
ll mo, s, d, R[100005];

ll Mul(ll x, ll y, ll n)
{
	ll d = (ll)((long double)x * y / n);
	d = x * y - n * d;
	while (d < 0)
		d += n;
	while (d >= n)
		d -= n;
	return d;
}

ll Pow(ll a, int b, ll n)
{
	ll ret = 1 % n, c = a % n;
	while (b)
	{
		if (b & 1)
			ret = Mul(ret, c, n);
		c = Mul(c, c, n);
		b >>= 1;
	}
	
	return ret;
}

int Sum(ll S, ll D, int n) //S to (S + (n - 1) * D) * R ^ (n - 1)
{
	int s = S % p1, d = D % p1, ans = 0, rn = R[n] % p1;
	if (r % p1 == 1)
	{
		if (!(n & 1))
			return ((long long)(n - 1) * d + s + s) % p1 * (n / 2) % p1;
		return ((long long)(n - 1) * d + s + s) / 2 % p1 * n % p1;
	}
	
	ans = (long long)(n - 1) * d % p1;
	ans = (long long)(s + ans) * rn % p1;
	ans -= ((long long)s + (long long)(rn - r % p1) * ny % p1 * d % p1) % p1;
	while (ans < 0)
		ans += p1;
	while (ans >= p1)
		ans -= p1;
	ans = (long long)ans * ny % p1;
	return ans;
}

struct Node
{
	int left, right, sum;
	long long val, s, d;
	
	void init(int l, int r, int v)
	{
		left = l, right = r;
		val = v;
		sum = v % p1;
		s = d = 0;
	}
	
	void Add(ll S, ll D)
	{
		if (left == right)
		{
			val += S;
			if (val >= mo)
				val -= mo;
			sum += (S % p1);
			if (sum >= p1)
				sum -= p1;
		}
		
		else
		{
			sum += Sum(S, D, right - left + 1);
			if (sum >= p1)
				sum -= p1;
			s += S;
			if (s >= mo)
				s -= mo;
			d += D;
			if (d >= mo)
				d -= mo;
		}
	}
	
	void Down(Node &a, Node &b)
	{
		if (s == 0 && d == 0)
			return;
		int mid = b.left - left;
		a.Add(s, d);
		b.Add(Mul(s + Mul(d, mid, mo), R[mid], mo), Mul(d, R[mid], mo));
		s = d = 0;
	}
}seg[500005];

void Make(int l, int r, int i);
void Add(int l, int r, int i);
void Ask(int l, int r, int i);
void Modify(int x, int g);

int main()
{
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d %d %d %d %d", &n, &q, &r, &p1, &p2);
		mo = p1, mo *= p2;
		R[0] = 1;
		for (i = 1; i <= n; i++)
		{
			R[i] = Mul(R[i - 1], r, mo);
			scanf("%d", &a[i]), a[i] %= mo;
		}
		
		ny = Pow(r - 1, p1 - 2, p1);
		Make(1, n, 1);
		for (i = 1; i <= q; i++)
		{
			scanf("%d", &type);
			if (type == 0)
			{
				int ss, dd;
				scanf("%d %d %d %d", &ss, &dd, &x, &y), s = ss, d = dd;
				Add(x, y, 1);
			}
			
			else if (type == 1)
				scanf("%d %d", &x, &g), Modify(x, g);
			else
				scanf("%d %d", &x, &y), ans = 0, Ask(x, y, 1), printf("%d\n", ans);
		}
	}
	
	return 0;
}

void Make(int l, int r, int i)
{
	int mid = (l + r) >> 1;
	if (l == r)
	{
		pos[l] = i;
		seg[i].init(l, r, a[l]);
		return;
	}
	
	seg[i].init(l, r, 0);
	Make(l, mid, (i << 1)), Make(mid + 1, r, (i << 1) | 1);
	seg[i].sum = (seg[i << 1].sum + seg[(i << 1) | 1].sum) % p1;
}

void Add(int l, int r, int i)
{
	int lc = (i << 1), rc = (lc | 1);
	if (l > seg[i].right || r < seg[i].left)
		return;
	if (l <= seg[i].left && r >= seg[i].right)
	{
		int mid = seg[i].left - l;
		seg[i].Add(Mul(s + Mul(d, mid, mo), R[mid], mo), Mul(d, R[mid], mo));
		return;
	}
	
	seg[i].Down(seg[lc], seg[rc]);
	Add(l, r, lc), Add(l, r, rc);
	seg[i].sum = (seg[i << 1].sum + seg[(i << 1) | 1].sum) % p1;
}

void Ask(int l, int r, int i)
{
	int lc = (i << 1), rc = (lc | 1);
	if (l > seg[i].right || r < seg[i].left)
		return;
	if (l <= seg[i].left && r >= seg[i].right)
	{
		ans += seg[i].sum;
		if (ans >= p1)
			ans -= p1;
		return;
	}
	
	seg[i].Down(seg[lc], seg[rc]);
	Ask(l, r, lc), Ask(l, r, rc);
}

void Modify(int x, int g)
{
	int list[20], tot = 0, now, i, delta;
	now = pos[x];
	while (now)
		list[++tot] = now, now >>= 1;
	for (i = tot; i >= 1; i--)
		seg[list[i]].Down(seg[list[i] << 1], seg[(list[i] << 1) | 1]);
	now = pos[x], delta = seg[now].sum;
	seg[now].val = Pow(seg[now].val, g, p2);
	delta = seg[now].val % p1 - delta;
	if (delta < 0)
		delta += p1;
	while (now)
	{
		seg[now].sum += delta;
		if (seg[now].sum >= p1)
			seg[now].sum -= p1;
		now >>= 1;
	}
}
