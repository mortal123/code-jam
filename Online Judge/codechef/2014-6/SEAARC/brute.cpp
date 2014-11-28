#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int LIMIT = 100000;
const int N = 111111;

int a[N], n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			if (a[i] == a[j]) {
				for(int k = 1; k < i; k++)
					if (a[k] != a[i])
						for(int l = i + 1; l < j; l++)
							if (a[k] == a[l]) {
								ans++;
							}
			}
	printf("%d\n", ans);
}
