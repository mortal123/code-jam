#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

string str[400];
string s;
vector<int> ss;

void dfs(int len, char up) {
	if (len > 24)
		return ;
	if (len > 0) {
		int cnt = s.length() * (s.length() + 1) / 2, maxlen = 0;
		for(int i = 0, j = 0; i < s.length(); i = j) {
			j = i + 1;
			if (s[i] == 'a') {
				while(j < s.length() && s[j] == 'a')
					j++;
				cnt -= (j - i) * (j - i + 1) / 2;
				maxlen = max(maxlen, j - i);
			}
		}
		cnt += maxlen;
		if (str[cnt] == "" || str[cnt].size() > s.size() || s.size() == str[cnt].size() && s < str[cnt])
			str[cnt] = s;
	}
	s += 'a';
	dfs(len + 1, up);
	s.erase(s.size() - 1);
	s += up;
	dfs(len + 1, up + 1);
	s.erase(s.size() - 1);
}

int main() {
	freopen("output.txt", "w", stdout);
	s = "";
	str[16] = "aaabba";
	dfs(0, 'b');
	for(int i = 1; i <= 300; i++) {
		cout << "\"" << str[i] << "\"" << "," << endl;
	}
	return 0;
}
