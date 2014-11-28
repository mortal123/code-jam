#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 2600;
const int inf = 1000000000;

char s[MAXN], str[MAXN];
vector<int> pos;
int f[MAXN][MAXN];

int isUppercase(char a) {
	return a >= 'A' && a <= 'Z';
}

int isLowercase(char a) {
	return a >= 'a' && a <= 'z';
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%s", str);
	int n = 0, flag = 0;
	for(int i = 0; str[i]; i++) {
		s[++n] = str[i];
		if (n > 1 && isUppercase(s[n]) && isLowercase(s[n - 1]) && s[n - 1] - 'a' == s[n] - 'A') 
			n -= 2, flag++;
	}
	s[n + 1] = 0;
//	printf("%s", s + 1);
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			f[i][j] = inf;
	for(int i = 1; i < n; i++)
		if (isLowercase(s[i]) && isUppercase(s[i + 1])) {
			printf("-1\n");
			return 0;
		}
	for(int i = 1; i <= n; i++)
		if (isUppercase(s[i]) && i < n && isLowercase(s[i + 1]) || s[i] == '*')
			pos.push_back(i);
	for(int len = 1; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			if (s[i] == '*') {
				f[i][j] = min(f[i][j], f[i + 1][j]);
				if (isUppercase(s[j]))
					f[i][j] = min(f[i][j], f[i][j - 1] + 1);
			}
			if (s[j] == '*') {
				f[i][j] = min(f[i][j], f[i][j - 1]);
				if (isLowercase(s[i]))
					f[i][j] = min(f[i][j], f[i + 1][j] + 1);
			}
			if (isLowercase(s[i]) && isUppercase(s[j]) && s[i] - 'a' == s[j] - 'A')
				f[i][j] = min(f[i][j], f[i + 1][j - 1] + 1);
			for(int k = 0; k < pos.size(); k++)
				if (pos[k] >= i && pos[k] <= j) {
					if (s[pos[k]] == '*' && pos[k] > i && pos[k] < j)
						f[i][j] = min(f[i][j], f[i][pos[k]] + f[pos[k]][j]);
					if (pos[k] < j)
						f[i][j] = min(f[i][j], f[i][pos[k]] + f[pos[k] + 1][j]);
				}
		}
	/*
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			printf("(%d, %d) = %d\n", i, j, f[i][j]);
	*/
	if (f[1][n] >= inf / 2)
		printf("-1\n");
	else
		printf("%d\n", f[1][n] + flag);
	return 0;
}
