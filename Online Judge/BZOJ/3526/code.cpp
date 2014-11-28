#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 222222;

struct Node {
	int pass[2][2];
	int v[2][2];
	void set(int av, int bv) {
		v[0][0] = v[1][0] = av;
		v[0][1] = v[1][1] = bv;
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++) {
				pass[i][j] = (v[0][i] <= v[1][j]);
			}
	}
};

Node tree[N << 2];
int n, m;
int a[N], b[N];

Node combine(const Node &a, const Node &b) {
	Node result;
	for(int i = 0; i < 2; i++) {
		result.v[0][i] = a.v[0][i];
		result.v[1][i] = b.v[1][i];
	}
	
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++) {
			int &t = result.pass[i][j];
			t = 0;
			for(int k = 0; k < 2 && t == 0; k++)
				for(int l = 0; l < 2 && t == 0; l++)
					t |= (a.v[1][k] <= b.v[0][l] && a.pass[i][k] && b.pass[l][j]);
		}
	return result;
}

void modify(int x, int l, int r, int p, int av, int bv) {
	if (l == r) {
		tree[x].set(av, bv);
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) {
		modify(x << 1, l, mid, p, av, bv);
	} else {
		modify(x << 1 | 1, mid + 1, r, p, av, bv);
	}
	tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
}

void build(int x, int l, int r) {
	if (l == r) {
		tree[x].set(a[l], b[l]);
	} else {
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i], &b[i]);
	}	
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		modify(1, 1, n, u, a[v], b[v]);
		modify(1, 1, n, v, a[u], b[u]);
		swap(a[u], a[v]);
		swap(b[u], b[v]);
		bool ans = false;
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
				ans |= tree[1].pass[j][k];
		printf("%s\n", ans ? "TAK" : "NIE");
	}
}
