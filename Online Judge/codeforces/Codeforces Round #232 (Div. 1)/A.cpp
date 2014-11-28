#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int MOD = 1000000007;

const int N = 1111;

int C[N * 30];
int n;
int a[N];
map<int, int> cnt;

long long pow(long long a, long long b) {
	if (b == 0)
		return 1;
	if (b == 1)
		return a % MOD;
	
	long long tmp = pow(a, b / 2);
	if (b % 2 == 0) {
		return tmp * tmp % MOD;
	} else {
		return tmp * tmp % MOD * a % MOD;
	}
}

int main() {
	scanf("%d", &n);
	C[n - 1] = 1;
	for(int i = n; i <= 30 * n; i++) {
		C[i] = C[i - 1];
		C[i] = 1LL * C[i] * i % MOD;
		C[i] = 1LL * C[i] * pow((i - (n - 1)) % MOD, MOD - 2) % MOD;
	}
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		int x = a[i];
		for(long long j = 2; j * j <= x; j++) {
			while(x % j == 0) {
				cnt[j]++;
				x /= j;
			}
		}
		
		if (x > 1)
			cnt[x]++;
	}
	
	long long ans = 1;
	
	for(map<int, int> :: iterator it = cnt.begin(); it != cnt.end(); it++) {		
		ans = ans * C[it->second + n - 1] % MOD;
	}
	
	printf("%I64d\n", ans);
	return 0;
} 
