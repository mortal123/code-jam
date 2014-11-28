#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;



int main() {
	long long a;
	scanf("%lld", &a);
	a %= 6;
	if (a == 1 || a == 3 || a == 0) {
		printf("yes\n");
	} else {
		printf("no\n");
	}
 	return 0;
}
