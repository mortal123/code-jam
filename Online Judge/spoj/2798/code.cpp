#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int inf = 1000000;

int n;
vector<int> e[N];
int que[N], fa[N], tag[N], top[N], pos[N], size[N], son[N], color[N], rpos[N];
struct Node {
	int l, r;
	bool flag;
	inline void update(const Node &a, const Node &b) {
		flag = (a.flag || b.flag);
	}
}T[N * 4];

void build(int root, int l, int r) {
	T[root].l = l;
	T[root].r = r;
	T[root].flag = false;
	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(root * 2, l, mid);
	build(root * 2 + 1, mid + 1, r);
}

void modify(int root, int pos, int val) {
	if (T[root].l == T[root].r) {
		T[root].flag = val;
		return;
	}
	int mid = (T[root].l + T[root].r) / 2;
	if (pos <= mid)
		modify(root * 2, pos, val);
	else
		modify(root * 2 + 1, pos, val);
	T[root].update(T[root * 2], T[root * 2 + 1]);
}

int query(int root, int l, int r) {
	if (T[root].flag == false)
		return inf;
		
	if (T[root].l == T[root].r)
		return T[root].r;
	int mid = (T[root].l + T[root].r) / 2;
	if (l <= mid) {
		int res = query(root * 2, l, r);
		if (res != inf)
			return res;
	}
	if (r > mid) {
		int res = query(root * 2 + 1, l, r);
		if (res != inf)
			return res;
	}
	return inf;
}

void buildTree() {
	int head = 1, tail = 1;
	que[tail] = 1;
	fa[1] = 0;
	while(head <= tail) {
		int x = que[head++];
		for(int i = 0; i < e[x].size(); i++) {
			int y = e[x][i];
			if (y == fa[x])
				continue;
			fa[y] = x;
			que[++tail] = y;
		}
	}	
	fill(size + 1, size + n + 1, 0);
	for(int i = n; i >= 1; i--) {
		int x = que[i];
		size[x]++;
		size[fa[x]] += size[x];
	}
	for(int i = 1; i <= n; i++) {
		int x = que[i];
		int mm = -1;
		son[x] = -1;	
		for(int j = 0; j < e[x].size(); j++) {
			int y = e[x][j];
			if (y == fa[x])
				continue;
			if (size[y] > mm) {
				mm = size[y];
				son[x] = y;
			}
		}
	}
	fill(tag + 1, tag + n + 1, -1);
	tag[0] = 0;
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		int x = que[i];
		if (tag[x] == -1) {
			int temp = x;
			tag[x] = tag[fa[x]] + 1;
			while(temp != -1) {
				tag[temp] = tag[x];
				top[temp] = x;
				pos[temp] = ++tot;
				rpos[tot] = temp;
				temp = son[temp];
			}
		}
	}
	build(1, 1, tot);
}

int ask(int x) {
	if (x == 0)
		return inf;
	int res;
	
	res = ask(fa[top[x]]);
	if (res != inf)
		return rpos[res];
	res = query(1, pos[top[x]], pos[x]);
	if (res != inf)
		return rpos[res];
	return inf;
}

inline int read() {
	char ch;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
	
	int res = 0;
	for(; '0' <= ch && ch <= '9'; ch = getchar())
		res = res * 10 + ch - '0';
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	int m;
	n = read(); m = read();
	for(int i = 1; i < n; i++) {
		int a, b;
		a = read(); b = read();
		e[a].push_back(b);
		e[b].push_back(a);
	}
	buildTree();
	for(int i = 1; i <= m; i++) {
		int type, x;
		type = read(); x = read();
		if (type == 0) {
			color[x] ^= 1;
			modify(1, pos[x], color[x]);
		} else {
			int tmp = ask(x);
			printf("%d\n", tmp == inf ? -1 : tmp);
		}
	}
	return 0;
}
