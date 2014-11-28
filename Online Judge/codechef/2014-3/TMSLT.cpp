#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1111111;
const int MOD = 1000000;

int test;
int cnt[N];

int main() {
	ios::sync_with_stdio(false);
	cin >> test;
	while(test--) {
		int n;
		long long a, b, c, d;
		cin >> n >> a >> b >> c >> d;
		for(int i = 1, cur = d; i <= n; i++) {
			cnt[cur] ^= 1;
			cur = (a * cur * cur + b * cur + c) % MOD;
		}
		
		int ans = 0;
		
		for(int i = MOD - 1, sign = 1; i >= 0; i--) {
			if (cnt[i]) {
				cnt[i] = 0;
				ans += sign * i;	
				sign *= -1;	
			}
		}
		
		cout << abs(ans) << endl;
	}
	return 0;
}
