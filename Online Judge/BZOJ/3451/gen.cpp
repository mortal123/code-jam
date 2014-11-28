#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int n = 10;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	printf("%d\n", n);
	for(int i = 1; i < n; i++) {
		printf("%d %d\n", i, rand() % i);
	}
	
	return 0;
}
