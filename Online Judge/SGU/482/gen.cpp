#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 5;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % 5 + 1);
	}
	return 0;
} 
