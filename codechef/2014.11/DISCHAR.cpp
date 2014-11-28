#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

const int N = 111111;

char str[N];
set<char> s;

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		scanf("%s", str);
		s.clear();
		for(int i = 0; str[i]; i++) {
			s.insert(str[i]);
		}
		cout << s.size() << endl;
	}
	return 0;
}