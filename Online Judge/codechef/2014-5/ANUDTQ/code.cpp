#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

struct Node;

typedef pair <Node*, Node*> Pair;

const int N = (111111 << 1), MEM = (N << 2);
const int DIGIT = ((1 << 15) - 1);

int n, m, father[N];
vector<int> e[N];
long long sv[N];
Node *root, *null, *pos[N][2];
int used = 0;

struct Node {
	int size, type, vsize;
	long long tag, val, sum;
	Node *left, *right, *father;
	
	Node* update() {
		size = left->size + 1 + right->size;
		vsize = left->vsize + (type > 0) + right->vsize;
		sum = left->sum + right->sum + val;
		return this;
	}
	
	void down() {
		if (tag) {
			if (left != null) {
				left->val += (left->type > 0) * tag;
				left->sum += 1LL * left->vsize * tag;
				left->tag += tag;
			}
			if (right != null) {
				right->val += (right->type > 0) * tag;
				right->sum += 1LL * right->vsize * tag;
				right->tag += tag;
			}
			tag = 0;
		}
	}
	Pair split(int);
};

Node memory[MEM];

bool random(int a, int b) {
	return (((rand() & DIGIT) << 15) | rand()) % (a + b) < a;
}

int queryRank(Node *x) {
	int res = x->left->size + 1;
	while(x != root) {
		if (x->father->left == x) {
			x = x->father;
		} else if (x->father->right == x) {
			x = x->father;
			res += x->left->size + 1;
		} else {
			while(1);
		}
	}
	return res;
}

Node *newNode(long long v, int type, Node *para = null) {
	Node *res = &memory[used++];
	res->left = res->right = res->father = para;
	res->tag = 0;
	res->val = res->sum = (type > 0) * v;
	res->type = type;
	res->size = 1;
	res->vsize = (type > 0);
	return res;
}

Pair Node::split(int num) {
    if (this == null) {
        return make_pair(null, null);
    } 
    this->down();
    if (left->size >= num) {
    	Pair ret = left->split(num);
    	left = ret.second;
    	ret.second->father = this;
    	ret.first->father = null;
    	return make_pair(ret.first, this->update());
    } else {
    	Pair ret = right->split(num - left->size - 1);
    	right = ret.first;
    	ret.first->father = this;
    	ret.second->father = null;
    	return make_pair(this->update(), ret.second);
    }
}

Node *mergy(Node *a, Node *b) {
	if (a == null) {
		return b;
	}
	if (b == null) {
		return a;
	}
	if (random(a->size, b->size)) {
		a->down();
		a->right = mergy(a->right, b);
		a->right->father = a;
		return a->update();
	} else {
		b->down();
		b->left = mergy(a, b->left);
		b->left->father = b;
		return b->update();
	}
}

void buildTree() {
	null = newNode(0, 0, NULL);
	null->size = 0;
	null->left = null->right = null->father = null;
	vector<int> q, qe;
	q.push_back(1);
	qe.push_back(0);
	root = pos[1][0] = newNode(sv[1], 1);
	father[1] = 0;
	while(!q.empty()) {
		int x = q.back();
		if (qe.back() == (int)e[x].size()) {
			root = mergy(root, pos[x][1] = newNode(0, -x));	
			q.pop_back();
			qe.pop_back();
			continue;
		}
		int y = e[x][qe.back()++];
		if (y == father[x])
			continue;
		father[y] = x;
		root = mergy(root, pos[y][0] = newNode(sv[y], y));
		q.push_back(y);
		qe.push_back(0);
	}
}

void getTriBlock(long long x, Node *&a, Node *&b, Node *&c) {
	int lpos = queryRank(pos[x][0]);
	int rpos = queryRank(pos[x][1]);
	Pair ret = root->split(lpos - 1);
	Pair ret2 = ret.second->split(rpos - lpos + 1);
	a = ret.first; 
	b = ret2.first;
	c = ret2.second;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
	srand(time(0));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &sv[i]);
	}	
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a++; b++;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	buildTree();
	scanf("%d", &m);
	long long special = 0;
	for(int i = 1; i <= m; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			long long key, value;
			scanf("%lld %lld", &key, &value);
			key = key + 1 + special;
			int lpos = queryRank(pos[key][0]);
			Pair ret = root->split(lpos);
			++n;
			root = mergy(ret.first, pos[n][0] = newNode(value, n));
			root = mergy(root, pos[n][1] = newNode(0, -n));
			root = mergy(root, ret.second);
		} else if (type == 2) {
			long long key, value;
			scanf("%lld %lld", &key, &value);
			key = key + 1 + special;
			Node *a, *b, *c;
			getTriBlock(key, a, b, c);
			b->tag += value;
			b->val += (b->type > 0) * value;
			b->sum += 1LL * b->vsize * value;
			root = mergy(mergy(a, b), c);
		} else if (type == 3) {
			long long key;
			scanf("%lld", &key);
			key = key + 1 + special;
			Node *a, *b, *c;
			getTriBlock(key, a, b, c);
			root = mergy(a, c);
		} else if (type == 4) {
			long long key;
			scanf("%lld", &key);
			key = key + 1 + special;
			Node *a, *b, *c;
			getTriBlock(key, a, b, c);
			printf("%lld\n", b->sum);
			special = b->sum;
			root = mergy(mergy(a, b), c);
		}
	}
	return 0;
}
