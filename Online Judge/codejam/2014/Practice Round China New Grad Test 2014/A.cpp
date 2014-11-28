#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int N = 222;

map<string, int> Map;
int n, visit[N];
string name[N], a, b; 
vector<int> e[N];

int getID(string a) {
	if (Map.count(a))
		return Map[a];
	int res = Map.size();
	return Map[a] = res;
}

int dfs(int x, int color) {
	if (visit[x] != 0) {
		if (color != visit[x])
			return 0;
		return 1;
	}
	visit[x] = color;
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!dfs(y, color * -1))
			return 0;
	}
	return 1;
}

int run(int test) {
	Map.clear();
	scanf("%d", &n);
	for(int i = 0; i < 210; i++)
		e[i].clear();
	for(int i = 1; i <= n; i++) {
		cin >> a >> b;
		int ida = getID(a), idb = getID(b);
		e[ida].push_back(idb);
		e[idb].push_back(ida);
	}
	for(int i = 0; i < Map.size(); i++) {
		visit[i] = 0;
	}
	for(int i = 0; i < Map.size(); i++)
		if (visit[i] == 0)
			if (!dfs(i, 1))
				return 0;
	return 1;
}

int main() {
	freopen("A-small-2-attempt0.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int Test;
	scanf("%d", &Test);
	for(int test = 1; test <= Test; test++) {
		if (!run(test))
			printf("Case #%d: No\n", test);
		else
			printf("Case #%d: Yes\n", test);
	}
	return 0;
} 
