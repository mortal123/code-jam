#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1111;

int f[N];
char buf[N];
int n;

int main() {
	scanf("%s", buf + 1);
	n = strlen(buf + 1);
	for(int i = 1; i <= n; i++) {
		f[i] = 1;
	}
	
	int ans = 0;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < i; j++)
			if (buf[i] == buf[j] && (i - j) % 2 == 1)
				f[i] = max(f[j] + 1, f[i]);
		ans = max(ans, f[i]);
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
