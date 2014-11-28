#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 2222222;
const int MOD = (int)(1e9 + 7);
long long mi[N];

int a[N], len;

int main() {
	mi[0] = 2;
	for(int i = 1; i <= 10000; i++) {
		mi[i] = 1;
		for(int j = 1; j <= 10; j++)
			mi[i] = (mi[i] * mi[i - 1]) % MOD;
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		int n;
		scanf("%d", &n);
		len = 0;
		long long res = 1;
		while(n) {
			if (n & 1)
				(res *= mi[len]) %= MOD;
			len++;
			n >>= 1; 
		}
		printf("%d\n", (int)(res * res % MOD));
	}	
	return 0;
}

