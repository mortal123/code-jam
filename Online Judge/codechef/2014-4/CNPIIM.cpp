#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

const int N = 2500;

long long sum[N + 5], ss[N * N + 5];

int main() {
	for(int i = 1; i <= N * N; i++)
		for(int j = 1; i * j <= N * N; j++) {
			ss[i * j]++;
		}
		
	for(int i = 1; i <= N * N; i++) {
		ss[i] += ss[i - 1];
	}
	
	for(int a = 1; a <= N; a++) {
		for(int b = 1; a + b <= N; b++) {
			sum[a + b] += ss[a * b - 1];
		}
	}
	int test;
	scanf("%d", &test);
	while(test--) {
		int n;
		scanf("%d", &n);
		cout << sum[n] << endl;
	}
	return 0;
}
