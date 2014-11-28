#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

const int N = 444;
const int MOD = 1e9 + 7;

int C[N][N];
int f[N][N];
pair<int, int> items[N];
int bound, n;
map<int, int> counts;

int main() {
	freopen("input.txt", "r", stdin);
	
	for(int i = 0; i < N; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
	}
	
	int test;
	scanf("%d", &test);
	while(test--) {
		counts.clear();
		memset(f, 0, sizeof(f));
		
		scanf("%d %d", &n, &bound);
		for(int i = 1; i <= n; i++) {
			int p;
			scanf("%d", &p);
			counts[p]++;
		}
		
		n = 0;
		for(map<int, int> :: iterator it = counts.begin(); it != counts.end(); ++it) {
			items[++n] = *it;
		}
		
		f[n][0] = 1;
		int total = 0;
		for(int i = n; i >= 1; i--) {
			int cnt = items[i].second;
			int para = 1;
			for(int j = 1; j <= cnt; j++) {
				para = 1LL * para * j % MOD;
			}
			
			for(int j = 0; j <= bound; j++) {
				if (!f[i][j])
					continue;
				
				if (total == 0) {
					(f[i - 1][j + 1] += 1LL * para * f[i][j] % MOD) %= MOD;
					continue;
				}
				
				int sum2 = C[cnt + total - 1][total - 1];
				int sum1 = ((C[cnt + total][total] - sum2) + MOD) % MOD;
				
				// -> j
					(f[i - 1][j] += 1LL * para * f[i][j] % MOD * sum2 % MOD) %= MOD;
				// -> j + 1
					(f[i - 1][j + 1] += 1LL * para * f[i][j] % MOD * sum1 % MOD) %= MOD;
			}
			
			total += cnt;
		}
		
		int ans = 0;
		for(int i = 0; i <= bound; i++) {
			(ans += f[0][i]) %= MOD;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
