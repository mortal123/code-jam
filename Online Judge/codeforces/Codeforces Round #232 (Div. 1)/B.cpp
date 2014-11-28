#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int n;

int isPrime(int x) {
	for(int i = 2; 1LL * i * i <= x; i++) {
		if (x % i == 0)
			return false;
	}
	
	return true;
}

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void simple(long long &a, long long &b) {
	long long t = gcd(a, b);
	a /= t;
	b /= t;
}

int main() {
	int test;
	scanf("%d", &test);
	for(int i = 1; i <= test; i++) {
		int n;
		scanf("%d", &n);
		int lower = n, upper = n + 1;
		while(!isPrime(lower))
			lower--;
		while(!isPrime(upper))
			upper++;
		long long a = 1LL * upper * lower - 2 * upper + (n - lower + 1) * 2, b = 2LL * lower * upper;
		simple(a, b);
		printf("%I64d/%I64d\n", a, b);
	}
	return 0;
} 
