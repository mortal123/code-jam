#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 100000 + 10;
const int inf = 2000000000;

int n;
int l[MAXN], r[MAXN], a[MAXN], ret[MAXN], rr[MAXN];

vector <pair<int, int> > vec;
priority_queue <pair<int, int> > que;

struct node
{
	int l, r, MinL, MaxR;
}T[MAXN * 3 * 2];

void build(int root, int l, int r)
{
	T[root].l = l; T[root].r = r;
	T[root].MinL = inf; T[root].MaxR = -inf;
	if (l == r)
		return;
	int mid = l + r >> 1;
	build(root * 2, l, mid);
	build(root * 2 + 1, mid + 1, r);
}

void insert(int root, int p, int _l, int _r)
{
	T[root].MaxR = max(T[root].MaxR, _r);
	T[root].MinL = min(T[root].MinL, _l);
	if (T[root].l == T[root].r) {
		return ;
	}
	int mid = (T[root].l + T[root].r) >> 1;
	if (p <= mid)
		insert(root * 2, p, _l, _r);
	else
		insert(root * 2 + 1, p, _l, _r);
}

int askMaxR(int root, int l, int r)
{
	if (l > r)
		return -inf;
	if (T[root].l == l && T[root].r == r)
		return T[root].MaxR;
	int mid = (T[root].l + T[root].r) >> 1;
	if (l > mid)
		return askMaxR(root * 2 + 1, l, r);
	else
	if (r <= mid)
		return askMaxR(root * 2, l, r);
	else
		return max(askMaxR(root * 2, l, mid), askMaxR(root * 2 + 1, mid + 1, r));
}

int askMinL(int root, int l, int r)
{
	if (l > r)
		return inf;
	if (T[root].l == l && T[root].r == r)
		return T[root].MinL;
	int mid = (T[root].l + T[root].r) >> 1;
	if (l > mid)
		return askMinL(root * 2 + 1, l, r);
	else
	if (r <= mid)
		return askMinL(root * 2, l, r);
	else
		return min(askMinL(root * 2, l, mid), askMinL(root * 2 + 1, mid + 1, r));	
}

int check()
{
	vector <int> tmp;
	tmp.clear();
	for(int i = 0; i < n; i++)
		tmp.push_back(a[i]);
	sort(tmp.begin(), tmp.end());
	for(int i = 1; i < n; i++)
		if (tmp[i] == tmp[i - 1])
			return 1;
	tmp.clear();
	for(int i = 0; i < n; i++) {
		tmp.push_back(a[i]);
		tmp.push_back(l[i]);
		tmp.push_back(r[i]);
	}
	sort(tmp.begin(), tmp.end());
	map <int, int> Mp;
	Mp.clear();
	int cur = 0;
	for(int i = 0; i < tmp.size(); i++)
		if (i == 0 || tmp[i] != tmp[i - 1])
			Mp[tmp[i]] = ++cur;
	build(1, 1, cur);
	for(int i = 0; i < n; i++) {
		insert(1, Mp[a[i]], l[ret[i]], r[ret[i]]);
	}
	for(int i = 0; i < n; i++) {
		int x;
		x = askMaxR(1, Mp[l[ret[i]]], Mp[a[i]] - 1);
		if (x >= a[i])
			return 1;
		x = askMinL(1, Mp[a[i]] + 1, Mp[r[ret[i]]]);
		if (x <= a[i])
			return 1;
	}
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	vec.clear();
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		vec.push_back(make_pair(a[i], i + n));
	}
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &l[i], &r[i]);
		vec.push_back(make_pair(l[i], i));
	}
	sort(vec.begin(), vec.end());
	for(int i = 0; i < vec.size(); i++)
	{
		int u = vec[i].second;
		if (u >= n) {
			if (que.empty()) {
				puts("Let's search for another office.");
				return 0;
			} else {
				int v = que.top().second;
				if (r[v] >= a[u - n]) {
					ret[u - n] = v;
					rr[v] = u - n;
					que.pop();
				} else {
					puts("Let's search for another office.");
					return 0;
				}
			}
		} else {
			que.push(make_pair(-r[u], u));
		}
	}
	
	if (check()) {
		puts("Ask Shiftman for help.\n");
	} else {
		puts("Perfect!");
		for(int i = 0; i < n - 1; i++)
			printf("%d ", rr[i] + 1);
		printf("%d\n", rr[n - 1] + 1);
	}
	return 0;
} 
