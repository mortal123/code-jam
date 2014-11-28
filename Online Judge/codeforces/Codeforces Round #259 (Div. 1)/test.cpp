#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int m = 3;

int a[111][111], b[111][111];

int bit(int x) {
	int res = 0;
	while(x) {
		res += x % 2;
		x /= 2;
	}
	return res;
}

int main() {
	for(int i = 0; i < (1 << m); i++, puts(""))
		for(int j = 0; j < (1 << m); j++) {
			printf("%d ", a[i][j] = bit(i ^ j));
		}
	int n = (1 << m);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			b[i][j] = 0;
			for(int k = 0; k < n; k++) {
				b[i][j] += a[i][k] * a[k][j];
			}
		}
	for(int i = 0; i < n; i++, puts(""))
		for(int j = 0; j < n; j++) {
			printf("%d ", b[i][j]);
		}
	return 0;
}

