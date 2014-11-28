#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;


const int N = 111111;

struct Node {
	Node *child[2];
};

Node *null, *root;
Node mem[N * 35];
int used, n, m;

void insert(Node *root, long long number, int dep) {
	if (dep == -1) {
		return ;
	}
	int dir = (number >> dep & 1);
	if (root->child[dir] == null) {
		root->child[dir] = &mem[used++];
		root->child[dir]->child[0] = root->child[dir]->child[1] = null;
	}
	insert(root->child[dir], number, dep - 1);
}

long long dfs(Node *root, long long number, int dep) {
	if (dep == -1)
		return 0;
	long long dir = (number >> dep & 1);
	dir ^= 1;
	if (root->child[dir] != null) {
		return dfs(root->child[dir], number, dep - 1) | (dir << dep);
	} else {
		return dfs(root->child[dir ^ 1], number, dep - 1) | ((dir ^ 1) << dep);
	}
}

int main() {
	null = new Node;
	null->child[0] = null->child[1] = null;
	
	int test;
	scanf("%d", &test);
	while(test--) {
		static int caseNumber = 0;
		printf("Case #%d:\n", ++caseNumber);
		scanf("%d %d", &n, &m);
		root = new Node;
		root->child[0] = root->child[1] = null;
		used = 0;
		for(int i = 1; i <= n; i++) {
			long long a;
			scanf("%I64d", &a);
			insert(root, a, 32);
		}
		for(int i = 1; i <= m; i++) {
			long long a;
			scanf("%I64d", &a);
			printf("%I64d\n", dfs(root, a, 32));
		}
	}
	return 0;
} 
