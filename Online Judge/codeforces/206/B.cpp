#include <cstdio>
#include <cstdlib> 
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <set>
using namespace std;

const int N = 22;
const int inf = 100000000;

int f[N][N];
int n;
char map[N][N];
set<string> ok[100];

inline int val(char x) {
	if (x == 'a')
		return 1;
	if (x == 'b')
		return -1;
	return 0;
}

int dfs(string now) {
	if ((int)now.size() == 2 * n - 1)
		return 0;
	int ret = 0;
	if ((int)now.size() % 2 == 0)
		ret = -inf;
	else
		ret = inf;
	for(char ch = 'a'; ch <= 'z'; ch++) {
		string tmp = now;
		tmp += ch;
		if (!ok[(int)now.size() + 1].count(tmp))
			continue;
		if ((int)now.size() % 2 == 0)
			ret = max(ret, val(ch) + dfs(tmp));
		else
			ret = min(ret, val(ch) + dfs(tmp));
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%s", map[i] + 1);
	for(int len = 1; len <= 2 * n - 1; len++) {
		for(int i = 0; i < 1 << (len - 1); i++) {
			string now;
			int x = 1, y = 1;
			for(int j = 0; j < (len - 1); j++) {
				now += map[x][y];
				if (i & (1 << j))
					x++;
				else
					y++;
				if (x > n || y > n)
					break;
			}
			if (x > n || y > n)
				continue;
			now += map[x][y];
			ok[len].insert(now);
		}
	}
	int result = dfs("");
	if (result > 0)
		printf("FIRST\n");
	else if (result == 0)
		printf("DRAW\n");
	else 
		printf("SECOND\n");
	return 0;
}
