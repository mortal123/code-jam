#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

string s;

int main() {
	ios::sync_with_stdio(false);
	int d;
	cin >> d;
	getline(cin, s);
	while(d--) {
		getline(cin, s);
	}
	getline(cin, s);
	cout << s << endl;
	return 0;
}