#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int n, m;

int calc(int n) {
	int result = 0, nn = (n + 1) % m;
	result += 6LL * nn % m * nn % m * nn % m * nn % m;
	result %= m;
	result -= 15LL * nn % m * nn % m * nn % m;
	result %= m;
	result += 10LL * nn % m * nn % m;
	result -= 1;
//	cout << r << " " << 1LL * result * nn / 30 << endl;
	return 1LL * (result % m + m) % m * nn % m;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		int answer = 0;
		m *= 30;
		for(int i = 1; i <= n; i++) {
			int r = n / (n / i);
			answer += 1LL * (n / i) % m * (calc(r) - calc(i - 1)) % m;
			answer %= m;
			i = r;
		} 
		printf("%d\n", (answer + m) % m / 30);
	}
	return 0;
}

