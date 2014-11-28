#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

const int n = 200000;
int m = 0, number = 0;
int exist[n + 100];

int main() {
	srand(3);
	freopen("input.txt", "w", stdout);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) {
		if (number <= 5 || number <= i / 2) {
			printf("0 %d %d\n", ++m, rand() + 1);
			number++;
			exist[m] = 1;
		} else {
			int tmp = rand() % 3;
			if (tmp == 0) {
				printf("0 %d %d\n", ++m, rand() + 1);
				number++;
				exist[m] = 1;
			} else if (tmp == 1) {
				int t = rand() % m + 1;
				printf("1 %d\n", t);
				number -= exist[t];
				exist[t] = 0;
			} else {
				int a, b;
				do {
					a = rand() % m + 1;
				} while(!exist[a]);
				do {
					b = rand() % m + 1;
				} while(!exist[b]);
				printf("2 %d %d\n", a, b);
			}
		}
	}
	return 0;
}
