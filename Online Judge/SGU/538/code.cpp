#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	bool left = false, latin = false, spaces = false, marks = false;
	int ans = 0;
	char ch;
	while(scanf("%c", &ch) == 1) {
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
			latin = true;
		else if (ch == ' ') 
			spaces = true;
		else if (ch == '(') {
			if (left) 
				ans++;
			left = true;
		} else if (ch == ')') {
			if (left && marks == false) {
				left = false;
			} else {
				ans++;
				ans += left;
				left = false;
			}
		} else {
			marks = true;
		}
		
		if (ch == ')' || ch == '(')
			marks = spaces = latin = false;
	}
	if (left)
		ans++;
	printf("%d\n", ans);
	return 0;
} 
