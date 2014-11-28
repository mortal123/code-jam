#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 110000;
const int MAXLEN = 2000020;
const int zero = 1000005;

int n;
int h[MAXLEN + 10];

struct Node {
	int x, y, id;
}p[MAXN];

vector<int> ans1, ans2;
int cnt[MAXN], who[MAXN];

int cmp(Node a, Node b) {
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}

int f[MAXN], g[MAXN];

int lowbit(int x) {
	return x & (-x);
}

int ask(int pos) {
	int res = 0;
	pos += zero;
	for(int i = pos; i; i -= lowbit(i))
		res = max(res, h[i]);
	return res;
}

int ins(int pos, int x) {
	pos += zero;
	for(int i = pos; i <= MAXLEN; i += lowbit(i)) {
		h[i] = max(h[i], x);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		p[i].x = x; p[i].y = y;
		p[i].id = i;
	}
	sort(p + 1, p + n + 1, cmp);
	memset(h, 0, sizeof(h));
	for(int i = 1, j = 1; i <= n; i++) {
		for(; j <= n && p[j].x < p[i].x; j++)
			ins(p[j].y, f[j]);
		f[i] = ask(p[i].y - 1) + 1;
	}
	memset(h, 0, sizeof(h));
	for(int i = n, j = n; i >= 1; i--) {
		for(; j >= 1 && p[j].x > p[i].x; j--)
			ins(-p[j].y, g[j]);
		g[i] = ask(-p[i].y - 1) + 1;
	}
	int ansLen = 0;
	for(int i = 1; i <= n; i++)
		ansLen = max(ansLen, f[i] + g[i] - 1);
	for(int i = 1; i <= n; i++) {
		if (f[i] + g[i] - 1 != ansLen)
			continue;
		ans1.push_back(p[i].id);
		cnt[f[i]]++; who[f[i]] = p[i].id;
	}
	for(int i = 1; i <= ansLen; i++)
		if (cnt[i] == 1)
			ans2.push_back(who[i]);
	sort(ans1.begin(), ans1.end());
	printf("%d", ans1.size());
	for(int i = 0; i < ans1.size(); i++)
		printf(" %d", ans1[i]);
	printf("\n");
	sort(ans2.begin(), ans2.end());
	printf("%d", ans2.size());
	for(int i = 0; i < ans2.size(); i++)
		printf(" %d", ans2[i]);
	printf("\n");
	return 0;
}
