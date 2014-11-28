#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	printf("2\n");
	for(int i = 1; i <= 2; i++) {
		int n = 50;
		printf("%d\n", n);
		for(int i = 2; i <= 100; i += 2) {
			printf("%d ", i);
		}
		printf("\n");
	}
	return 0;
}
