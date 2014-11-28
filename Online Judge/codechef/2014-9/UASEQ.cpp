#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;
const long long INF = (1LL << 60);

int n, k, a[N];
long long s1 = INF, s2 = INF;

bool go(int pos, int have, long long start, long long delta) {
	start += delta * pos;
	for(int i = pos; have <= k && i < n; i++) {
		if (start != a[i]) {
			have++;
		}
		start += delta;
	}
	return have <= k;
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for(int mask = 0; mask < (1 << (k + 2)); mask++) {
		vector<int> pos;
		for(int i = 0; i < (k + 2); i++) {
			if (mask >> i & 1) {
				pos.push_back(i);
			}
		}
		if (pos.size() < 2) {
			continue;
		}
		if ((a[pos[1]] - a[pos[0]]) % (pos[1] - pos[0]) != 0) {
			continue;
		}
		int delta = (a[pos[1]] - a[pos[0]]) / (pos[1] - pos[0]);
		long long start = a[pos[0]] - 1LL * delta * pos[0];
		bool flag = true;
		for(int i = 0; i < (k + 2) && flag; i++) {
			if ((mask >> i & 1) != (a[i] == start + 1LL * delta * i)) {
				flag = false;
			}
		}
		if (!flag) {
			continue;
		}
		if (go(k + 2, (k + 2) - (int)pos.size(), start, delta)) {
			if (start < s1 || start == s1 && delta < s2) {
				s1 = start;
				s2 = delta;
			}
		}
	}
	for(int i = 0; i < n; i++) {
		printf("%I64d%c", s1, i == n - 1 ? '\n' : ' ');
		s1 += s2;
	}
	return 0;
}

