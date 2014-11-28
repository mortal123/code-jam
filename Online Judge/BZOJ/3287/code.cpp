#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;


const int MAXN = 100;
long long f[MAXN + 5];
int g[MAXN + 5];

int main() {
	freopen("output.txt", "w", stdout);
	for(int i = 1; i <= 100; i++)
		f[i] = i, g[i] = i - 1;
	for(int i = 1; i <= 100; i++) {
		for(int j = i + 3; j <= 100; j++)
			if (f[i] + f[i] * (j - i - 2) > f[j])
				f[j] = f[i] + f[i] * (j - i - 2), g[j] = i;
	}
	for(int i = 1; i <= 60; i++) {
		printf("%d: %I64d from %d\n", i, f[i], g[i]);
	}
	return 0;
}
