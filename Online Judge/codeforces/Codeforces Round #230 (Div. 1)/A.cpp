#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-8;
long long ans = 0;

int main() {
	long long n;
	scanf("%I64d", &n);
	if (n == 0) {
		printf("0\n");
		return 0;
	}
	
	ans = 0;
	int up = n;
	for(int i = 0; i < n; i++) {
		while(1LL * up * up + 1LL * i * i > 1LL * n * n)
			up--;
		if (i == 0)
			ans += 2;
		else
			ans += 4;
		
		up--;
		while(up > 0 && 1LL * up * up + 1LL * (i + 1) * (i + 1) > 1LL * n * n) {
			ans += 4;
			up--;
		}
		
		up++;
	}
	
	printf("%I64d\n", ans + 2);
	return 0;
} 
