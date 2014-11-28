#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 10000000;
long long f[N + 5];
int n;

int main() {
	for(int i = 1; i <= N; i += 2)
		for(int j = i; j <= N; j += i)
			f[j]++;
	for(int i = 1; i <= N; i++)
		f[i] += f[i - 1];
	for(int i = 1; i <= N; i++)
		f[i] += f[i - 1];
	int test;
	scanf("%d", &test);
	while(test--) {
		static int ttt = 0;
		printf("Case #%d:\n", ++ttt);
		int n;
		scanf("%d", &n);
		cout << 1 + n + f[n - 1] << endl;
	}
}
