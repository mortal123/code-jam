#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111;

char buf[N + 1000];

int main() {
	scanf("%s", buf);
	char last = 0;
	int ans = 0;
	for(int i = 0, j = 0; buf[i]; i = j) {
		for(j = i; buf[j] == buf[i]; j++);
		if ((j - i) % 2 == 0)
			ans++;
	}
	
	printf("%d\n", ans);
	
	return 0;
} 
