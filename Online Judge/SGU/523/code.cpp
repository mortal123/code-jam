#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 110;

int n, f, visit[MAXN], hash[MAXN], a[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &f);
	for(int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		hash[a[i]] = 1;
	}
	visit[f] = 1;
	for (int i = 1; i <= n; i++) {
		if (visit[a[i]])
			continue;
		int dx = 1;
		if (a[i] < f)
			dx = -1;
		while(f != a[i]) {
			f += dx;
			if (hash[f]) {
				printf("%d ", f);
				hash[f] = 0;
			}
			visit[f] = 1;
		}
	}
	return 0;
}
