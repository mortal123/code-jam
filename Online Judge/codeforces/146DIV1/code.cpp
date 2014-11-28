#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 2000;

int check[N + 10];

int main() {
	int cnt = 0;
	for(int i = 2; i <= N; i++) {
		if (check[i])
			continue;
		cnt++;
		for(int j = i + i; j <= N; j += i)
			check[j] = 1;
	}
	printf("%d", cnt);
	return 0;
} 
