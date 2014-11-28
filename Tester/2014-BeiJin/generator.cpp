#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int test = 2, n = 200, m = 100000, q = 100000;

int main() {
	srand(time(0));
	printf("%d\n", test);
	while(test--) {
		printf("%d\n", n);
		for(int i = 2; i <= n; i++) {
			printf("%d %d\n", 1, i);
		}
	}
}