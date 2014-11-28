#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

char buf[111111]; 

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		bool bug = false;
		
		scanf("%s", buf);
		for(int i = 2; buf[i]; i++) {
			if (buf[i] == '0' && buf[i - 1] == '1' && buf[i - 2] == '0') {
				puts("Good");
				bug = true;
				break;
			}
			if (buf[i] == '1' && buf[i - 1] == '0' && buf[i - 2] == '1') {
				puts("Good");
				bug = true;
				break;
			}
		}
		
		if (!bug) {
			puts("Bad");
		}
	}
	return 0;
}
