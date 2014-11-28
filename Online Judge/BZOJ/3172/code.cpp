#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 205;
const int MAXLEN = int(1e6) + 5;

struct node {
	node *next[26], *fail;
	int v;
	node() {
		v = 0;
		memset(next, NULL, sizeof(next));
	}
}*root, Mem[MAXLEN * 2];

int use = 0;

node *q[MAXLEN * 2], *pos[MAXN];
int n;
char buf[MAXLEN];
string str[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	
	root = new node();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		node *tmp = root;
		for (int j = 0; buf[j]; j++) {
			if (tmp->next[buf[j] - 'a'] == NULL) {
				tmp->next[buf[j] - 'a'] = &Mem[++use];
			}
			tmp = tmp->next[buf[j] - 'a'];
			tmp->v++;
		}
		pos[i] = tmp;
		str[i] = buf;
	}
	int head = 0, tail = 0;
	q[++tail] = root;
	root->fail = root;
	while(head < tail) {
		node *tmp = q[++head];
		for (int i = 0; i < 26; i++)
			if (tmp->next[i] != NULL) {
				if (tmp == root) {
					tmp->next[i]->fail = root;
				} else {
					node *t = tmp->fail;
					while (t != root && t->next[i] == NULL)
						t = t->fail;
					if (t->next[i] == NULL)
						tmp->next[i]->fail = t;
					else
						tmp->next[i]->fail = t->next[i];
				}
				q[++tail] = tmp->next[i];
			}
	}
	for (int i = tail; i >= 1; i--) {
		q[i]->fail->v += q[i]->v;
	}
	
	for (int i = 1; i <= n; i++) {
		printf("%d\n", pos[i]->v);
	}
	return 0;
} 
