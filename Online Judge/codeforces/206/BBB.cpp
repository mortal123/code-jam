#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
	freopen("input.txt", "w", stdout);
	printf("100000 1 1 1 1\n");
	for(int i = 1; i <= 100000; i++)
		printf("%d ", 1);
	return 0;
}
