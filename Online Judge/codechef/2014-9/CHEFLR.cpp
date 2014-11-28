#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 111111;
const int MOD = 1e9 + 7;
char buf[N];


int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%s", buf);
		int result = 0;	
		for(int i = 0; buf[i]; i++) {
			result *= 2;
			if (buf[i] == 'r') {
				result++;
			}
			result %= MOD;
		}	
		(++result) %= MOD;
		int power = 1, answer = 0, len = strlen(buf) + 1;
		for(int i = 1; i < len; i++) {
			if (i % 2 == len % 2) {
				answer += power;
				answer %= MOD;
			}
			power *= 2;
			power %= MOD;
		}
		answer += result;
		answer %= MOD;
		if (len % 2 == 0) {
			(answer *= 2) %= MOD;
		} else {
			(answer *= 2) -= 1;
			answer %= MOD;
			(answer += MOD) %= MOD;
		}
		printf("%d\n", answer);
	}
	return 0;
} 
