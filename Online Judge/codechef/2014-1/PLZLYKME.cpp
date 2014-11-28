#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int N = 1111;

int main() {
	int test;
	cin >> test;
	while(test--) {
		long long l, d, s, c;
		cin >> l >> d >> s >> c;
		d--;
		while(d--) {
			if (s >= l)
				break;
			s = s + s * c;
		}
		if (s >= l) {
			puts("ALIVE AND KICKING");
		} else {
			puts("DEAD AND ROTTING");
		}
	} 
	return 0;
}
