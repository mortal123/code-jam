#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int isPrime(int x) {
	for(int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		int x, y;
		scanf("%d %d", &x, &y);
		for(int i = 1; ; i++) {
			if (isPrime(x + y + i)) {
				printf("%d\n", i);
				break;
			}
		}
	}
} 
