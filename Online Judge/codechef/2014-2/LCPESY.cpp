#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int cnt[1111];
char buf[111111];

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		fill(cnt, cnt + 1111, 0);
		scanf("%s", buf);
		for(int i = 0; buf[i]; i++) {
			cnt[buf[i]]++;
		}
		
		int ans = 0;
		scanf("%s", buf);
		for(int i = 0; buf[i]; i++) {
			ans += (cnt[buf[i]] > 0);
			cnt[buf[i]]--;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
