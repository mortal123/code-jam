#include <cstdio>
#include <cstdlib> 
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;

const int N = 22;
const int inf = 100000000;

int n;
char Map[N][N];
vector<int> vecs[100];
map<pair<int, vector<int> >, int> f;

inline int val(char x) {
	if (x == 'a')
		return 1;
	if (x == 'b')
		return -1;
	return 0;
}

int dfs(int len) {
	if (len == 2 * n)
		return 0;
	if (f.find(make_pair(len, vecs[len])) != f.end())
		return f[make_pair(len, vecs[len])];
	int ret = 0;
	if (len % 2 == 1)
		ret = -inf;
	else
		ret = inf;
		
	for(char ch = 'a'; ch <= 'z'; ch++) {
		vecs[len + 1].clear();
		for(int i = 0; i < vecs[len].size(); i++) {
			int x = vecs[len][i], y = len - x;
			if (x < n && Map[x + 1][y] == ch)
				vecs[len + 1].push_back(x + 1);
			if (y < n && Map[x][y + 1] == ch)
				vecs[len + 1].push_back(x);
		}
		if ((int)vecs[len + 1].size() == 0)
			continue;
		sort(vecs[len + 1].begin(), vecs[len + 1].end());
		vecs[len + 1].erase(unique(vecs[len + 1].begin(), vecs[len + 1].end()), vecs[len + 1].end());
		if (len % 2 == 1)
			ret = max(ret, val(ch) + dfs(len + 1));
		else
			ret = min(ret, val(ch) + dfs(len + 1));
	}
	return f[make_pair(len, vecs[len])] = ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%s", Map[i] + 1);
	f.clear();
	vecs[2].push_back(1);
	int result = dfs(2);
	result += val(Map[1][1]);
	if (result > 0)
		printf("FIRST\n");
	else if (result == 0)
		printf("DRAW\n");
	else 
		printf("SECOND\n");
	return 0;
}
