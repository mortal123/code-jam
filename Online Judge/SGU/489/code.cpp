#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

int f[2][10005];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	if (n == 1) {
		printf("%d\n", 1 % m);
		return 0;
	}
	n--;
	f[1][1] = 1;
	for(int i = 2; i <= n; i++) {
		int now = i % 2, last = (now ^ 1);
		for(int j = 1; j <= i; j++) {
			f[now][j] = (f[now][j - 1] + f[last][i - j]) % m;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		ans = (ans + f[n % 2][i]) % m;
	cout << (ans + ans) % m << endl;
	return 0;
} 
