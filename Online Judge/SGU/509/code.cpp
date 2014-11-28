#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 110000;

struct Node {
	int c, dir, id, id2;
	int64 pos;
	Node(int64 pos, int c, int dir) : pos(pos), c(c), dir(dir) {}
	Node() {}
}p[MAXN], tar[MAXN];

long long T, L;
int n;

int cmp(const Node &a, const Node &b) {
	return a.pos < b.pos;
}

int cmpID(const Node &a, const Node &b) {
	return a.id < b.id;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %I64d", &n, &L);
	for(int i = 0; i < n; i++) {
		scanf("%I64d %d %d", &p[i].pos, &p[i].c, &p[i].dir);
		p[i].id = i;
	}
	scanf("%I64d", &T);
	sort(p, p + n, cmp);
	for(int i = 0; i < n; i++) {
		p[i].id2 = i;
	}
	long long ds = 0, cnt = 0, final, finalPos;
	for(int i = 1; i < n; i++) {
		if (p[i].dir != p[0].dir) {
			cnt += 2 * T / L % n;
			if (p[i].dir == 1)
				ds = (L + p[0].pos - p[i].pos) % L;
			else
				ds = (L + p[i].pos - p[0].pos) % L;
			if (ds <= 2 * T % L)
				cnt++;
			cnt %= n;
		}
	}
	if (p[0].dir == 1)
		final = cnt;
	else
		final = (n - cnt) % n;
	finalPos = (p[0].pos + L + p[0].dir * (T % L)) % L;
	
	for(int i = 0; i < n; i++) {
		tar[i] = p[i];
		tar[i].pos = (tar[i].pos + L + tar[i].dir * (T % L)) % L;
	}
	sort(tar, tar + n, cmp);
	int last = -1;
	for(int i = n - 1; i >= 0; i--)
		if (tar[i].dir == 1)
			last = i;
	for(int i = n - 1; i >= 0; i--)
		if (tar[i].dir == 1)
			last = i;
		else {
			if (last == -1)
				continue;
			long long ds = tar[last].pos - tar[i].pos;
			if (ds < 0)
				ds += L;
			if (ds <= 2 * T)
				tar[i].c = tar[last].c;
		}
	for(int i = 0; i < n; i++) {
		if (tar[i].pos == finalPos) {
			for(int j = 0; j < n; j++) {
				p[(final + j) % n].c = tar[(i + j) % n].c;
				p[(final + j) % n].pos = tar[(i + j) % n].pos;
				p[(final + j) % n].dir = tar[(i + j) % n].dir;
			}
			break;
		}
	}
	sort(p, p + n, cmpID);
	for(int i = 0; i < n; i++)
		printf("%I64d %d %d\n", p[i].pos, p[i].c, p[i].dir);
	return 0;
}

