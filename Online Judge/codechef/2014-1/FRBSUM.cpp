#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 111111;

struct Node {
	int sum, l, r;
	Node* left, *right;
	
	Node() {
	}
	
	Node(int l, int r, int sum) : l(l), r(r), sum(sum) {
	}
	
};

Node* null, *root[N];

int n, m, val[N];
vector<pair<int, int> > pairs;

Node* build(int l, int r) {
	Node* root = new Node(l, r, 0);
	if (l == r)
		return root;
	root->left = build(l, (l + r) / 2);
	root->right = build((l + r) / 2 + 1, r);
	return root;
}

Node* insert(Node* root, int pos, int val) {
	Node* tmp = new Node;
	*tmp = *root;
	tmp->sum += val;
	
	if (tmp->l == tmp->r)
		return tmp;
	
	int mid = (tmp->l + tmp->r) / 2;
	
	if (pos <= mid) {
		tmp->left = insert(tmp->left, pos, val);
	} else {
		tmp->right = insert(tmp->right, pos, val);
	}
	
	return tmp;
}

int ask(Node* root, int l, int r) {
	if (l > root->r || r < root->l)
		return 0;
	
	if (l <= root->l && root->r <= r)
		return root->sum;
	
	return ask(root->left, l, r) + ask(root->right, l, r);
}

int main() {
	freopen("input.txt", "r", stdin);
	
	null = new Node(NULL, NULL, 0);
	null->left = null->right = null;
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		pairs.push_back(make_pair(a, i));		
	}
	
	sort(pairs.begin(), pairs.end());
	
	root[0] = build(1, n);
	val[0] = 0;
	
	for(int i = 0; i < (int)pairs.size(); i++) {
		if (i == 0 || pairs[i].first != pairs[i - 1].first) {
			root[m + 1] = insert(root[m], pairs[i].second, pairs[i].first);
			++m;
			val[m] = pairs[i].first;
			
		} else {
			root[m] = insert(root[m], pairs[i].second, pairs[i].first);
		}
	}
	
	int q;
	scanf("%d", &q);
	while(q--) {
		int ans = 1, nxt, lc, rc;
		scanf("%d %d", &lc, &rc);
		
		while(1) {
			int l = 0, r = m, mid;
			while(l < r) {
				mid = (l + r + 1) / 2;
				if (val[mid] <= ans) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			
			nxt = ask(root[l], lc, rc) + 1;
			
			if (nxt == ans)
				break;
			else 
				ans = nxt;
		}
		
		printf("%d\n", ans);
	}
}
