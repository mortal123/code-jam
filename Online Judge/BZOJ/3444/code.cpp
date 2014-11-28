#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

const int N = 1111111;
const int MOD = 989381;

int dgr[N], other[N];
int n, m, total = 0;
set<pair<int, int> > s;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) {
			swap(a, b);
		}
		
		if (s.count(make_pair(a, b)))
			continue;
		s.insert(make_pair(a, b));
		
		if (dgr[a] > dgr[b]) {
			swap(a, b);
		}
		
		
		if (dgr[a] == 0 && dgr[b] == 0) {
			dgr[a] = dgr[b] = 1;
			other[a] = b;
			other[b] = a;
		} else if (dgr[a] == 0 && dgr[b] == 1) {
			dgr[b]++;
			b = other[b];
			dgr[a]++;
			other[a] = b;
			other[b] = a;
		} else if (dgr[a] == 1 && dgr[b] == 1) {
			if (other[a] == b) {
				printf("0\n");
				return 0;
			}
			
			dgr[a]++;
			dgr[b]++;
			a = other[a];
			b = other[b];
			other[a] = b;
			other[b] = a;
		} else {
			printf("0\n");
			return 0;
		}
	}
	
	int res = 1;
	int total = 0, power = 0;
	for(int i = 1; i <= n; i++) {
		if (dgr[i] == 1)
			power++;
		else if (dgr[i] == 0)
			total++;
	}
	
	power /= 2;
	total += power;
	for(int i = 1; i <= power; i++)
		res = res * 2 % MOD;
	for(int i = 1; i <= total; i++)
		res = 1LL * res * i % MOD;
		
	printf("%d\n", res);
}
