#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "w", stdout);
	int n = 200000;
	printf("%d\n", n);
	
	for(int i = 2; i <= n; i++) {
		printf("%d %d 1\n", 1, i);
	}
	
	for(int i = 1; i < n ;i++) {
		printf("%d\n", i);
	}
	return 0;
}
