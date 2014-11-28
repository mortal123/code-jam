#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXLEN = 1100000;
const int LIST = 1, DICT = 2, DICTK = 3;

int ans, m, n;
char s[MAXLEN];

struct State {
	State(int type, int wish) : type(type), wish(wish) {}
	State() {}
	int type;
	long long wish;
};

int stack[MAXLEN];
int top = 0;
bool ok = false;

long long wish = 0;

int isNum(char x) {
	return x >= '0' && x <= '9';
}

int fail(int pos) {
	printf("Error at position %d!\n", pos - 1);
	exit(0);
}

void changeTop(int top) {
	if (top && stack[top] == DICT)
		wish += 2;
	if (top && stack[top] == DICTK)
		wish -= 2;
		
	if (top && stack[top] == DICT)
		stack[top] = DICTK;
	else if (top && stack[top] == DICTK)
		stack[top] = DICT;
}

int main() {
	freopen("input.txt", "r", stdin);
	ans = 0;
	scanf("%d", &m);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; ) {
		if (ok)
			fail(i);
		
		if (isNum(s[i])) { // string
			changeTop(top);
			long long integer = 0;
			bool flag = false;
					
			for(; isNum(s[i]); i++) {
				if (flag && integer == 0) // leading zero
					fail(i);
				integer = integer * 10 + s[i] - '0';
				flag = true;
				if (wish + i + 1 + integer > m) {
					fail(i);
				}
			}
			if (s[i] != ':' || wish + i + integer > m) {
				fail(i);
			}
			for(++i; integer && i <= n; i++, integer--);
			if (integer) {
				fail(i);
			}
				
		} else if (s[i] == 'i') {
			changeTop(top);
			if (i + 2 + wish > m) {
				fail(i);
			}
			
			bool flag = false;
			long long integer = 0;
			
			for(++i; isNum(s[i]); i++) {
				if (flag && integer == 0) // leading zero 
					fail(i);
				integer = integer * 10 + s[i] - '0';
				flag = true;
				if (wish + i + 1 > m) {
					fail(i);
				}
			}
			if (!flag || s[i] != 'e' || i + wish > m) {
				fail(i);
			}
			i++;
				
		} else if (s[i] == 'l') {
			changeTop(top);
			stack[++top] = LIST;
			if (i + 1 + wish > m) {
				fail(i);
			}
			i++;
			wish++;
		} else if (s[i] == 'd') {
			changeTop(top);
			stack[++top] = DICT;
			if (i + 1 + wish > m) {
				fail(i);
			}
			i++;
			wish++;
		} else if (s[i] == 'e') {
			if (!top)
				fail(i);
			if (top && stack[top] == DICTK)
				fail(i);
			top--;
			wish--;
			i++;
		} else {
			fail(i);
		}
		if (top == 0)
			ok = true;
	}
	if (top)
		fail(n + 1);
	printf("ok\n");
	return 0;
} 
