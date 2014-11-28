#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int N = 222222;
const int LIMIT = 1000;

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

void dfsDel(int x) {
	if (del[x])
		return ;
	del[x] = 1;
	for(int i = 0; i < (int)e[x].size(); i++) {
		int y = e[x][i];
		if (y == father[x])
			continue;
		dfsDel(y);
	}
}

int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	printf("%d\n", n = 1000);
	for(int i = 0; i < n; i++) {
		printf("%d ", sv[i] = rand() % LIMIT - LIMIT / 2);
	}	
	printf("\n");
	for(int i = 1; i < n; i++) {
		int a, b;
		a = i, b = rand() % i;
		e[a].push_back(b);
		e[b].push_back(a);
		printf("%d %d\n", a, b);
	}
	father[0] = -1;
	dfs(0);
	printf("%d\n", m = 1000);
	int special = 0;
	for(int i = 1; i <= m; i++) {
		loop:
		int type = rand() % 4 + 1;
		if (type == 3) {
			if (rand() % 4 != 1) {
				goto loop;
			}
		}
		printf("%d\n", type);
		if (type == 1) {
			loop1:
			long long key = rand() % n, value = rand() % LIMIT - LIMIT / 2;
			if (del[key])
				goto loop1;
			printf("%I64d %I64d\n", key - special, value);
			e[key].push_back(n++);
			sv[n - 1] = value;
		} else if (type == 2) {
			loop2:
			long long key = rand() % n, value = rand() % LIMIT - LIMIT / 2;
			if (del[key])
				goto loop2;
			printf("%I64d %I64d\n", key - special, value);
			dfs(key, value);
		} else if (type == 3) {
			loop3:
			long long key = rand() % n;
			if (del[key] || key == 0)
				goto loop3;
			printf("%I64d\n", key - special);
			dfsDel(key);
		} else if (type == 4) {
			loop4:
			long long key = rand() % n;
			if (del[key])
				goto loop4;
			printf("%I64d\n", key - special);
			special += ask(key);
		}
	}
	return 0;
}
