#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

string s, buf;
int num[2];

int main() {
	freopen("input.txt", "r", stdin);
	cin >> buf;
	cin >> s;
	for(int i = 0, flag = 0; i < (int)buf.length(); i++) {
		if (buf[i] == '|')
			flag = 1;
		else {
			if (buf[i] < 'A' || buf[i] > 'Z')
				continue;
			if (flag == 0)
				num[0]++;
			else
				num[1]++;
		}
	}
	
	for(int i = 0; i < (int)s.length(); i++) {
		if (s[i] < 'A' || s[i] > 'Z')
			continue;
		if (num[0] > num[1])
			buf = buf + s[i], num[1]++;
		else
			buf = s[i] + buf, num[0]++;
	}
	
	if (num[0] == num[1])
		cout << buf << endl;
	else
		cout << "Impossible" << endl;
	return 0;
} 
