#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1111111111;

int lower, upper;

int main() {
	lower = -INF, upper = INF;
	int n;
	scanf("%d", &n);
	char type[10], ans;
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%s %d %c", type, &x, &ans);
		if (type[0] == '>' && type[1] == '=') {
			if (ans == 'Y') {
				lower = x;
			} else if (ans == 'N') {
				upper = x - 1;
			}
		} else if (type[0] == '>') {
			if (ans == 'Y') {
				lower = x + 1;
			} else {
				upper = x;
			}
		} else if (type[0] == '<' && type[1] == '=') {
			if (ans == 'Y') {
				upper = x;
			} else {
				lower = x + 1;
			}
		} else if (type[0] == '<') {
			if (ans == 'Y') {
				upper = x - 1;
			} else {
				lower = x;
			}
		}
	}
	if (lower > upper) {
		printf("Impossible\n");
	} else {
		printf("%d\n", lower);
	}
	return 0;
} 
