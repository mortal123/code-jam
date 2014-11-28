#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int INF = 1e8;
const int N = 100000 + 5;

struct Node {
	int size, tag;
	Node *left, *right;
	inline Node(Node *_left, Node *_right) {
		left = _left;
		right = _right;
	}

	Node() {}
	
	inline Node* update() {
		size = left->size + 1 + right->size;
		if (size >= INF) {
			size = INF;
		}
		return this;
	}
	
	inline Node* merge(Node *a, Node *b);
};

Node pool[N * 100];
int used;
vector<pair<int, int> > e[N];
int n, m, q, deg[N], special[N];


Node *null, *root[N];

Node *newNode() {
	Node *res = &pool[used++];
	res->left = res->right = null;
	res->size = 1;
	res->tag = 0;
	return res;
}

bool random(int a, int b) {
	return rand() % (a + b) < a;
}

Node* merge(Node *a, Node *b) {
	if (a == null) {
		return b;
	} else if (b == null) {
		return a;
	}
	if (a->size == INF) {
		return a;
	}
	Node *temp = newNode();
	Node *t2 = newNode();;
	if (random(a->size, b->size)) {
		*temp = *a;
		*t2 = *b;
		t2->tag -= temp->tag;
		temp->right = merge(temp->right, t2);
	} else {
		*temp = *b;
		*t2 = *a;
		t2->tag -= temp->tag;
		temp->left = merge(t2, temp->left);
	}
	return temp->update();
}

void prepare() {
	used = 0;
	null = new Node;
	null->left = null->right = null;
	null->tag = null->size = 0;
}

int search(Node *root, int k) {
	int total = 0;
	while(1) {
		total += root->tag;
		if (k <= root->left->size) {
			root = root->left;
		} else if (k == root->left->size + 1) {
			break;
		} else {
			k -= root->left->size + 1;
			root = root->right;
		}
	}
	return total;
}

void solve() {
	scanf("%d %d %d", &n, &m, &q);
	fill(special + 1, special + n + 1, 0);
	fill(deg + 1, deg + n + 1, 0);
	fill(root + 1, root + n + 1, null);
	for(int i = 1; i <= n; i++) {
		e[i].clear();
	}
	for(int i = 2; i <= n; i++) {
		scanf("%d", &special[i]);
	}

	for(int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		e[a].push_back(make_pair(c, b));
		deg[b]++;
	}

	static vector<int> queue;
	queue.clear();
	for(int i = 1; i <= n; i++) {
		if (deg[i] == 0) {
			queue.push_back(i);
		}
	}

	for(int head = 0; head < (int)queue.size(); head++) {
		int x = queue[head];
		for(int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i].second;
			if ((--deg[y]) == 0) {
				queue.push_back(y);
			}
		}
	}

	/*for(int i = 0; i < n; i++) {
		cout << queue[i] << " ";
	}
	cout << endl;
	return ;
	*/

	for(int i = n - 1; i >= 0; i--) {
		int x = queue[i];
		sort(e[x].begin(), e[x].end());
		for(int it = 0; it < (int)e[x].size(); it++) {
			int y = e[x][it].second;
			root[x] = merge(root[x], root[y]);
		}
		if (root[x] != null) {
			Node *temp = newNode();
			*temp = *root[x];
			temp->tag++;
			root[x] = temp;
		}
		if (special[x]) {
			root[x] = merge(newNode(), root[x]);
		}
	}

	for(int i = 0; i < q; i++) {
		int k;
		scanf("%d", &k);
		if (k > root[1]->size) {
			puts("-1");
		} else {
			printf("%d\n", search(root[1], k));
		}
	}
}

int main() {
	int test;
	scanf("%d", &test);
	while(test--) {
		static int testCount = 0;
		printf("Case #%d:\n", ++testCount);
		prepare();
		solve();
	}
}
