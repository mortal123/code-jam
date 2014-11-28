#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>

char hash[200];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test--) {
		memset(hash, 0, sizeof(hash));
		int n;
		scanf("%d", &n);
		static char buf1[10], buf2[10];
		for(int i = 1; i <= n; i++) {
			scanf("%s", buf1);
			scanf("%s", buf2);
			hash[buf1[0]] = buf2[0];
		}
		static char buf[1111111];
		scanf("%s", buf);
		int l = 0, r = -1;
		bool flag = false;
		for(int i = 0; buf[i]; i++) {
			if (hash[buf[i]]) {
				buf[i] = hash[buf[i]];
			}
			r = i;
			if (buf[i] == '.') {
				flag = true;
			}
		}
		
		while(l < r && buf[l] == '0') {
			l++;
		}
		while(flag && l < r && buf[r] == '0') {
			r--;
		}
		if (buf[r] == '.') {
			r--;
		}
		if (l > r) {
			printf("0\n");
		} else {
			for(int i = l; i <= r; i++) {
				printf("%c", buf[i]);
			}
			printf("\n");
		}
	}
}
