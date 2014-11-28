#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1111111;

char buf[N], str[N];
int ans = 0, m;

int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for(int i = 0; i < n; i++)
		if (buf[i] == '1' && buf[(i + 1) % n] == '0') {
			for(int j = 0; j < n; j++)
				str[(i + j + 1) % n] = buf[j];
			break;
		}
	int tmp;
	for(int i = 0; i < n; i++) {
			
	}
	return 0;
}
