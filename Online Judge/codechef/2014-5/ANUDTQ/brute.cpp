#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 222222;

vector<int> e[N];
int n, m;
long long sv[N];
int del[N], father[N];

void dfs(int x) {
	if (del[x])
		return ;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father[x])
			continue;
		father[y] = x;
		dfs(y);
	}
}

void dfs(int x, long long v) {
	if (del[x])
		return ;
	sv[x] += v;	
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father[x])
			continue;
		dfs(y, v);
	}
}

long long ask(int x) {
	if (del[x])
		return 0;
	long long res = sv[x];
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father[x])
			continue;
		res += ask(y);
	}
	return res;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%I64d", &sv[i]);
	}	
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	father[0] = -1;
	dfs(0);
	scanf("%d", &m);
	long long special = 0;
	for(int i = 1; i <= m; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			long long key, value;
			scanf("%I64d %I64d", &key, &value);
			key += special;
			e[key].push_back(n++);
			sv[n - 1] = value;
		} else if (type == 2) {
			long long key, value;
			scanf("%I64d %I64d", &key, &value);
			key += special;
			dfs(key, value);
		} else if (type == 3) {
			long long key;
			scanf("%I64d", &key);
			key += special;
			del[key] = 1;
		} else if (type == 4) {
			long long key;
			scanf("%I64d", &key);
			key += special;
			printf("%I64d\n", ask(key));
			special += ask(key);
		}
	}
	return 0;
}
