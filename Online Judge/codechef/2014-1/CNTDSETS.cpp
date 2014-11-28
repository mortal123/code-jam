#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int n, d;
long long tot;

long long pow(long long a, long long b, long long mod) {
	if (b == 0)
		return 1;
		
	if (b == 1)
		return a % mod;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &d);
		tot = pow(d + 1, n, MOD - 1);
	}
	return 0;
}
