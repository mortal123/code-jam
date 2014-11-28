#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int n;
string s, ss;

void run(int test) {
	printf("Case #%d: ", test);
	scanf("%d", &n);
	int ans = 1;
	getline(cin, ss);
	getline(cin, ss);
	for(int i = 2; i <= n; i++) {
		getline(cin, s);
		if (s > ss)
			ans++, ss = s;
	}
	printf("%d\n", n - ans);
}

int main() {
	freopen("C-small-1-attempt4.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int testCount = 0;
	scanf("%d", &testCount);
	for(int test = 1; test <= testCount; test++) {
		run(test);
	}
	return 0;
}
