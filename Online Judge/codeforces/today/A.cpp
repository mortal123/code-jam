#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char str[200];
int main() {
	int ans = 1;
	for(int i = 1; i <= 20; i++) {
		printf("%d: %d\n", i, ans);
		ans = ans * 16 % 7;
	}
	int n;
	gets(str);
	int left = 0;
	for(int i = 0; str[i]; i++) {
		left = left * 10 + str[i] - '0';
		left %= 7;
	}
	if (left == 0)
		printf("yes\n");
	else
		printf("no\n");
	return 0;
}
