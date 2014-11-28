#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;
int ans[N];
pair<int, int> events[N];
int n, m, cnt[20];
char buf[N];

int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", buf + 1);
	sort(events + 1, events + m + 1);
	for(int i = 1; i <= n; i++) {
		int x = buf[i] - '0';
		
		cnt[x] ++;
		int res = 0;
		for(int j = 0; j < x; j++)
			res += (x - j) * cnt[j];
		for(int j = x + 1; j < 10; j++)
			res += (j - x) * cnt[j];
		ans[i] = res;
	}
	
	for(int i = 1; i <= m; i++) {
		int a;
		scanf("%d", &a);
		printf("%d\n", ans[a]);
	}
	return 0;
}
