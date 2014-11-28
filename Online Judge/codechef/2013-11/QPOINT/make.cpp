#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 1000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		int num = 3;
		printf("%d", num);
		printf(" %d %d", i * 100 + 1, 1);
		printf(" %d %d", i * 100 + 50, 50);
		printf(" %d %d\n", i * 100 + 60, 1);
	}
	int qnum = 1000;
	printf("%d\n", qnum);
	for(int i = 1; i <= qnum; i++) {
		printf("%d %d\n", rand() % 1000, rand() % 4);
	}
	return 0;
}
