#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;

int n, m;
int a[N], pos;

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	pos = 0;
	for(int i = 0; i < m; i++) {
		static char buf[N];
		int d;
		scanf("%s %d", buf, &d);
		if (buf[0] == 'C') {
			(pos += d) %= n;
		} else if (buf[0] == 'A') {
			(pos += n - d) %= n;
		} else {
			printf("%d\n", a[(pos + d - 1) % n]);
		}
	}
	return 0;
}

