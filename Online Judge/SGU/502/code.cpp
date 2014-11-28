#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int tot, cnt[100];
long long n, pro;

void dfs(int dep, long long s, int left) {
	if (++pro > 1000000)
		return;
	if (dep > tot) {
		if (left == 0) {
			printf("%I64d\n", s);
			exit(0);
		}
		return;
	}
	for(int i = 0; i < 10; i++) {
		if (i == 0 && s == 0)
			continue;
		if (cnt[i] == 0)
			continue;
		cnt[i]--;
		dfs(dep + 1, s * 10 + i, (left * 10 + i) % 17);
		cnt[i]++;
	}
}

int main() {
	scanf("%I64d", &n);
	while(n) {
		cnt[n % 10]++;
		n /= 10;
		tot++;
	}
	dfs(1, 0, 0);
	printf("-1\n");
	return 0;
}
