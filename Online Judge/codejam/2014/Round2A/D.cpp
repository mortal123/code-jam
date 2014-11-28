#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int m, n;
char buf[1111][111];
int assign[1111];
int ans = 0;

struct Node {
	Node *child[26];
	void clear() {
		for(int i = 0; i < 26; i++) {
			child[i] = NULL;
		}
	}
}mem[1111111];

Node *root[11111];

int used = 0;
int ansV, ansW, cnt[111111];

Node *newNode() {
	mem[++used].clear();
	return &mem[used];
}

int insert(Node *r, char* buf) {
	int res = 0;
	for(int i = 0; buf[i]; i++) {
		int idx = buf[i] - 'A';
		if (r->child[idx] == NULL) {
			Node *tmp = newNode();
			r->child[idx] = tmp;
			res++;
		}
		r = r->child[idx];
	}
	return res;
}

void dfs(int x) {
	if (x == m + 1) {
		used = 0;
		int cur = 0;
		for(int i = 1; i <= n; i++) {
			root[i] = newNode();
			if (cnt[i])
				cur++;
		}
		for(int i = 1; i <= m; i++) {
			cur += insert(root[assign[i]], buf[i]);
		}
		if (cur > ansV) {
			ansV = cur;
			ansW = 1;
		} else if (cur == ansV) {
			ansW++;
		}
		return ;	
	} 
	for(int i = 1; i <= n; i++) {
		assign[x] = i;
		cnt[i]++;
		dfs(x + 1);
		cnt[i]--;
	}
}

int main() {
	freopen("D-small-attempt0.in", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		printf("Case #%d: ", ++testCount);
		scanf("%d %d", &m, &n);
		ansV = -1;
		ansW = 0;
		for(int i = 1; i <= m; i++) {
			scanf("%s", buf[i]);
		}
		dfs(1);
		printf("%d %d\n", ansV, ansW);
	}
	return 0;
}
 
