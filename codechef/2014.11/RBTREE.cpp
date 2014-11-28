#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int a, b;
int type = 1;

int depth(int x) {
	int result = 0;
	while(x) {
		result++;
		x >>= 1;
	}
	return result;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		static char buffer[100];
		scanf("%s", buffer);
		if (buffer[1] == 'i') {
			type ^= 1;
			continue;
		}
		scanf("%d %d", &a, &b);
		int answer = 0, da = depth(a), db = depth(b);
		while(true) {
			if (a < b) {
				swap(a, b);
				swap(da, db);
			}
			if ((da % 2 == type % 2) == (buffer[1] == 'b')) {
				answer++;
			}
			if (a == b) {
				break;
			}
			da--;
			a /= 2;
		}
		printf("%d\n", answer);
	}
	return 0;
}