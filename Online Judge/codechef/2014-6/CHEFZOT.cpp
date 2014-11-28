#include <cstdio>
#include <cstdlib>
#include <algorithm> 
using namespace std;

const int N = 111111;

int n;
int a[N];

int main() {
	int ans = 0;
	scanf("%d", &n);
	for(int i = 1, len = 0; i <= n; i++) {
		scanf("%d", &a[i]);
		if (a[i] == 0) {
			len = 0;
		} else {
			ans = max(ans, ++len);
		}
	}
	printf("%d\n", ans);
	return 0;
}
