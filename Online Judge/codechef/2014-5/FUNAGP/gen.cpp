#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

//int p1 = 1e9 + 7, p2 = 1e9 + 9;
int p1 = 3, p2 = 2;
const int LIMIT = 10;

int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	int test = 1;
	printf("%d\n", test);
	while(test--) {
		int n = 10, q = 10, r = rand() % LIMIT;
		printf("%d %d %d %d %d\n", n, q, r, p1, p2);
		for(int i = 1; i <= n; i++) {
			printf("%d ", 0);
		}
		puts("");
		for(int i = 1; i <= q; i++) {
			int t = rand() % 3;
			if (t == 0) {
				int l = rand() % n + 1, r = rand() % n + 1;
				if (l > r) {
					swap(l, r);
				}
				printf("0 %d %d %d %d\n", rand() % LIMIT + 1, rand() % LIMIT + 1, l, r);
			} else if (t == 1) {
				printf("1 %d %d\n", rand() % n + 1, rand() % 100 + 1);
			} else {
				int l = rand() % n + 1, r = rand() % n + 1;
				if (l > r) {
					swap(l, r);
				}
				printf("2 %d %d\n", l, r);
			}
		}
	}
}
