#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 5000000 + 10;

int total, len[N], to[N][2], suf[N];
char str[N], answer[N];
int n, last;

void clear(int pos) {
	to[pos][0] = to[pos][1] = -1;
}

int getSuf(int x, int s) {
	if (s == -1) {
		return 0;
	}
	while (str[x] != str[x - len[s] - 1]) {
		s = suf[s];
	}
	return s;
}

bool expand(int x) {
	int idx = str[x] - 'a';

	int first = getSuf(x, last);
	int second = getSuf(x, suf[first]);
	//cout << first << " " << second << endl;
	second = to[second][idx];
	if (to[first][idx] == -1) {
		clear(total);
		to[first][idx] = total;
		len[total] = len[first] + 2;
		suf[total] = (second == -1 ? 1 : second); 
		last = total++;
		return true;
	}
	last = to[first][idx];
	return false;
}

int main() {
	str[0] = '#';
	gets(str + 1);
	n = strlen(str + 1);
	total = 0;

	clear(total);
	suf[total] = -1;
	len[total++] = -1;

	clear(total);
	suf[total] = 0;
	len[total++] = 0;
	
	last = total - 1;

	for(int i = 1; i <= n; i++) {
		answer[i] = expand(i) ? '1' : '0';
	}
	answer[n + 1] = 0;
	puts(answer + 1);
	return 0;
}
