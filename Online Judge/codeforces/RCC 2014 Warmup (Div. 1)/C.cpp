#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

const int N = 111;
const int LIMIT = 10000;
const double eps = 1e-6;

int a[N], b[N];
int n, m;

int isSq(long long t) {
	long long tt = (long long)sqrt(t + eps);
	return tt * tt == t;
}

void gen(int n, int a[]) {
	bool flag = false;
	while(!flag) {
		long long total = 0;
		for(int i = 1; i < n; i++) {
			a[i] = rand() % LIMIT + 1;
			total += 1LL * a[i] * a[i];
		}
		for(int i = 1; i <= LIMIT; i++) {
			long long t = total + i * i;
			a[n] = i;
			if (isSq(t)) {
				flag = true;
				break;
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	gen(n, a);
	gen(m, b);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			printf("%d%c", a[i] * b[j], j == m ? '\n' : ' ');
		}
	}
	return 0;
} 
