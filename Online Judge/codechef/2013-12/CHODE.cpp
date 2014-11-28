#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 111111;

pair<int, int> w[30];
char key[N], buf[N];

int main() {
	int test;
	scanf("%d", &test);
	gets(key);
	while(test--) {
		gets(key);
		gets(buf);
		int n = strlen(buf);
		for(int i = 0; i < 26; i++) {
			w[i].first = 0;
			w[i].second = i;
		}
		
		for(int i = 0; i < n; i++) {
			if (buf[i] >= 'a' && buf[i] <= 'z')
				w[buf[i] - 'a'].first++;
			if (buf[i] >= 'A' && buf[i] <= 'Z')
				w[buf[i] - 'A'].first++;
		}
		sort(w, w + 26);
		for(int i = 0; i < n; i++) {
			bool upperCase = false;
			if (buf[i] >= 'A' && buf[i] <= 'Z') {
				upperCase = true;
				buf[i] = buf[i] - 'A' + 'a';
			}
			
			if (buf[i] < 'a' || buf[i] > 'z')
				continue;
			
			for(int j = 0; j < 26; j++)
				if (buf[i] == w[j].second + 'a') {
					buf[i] = key[j];
					if (upperCase)
						buf[i] = buf[i] - 'a' + 'A';
					break;
				}
		}
		puts(buf);
	}
	return 0;
}
