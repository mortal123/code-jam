#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 1111111;

bool flag[N];
int count[N];
long long L, R;

int main() {
	flag[1] = true;
	for(int i = 2; i <= 1000000; i++)
		if (flag[i] == false) {
			for(int j = i + i; j <= 1000000; j += i)
				flag[j] = true;
		}
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%lld %lld", &L, &R);
		for(int i = 0; i <= R - L; i++)
			count[i] = 0;
		for(long long i = 1; i * i <= R; i++) {
			long long first = L / i * i;
			if (first < L)
				first += i;
			for(long long iter = first; iter <= R; iter += i) {
				if (i * i < iter)
					count[iter - L] += 2;
				else if (i * i == iter)
					count[iter - L]++;
			}
		}	
		int ans = 0;
		for(int i = 0; i <= R - L; i++) {
			if (flag[count[i]] == false)
				ans++;
		}	
		printf("%d\n", ans);
	}
	return 0;
}
