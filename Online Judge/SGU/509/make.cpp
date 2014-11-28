#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

long long T, L, a[200];
int n;

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	T = rand() % 20; L = 13;
	n = 5;
	printf("%d %I64d\n", n, L);
	for(int i = 1; i <= n; i++) {
		bool flag;
		long long tmp;
		while(1) {
			flag = true;
			tmp = rand();
			tmp %= L;
			for(int j = 1; j < i; j++)
				if (a[j] == tmp)
					flag = false;
			if (flag)
				break;
		} 
		a[i] = tmp;
		printf("%I64d %d %d\n", tmp, rand(), rand() % 2 ? 1 : -1);
	}
	printf("%I64d\n", T);
	return 0;
}
