#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <set>
#include <cassert>
#include <iostream>
using namespace std;

string t, s;
int next[110000];
int last[27], pos[200];

int modify(int start) {
	for(int i = 0; i < s.length(); i++) {
		while(pos[i] < t.length() && pos[i] < start)
			pos[i] = next[pos[i]];
		if (pos[i] >= t.length())
			return 0;
		start = pos[i] + 1;
	}
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> t;
	cin >> s;
	for(int i = 0; i < 26; i++) {
		last[i] = t.length();
	}
	for(int i = t.length() - 1; i >= 0; i--) {
		next[i] = last[t[i] - 'a'];
		last[t[i] - 'a'] = i;
	}
	for(int i = 0; i < s.length(); i++)
		pos[i] = last[s[i] - 'a'];
	long long ans = 0;
	for(int i = 0; i < t.length(); i++) {
		if (!modify(i))
			break;
		ans += t.length() - pos[s.length() - 1];
		//cerr << t.length() - pos[s.length() - 1] + 1 << endl;
	}
	printf("%I64d\n", ans);
	return 0;
}
