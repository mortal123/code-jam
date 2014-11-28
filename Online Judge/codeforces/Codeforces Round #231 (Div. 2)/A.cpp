#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 111111;

char buf[N];

int main() {
	scanf("%s", buf);
	int i = 0, a = 0, b = 0, c = 0;
	
	for(; buf[i] != '+'; i++) {
		a++;
	}
	
	for(++i; buf[i] != '='; i++) {
		b++;
	}
	
	for(++i; buf[i]; i++) {
		c++;
	}
	
	if (a + b != c) {
		if (a + b + 2 == c) {
			c--;
			a++;
		} else if (a + b == c + 2) {
			c++;
			if (a > 1)
				a--;
			else
				b--;
		} else {
			printf("Impossible\n");
			return 0;
		}
	}
	
	if (a == 0 || b == 0 || c == 0) {
		printf("Impossible\n");
		return 0;
	}
	
	for(int i = 0; i < a; i++) {
		printf("|");
	}
	printf("+");
	for(int i = 0; i < b; i++) {
		printf("|");
	}
	printf("=");
	for(int i = 0; i < c; i++) {
		printf("|");
	}
	printf("\n");
	return 0;
}
