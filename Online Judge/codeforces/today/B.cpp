#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

char str[1000];
int main() {
	gets(str);
	int cnt = 0;
	for(int i = 0; str[i]; i++) {
		cnt = cnt * 10 + str[i] - '0';
		cnt %= 3;
	}
	printf("%s\n", cnt ? "no" : "yes");
	return 0;
}
