#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1111;

long long array[N];
long long pa, pb, pc, mod;
int n;
char oper[N];
long long a, b; // a * x + b;


long long multi(long long a, long long b) {
	if (b == 0)
		return 0;
	
	if (b == 1)
		return a;
	
	if (b % 2 == 0) {
		return 2 * multi(a, b / 2) % pc;
	} else {
		return (2 * multi(a, b / 2) % pc + a) % pc;
	}
}

int main() {
	
	freopen("input.txt", "r", stdin);
	
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &array[i]);
		}		
		
		scanf("%lld %lld %lld", &pa, &pb, &pc);
		
		scanf("%s", oper + 1);
		
		int left = 1, right = n, now = 1;
		
		a = 1, b = 0;
		
		for(int i = 1; i <= n; i++) {
			if (oper[i] == 'R') {
				if (now == left)
					now = right;
				else
					now = left;
				
				printf("%lld ", (multi(array[now], a) + b) % pc);
			} else if (oper[i] == 'A') {
				(b += pa) %= pc;
				printf("%lld ", (multi(array[now], a) + b) % pc);
			} else {
				a = multi(a, pb);
				b = multi(b, pb);
				printf("%lld ", (multi(array[now], a) + b) % pc);
			}
			
			if (now == left) {
				now++;
				left++;
			} else {
				now--;
				right--;
			}
			
		}
		printf("\n");
	}
	return 0;
}
