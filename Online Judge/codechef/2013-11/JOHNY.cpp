#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
pair<int, int> a[1000000];
 
int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i].first);
			a[i].second = i;
		}
		sort(a + 1, a + n + 1);
		int k;
		scanf("%d", &k);
		for(int i = 1; i <= n; i++) {
			if (a[i].second == k)
				printf("%d\n", i);
		}
	}
	return 0;
} 
