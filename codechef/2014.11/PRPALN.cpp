#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 111111;
char str[N];
int n;

bool solve(char str[], int n, int del) {
	for(int l = 0, r = n - 1; l <= r; ) {
		if (l == del) {
			l++;
		} else if (r == del) {
			r--;
		} else {
			if (str[l] != str[r]) {
				return false;
			}
			l++;
			r--;
		}
	}
	return true;
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%s", str);
		n = strlen(str);
		bool flag = true;
		for(int i = 0; i < n; i++) {
			if (str[i] != str[n - i - 1]) {
				if (solve(str, n, i) || solve(str, n, n - i - 1)) {
					break;
				}
				flag = false;
				break;
			}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}

