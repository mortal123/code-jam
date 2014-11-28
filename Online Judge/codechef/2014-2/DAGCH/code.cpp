#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int INF = 1e9;

int val[N * 4];

int ans[N];
int n, m, q, father[N];
vector<int> from[N], sons[N];
int left[N], right[N], pos, cnt[N], super[N];

char buf[10000];

inline void read(int &n) {
	static char ch;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	for(n = 0; ch >= '0' && ch <= '9'; ch = getchar()) {
		n = n * 10 + ch - '0';
	}
}

inline void myAssert(bool flag) {
	if (!flag) {
		int x = 0, y = 1;
		y = y / x;
	}
}

void dfs(int x) {
	left[x] = ++pos;
	for(int i = 0; i < (int)sons[x].size(); i++) {
		int y = sons[x][i];
		dfs(y);
	}
	
	right[x] = pos;
}

int ask(int x, int l, int r, int qpos) {
	if (qpos <= l && r <= qpos) {
		return val[x];
	}
	
	val[x << 1] = min(val[x << 1], val[x]);
	val[x << 1 | 1] = min(val[x << 1 | 1], val[x]);
	int mid = (l + r) / 2;
	if (qpos <= mid) {
		return ask(x << 1, l, mid, qpos);
	} else {
		return ask(x << 1 | 1, mid + 1, r, qpos);
	}
}

void insert(int x, int l, int r, const int &ql, const int &qr, const int &v) {
	if (qr < l || ql > r)
		return ;
	
	if (ql <= l && r <= qr) {
		val[x] = min(val[x], v);
		return ;
	}
	
	int mid = (l + r) / 2;
	insert(x << 1, l, mid, ql, qr, v);
	insert(x << 1 | 1, mid + 1, r, ql, qr, v);
}

void run() {
	read(n); read(m); read(q);
	//("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i++) {
		from[i].clear();
		sons[i].clear();
		cnt[i] = 0;
	}
		
	for(int i = 1; i <= m; i++) {
		int a, b;
		read(a); read(b);
		//scanf("%d %d", &a, &b);
		from[b].push_back(a);
	}
	
	father[1] = 0;
	for(int i = 2, cur = 1; i <= n; i++) {
		cur = -1;
		for(int j = 0; j < (int)from[i].size(); j++) {
			if (from[i][j] < i && from[i][j] > cur)
				cur = from[i][j];
		}
			
		sons[cur].push_back(i);
		father[i] = cur;
	}
	
	pos = 0;
	dfs(1);
	for(int i = 0; i <= 4 * n; i++) {
		val[i] = INF;
	}
	
	for(int x = n; x >= 2; x--) {
		super[x] = INF;
		for(int i = 0; i < (int)from[x].size(); i++) {
			int y = from[x][i];
			if (y > x) {
				super[x] = min(super[x], ask(1, 1, n, left[y]));
			} else {
				super[x] = min(super[x], y);
			}
		}
		//myAssert(super[x] < x);
		insert(1, 1, n, left[x], right[x], super[x]);
		cnt[super[x]]++;
	}
	
	for(int i = 1; i <= q; i++) {
		int x;
		read(x);
		//scanf("%d", &x);
		printf("%d%c", cnt[x], i == q ? '\n' : ' ');
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int test;
	read(test);
	//scanf("%d", &test);
	while(test--) {
		run();
	}
	return 0;
} 
