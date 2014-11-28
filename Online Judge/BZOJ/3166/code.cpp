#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 60000, base = 30;

struct node {
	int size;
	node *child[2];
	node (int size = 0, node *left = NULL, node *right = NULL) : size(size) {
		child[0] = left;
		child[1] = right;
	}
};

node *root[MAXN];

int a[MAXN], n, h[MAXN] = {0};
vector<pair<int, int> > vec;

inline int lowbit(int x) {
	return (x & (-x));
}

inline int ask(int pos) {
	int res = 0;
	for (int i = pos; i; i -= lowbit(i)) 
		res += h[i];
	return res;
}

inline void ins(int pos) {
	for(int i = pos; i <= n; i += lowbit(i))
		h[i]++;
}

node* mergy(node* a, int val, int dep) {
	if (dep < 0) {
		return new node(1, NULL, NULL);
	}
	node* tmp = new node(0, NULL, NULL);
	if (a)
		*tmp = *a;
	tmp->size++;
	if (val & (1 << dep)) {
		tmp->child[1] = mergy(tmp->child[1], val, dep - 1);
	} else {
		tmp->child[0] = mergy(tmp->child[0], val, dep - 1);
	}
	return tmp;
}

int Ask(node* L, node* R, int v, int dep) {
	if (dep < 0)
		return 0;
	int size[2] = {0};
	for(int i = 0; i < 2; i++) {
		if (R->child[i])
			size[i] += R->child[i]->size;
		if (L && L->child[i])
			size[i] -= L->child[i]->size;
	}
	//printf("dep = %d :: %d %d\n", dep, size[0], size[1], R->child[0]->size);
	if (v & (1 << dep)) {
		if (size[0]) {
			return Ask(L ? L->child[0] : L, R->child[0], v, dep - 1);
		} else {
			return (1 << dep) + Ask(L ? L->child[1] : L, R->child[1], v, dep - 1);	
		}
	} else {
		if (size[1]) {
			return (1 << dep) + Ask(L ? L->child[1] : L, R->child[1], v, dep - 1);
		} else {
			return Ask(L ? L->child[0] : L, R->child[0], v, dep - 1);
		}
	}
}

int Sec(int L, int R) {
	return ask(R) - ask(L - 1);
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	root[0] = NULL;
	int ans = 0;
	for(int i = 1; i <= n; i++)
		h[i] = 0;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		root[i] = mergy(root[i - 1], a[i], base);
		vec.push_back(make_pair(a[i], i));
	}
	sort(vec.begin(), vec.end());
	for(int i = vec.size() - 1; i >= 0; i--) {
		for (int j = i; j >= 0 && vec[j].first == vec[i].first; j--) {
			int L, R, l, r, mid, pos = vec[j].second, val = vec[j].first;
			l = 1, r = pos;
			while (l < r) {
				mid = (l + r) / 2;
				if (Sec(mid, pos) < 2)
					r = mid;
				else
					l = mid + 1;
			}
			L = l;
			l = pos, r = n;
			while(l < r) {
				mid = (l + r) / 2 + 1;
				if (Sec(pos, mid) < 2)
					l = mid;
				else
					r = mid - 1;
			}
			R = l;
			ans = max(ans, a[pos] ^ Ask(root[L - 1], root[R], a[pos], base));
			//printf("\n%d %d %d %d ------------\n", pos, L, R, Ask(root[L - 1], root[R], a[pos], base));
		}
		int temp = vec[i].first;
		for (; i >= 0 && vec[i].first == temp; i--) {
			ins(vec[i].second);
		}
		i++;
	}
	printf("%d\n", ans);
	return 0;
}
