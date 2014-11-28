#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 55;
const int INF = 1e9;

int a[N];
int n, q;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}	
	
	scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int k, ans = 0;
		scanf("%d", &k);
		for(int l = 1; l <= n; l++) {
			int minV = INF;
			for(int r = l; r <= n; r++) {
				minV = min(minV, a[r]);
				if (minV == k)
					ans++;
			}
		}
		
		printf("%d\n", ans);
	}
}
