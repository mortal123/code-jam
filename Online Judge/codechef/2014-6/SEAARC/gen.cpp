#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int LIMIT = 100000;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 100000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		printf("%d ", rand() % 1250 + 1);
	}
	printf("\n");
}
