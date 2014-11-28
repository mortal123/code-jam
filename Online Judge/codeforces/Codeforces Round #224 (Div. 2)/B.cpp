#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int N = 1111;

long long a, b, w, x, c;
pair<long long, long long> f[N][41];

long long cycle(long long a, long long b) {
	if (a >= 0)
		return a;
	return w + a;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%I64d %I64d %I64d %I64d %I64d", &a, &b, &w, &x, &c);
	for(int i = 1; i <= w; i++) {
		f[i][0] = make_pair(cycle(i - x, w), i < x);
	}
	
	f[0][0] = make_pair(w - x, 1);
	
	if (c <= a) {
		printf("0\n");
		return 0;
	}
	
	for(int i = 1; i <= 40; i++) {
		for(int j = 0; j <= w; j++) {
			f[j][i] = make_pair(f[f[j][i - 1].first][i - 1].first, f[j][i - 1].second + f[f[j][i - 1].first][i - 1].second);
		}
	}
	
	long long ans = 0;
	
	for(int i = 40; i >= 0; i--) {
		if (a - f[b][i].second >= c - (1LL << i))
			continue;
		ans += (1LL << i);
		a -= f[b][i].second;
		c -= (1LL << i);
		b = f[b][i].first;
	}
	
	printf("%I64d\n", ans + 1);
	
	return 0;
} 
