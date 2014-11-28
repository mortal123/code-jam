#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const int INF = 111111111;

int cntPrime, prime[N], n;
int isPrime[N], used[N];
vector<pair<int, int> > ans;

int main() {
	cntPrime = 0;
	prime[0] = INF;
	fill(isPrime + 1, isPrime + 100000 + 1, true);
	for(int i = 2; i <= 100000; i++) {
		if(isPrime[i]) {
			prime[++cntPrime] = i;	
		}
		for(int j = 1; j <= cntPrime && prime[j] * i <= 100000 && i % prime[j - 1]; j++)
			isPrime[prime[j] * i] = false;
	}
	scanf("%d", &n);
	fill(used + 1, used + n + 1, false);
	for(int i = 1; i <= cntPrime; i++) {
		for(int j = prime[i], k; j <= n; j += prime[i])
			if(!used[j]) {
				for(k = j + prime[i]; k <= n; k += prime[i]) if(!used[k]) {
					used[j] = used[k] = true;
					ans.push_back(make_pair(j, k));
					break;
				}
				j = k;
			}
	}
	printf("%d\n", (int)ans.size());
	/*for(int i = 0; i < (int)ans.size(); i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}*/
	return 0;
}

