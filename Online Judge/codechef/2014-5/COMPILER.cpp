#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char buf[1111111];

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%s", buf);
		int ans = 0, cnt = 0;
		for(int i = 0; buf[i]; i++) {
			if (buf[i] == '<') {
				cnt++;
			} else {
				cnt--;
			}
			if (cnt < 0) {
				break;
			} else if (cnt == 0) {
				ans = max(ans, i + 1);
			}
		}
		printf("%d\n", ans);
	}
}
