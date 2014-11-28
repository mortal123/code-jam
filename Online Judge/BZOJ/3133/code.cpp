#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 210000;
const int MAXM = 18;

int Rank[MAXN], visit[MAXN];
int dep[MAXN], fa[MAXN][20], obj[MAXN], n, m, root;

struct num
{
	int v;
	friend int operator <(num a, num b)
	{
		return Rank[a.v] < Rank[b.v];
	}
};

num make_num(int x)
{
	num a;
	a.v = x;
	return a;
}

set <num> T;
vector <int> e[MAXN];

int cmp(int a, int b)
{
	return obj[a] < obj[b];
}

void dfs(int x, int ffa)
{
	obj[x] = x;
	dep[x] = dep[ffa] + 1;
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		dfs(y, x);
		obj[x] = min(obj[x], obj[y]);
	}
	sort(e[x].begin(), e[x].end(), cmp);
}

int top = 0;

void dfsRank(int x)
{
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		dfsRank(y);
	}
	Rank[x] = ++top;
}

int push()
{
	num tmp = *(T.begin());
	T.erase(tmp);
	visit[tmp.v] = 1;
	//printf("push at %d\n", tmp.v);
	return tmp.v;
}

int reMove(int pos)
{
	int t = pos;
	for(int i = MAXM; i >= 0; i--)
		if (visit[fa[pos][i]])
			pos = fa[pos][i];
	visit[pos] = 0;
	T.insert(make_num(pos));
	return -dep[pos] + dep[t];
}

int main()
{
	freopen("input.txt", "r", stdin);
	T.clear();
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		e[i].clear();
		visit[i] = 0;
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d", &fa[i][0]);
		if (fa[i][0])
			e[fa[i][0]].push_back(i);
		else
			root = i;
	}
	for(int j = 1; j <= MAXM; j++)
		for(int i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	dfs(root, 0);
	dfsRank(root);
	for(int i = 1; i <= n; i++) {
		T.insert(make_num(i));
	}
	for(int i = 1; i <= m; i++) {
		int op, k;
		scanf("%d %d", &op, &k);
		if (op == 1) {
			for(int j = 1; j < k; j++) {
				push();
			}
			printf("%d\n", push());
		} else {
			printf("%d\n", reMove(k));
		}
	}
	return 0;
} 

