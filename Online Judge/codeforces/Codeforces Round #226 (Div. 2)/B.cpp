#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 5555;

char buf[N];
int ans = 0;
char a[10];
int main() {
	freopen("input.txt", "r", stdin);
	a[0] = 'b';
	a[1] = 'e';
	a[2] = 'a';
	a[3] = 'r';
	a[4] = 1;
	
	scanf("%s", buf);
	for(int i = 0; buf[i]; i++) {
		int match = 0;
		bool flag = false;
		for(int j = i; buf[j]; j++) {
			if (i <= j - 3 && buf[j - 3] == 'b' && buf[j - 2] == 'e' && buf[j - 1] == 'a' && buf[j] == 'r')
				flag = true;
			
			ans += flag;
		}
	}
	
	printf("%d\n", ans);
	return 0;
} 
