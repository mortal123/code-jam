#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int inf = 1000000000;
const int MAXN = 60;
int f[100005];
int a[MAXN], n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	for(int i = a[n - 1]; i >= 1; i--) {
		f[i] = 0;
		for(int j = 0; j < n; j++)
			f[i] += a[j] / i;
		for(int j = i + i; j <= a[n - 1]; j += i) {
			int res = f[j];
			for(int k = 0; k < n; k++) {
				res += (a[k] % j) / i;
			}
			f[i] = min(f[i], res);
		}
	}
	printf("%d\n", f[1]);
	return 0;
} 
