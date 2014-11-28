#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

#define foreach(container, it) \
    for(typeof((container).begin()) it = (container).begin(); it!=(container).end(); ++it)

using namespace std;

typedef pair<int, int> PII;

const int N = 111111;
const int INF = (1 << 30);

vector<int> sons[N];

int n, q;
int nowVal[N], father[N];
int size[N], sub[N], rpos[N], pos[N], top[N], floor[N];
int light[N], heavy[N], curRoot;

priority_queue<PII, vector<PII>, greater<PII> > heap[N];

// segment Tree
int tv[N * 4];

void build(int x, int l, int r) {
	if (l == r) {
		tv[x] = light[rpos[l]];
		return ;
	}
	
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	tv[x] = min(tv[x << 1], tv[x << 1 | 1]);
}

void buildTree() {
	vector<int> q;
	q.push_back(1);
	for(int head = 0; head < (int)q.size(); head++) {
		int x = q[head];
		foreach(sons[x], it) {
			q.push_back(*it);
		}
	}
	
	fill(size + 1, size + n + 1, 0);
	for(int i = n - 1; i >= 0; i--) {
		int x = q[i];
		size[x]++;
		size[father[x]] += size[x];
		sub[x] = -1;
		foreach(sons[x], it) {
			if (sub[x] == -1 || size[*it] > size[sub[x]]) {
				sub[x] = *it;
			}
		}
		
		light[x] = nowVal[x];
		heap[x].push(make_pair(nowVal[x], 0));
		foreach(sons[x], it) {
			if (sub[x] != *it) {
				light[x] = min(light[x], heavy[*it]);
				heap[x].push(make_pair(heavy[*it], *it));
			}
		}
		
		heavy[x] = light[x];
		if (sub[x] != -1) {
			heavy[x] = min(heavy[x], heavy[sub[x]]);
		}
	}
	
	static int used[N], total = 0;
	fill(used + 1, used + n + 1, 0);
	for(int i = 0; i < n; i++) {
		int x = q[i];
		if (!used[x]) {
			int temp = x, last = x;
			while(temp != -1) {
				top[temp] = x;
				used[temp] = 1;
				last = temp;
				rpos[++total] = temp;
				pos[temp] = total;
				temp = sub[temp];
			}
			
			temp = x;
			while(temp != -1) {
				floor[temp] = last;
				temp = sub[temp];
			}
		}
	}
	
	build(1, 1, n);
}

void change(int x, int l, int r, int p) {
	if (l == r) {
		tv[x] = light[rpos[p]];
		return;
	}
	
	int mid = (l + r) >> 1;
	if (p <= mid) {
		change(x << 1, l, mid, p);
	} else {
		change(x << 1 | 1, mid + 1, r, p);
	}
	tv[x] = min(tv[x << 1], tv[x << 1 | 1]);
}

int ask(int x, int l, int r, int ql, int qr) {
	if (qr < l || ql > r)
		return INF;
	
	if (ql <= l && r <= qr) {
		return tv[x];
	}
	
	int mid = (l + r) >> 1;
	
	return min(ask(x << 1, l, mid, ql, qr), ask(x << 1 | 1, mid + 1, r, ql, qr));
}

int getVal(int x) {
	while(!heap[x].empty()) {
		PII temp = heap[x].top();
		if (temp.second == 0 && nowVal[x] != temp.first || 
			temp.second != 0 && heavy[temp.second] != temp.first) {
				heap[x].pop();
		} else {
			break;
		}
	}
	
	return heap[x].top().first;
}

void modify(int x, int v) {
	nowVal[x] = v;
	int s = x, source = x;
	
	while(x) {
		if (x == source) {
			heap[x].push(make_pair(nowVal[x], 0));
		} else {
			heap[x].push(make_pair(heavy[s], s));
		}
		
		light[x] = getVal(x);
		change(1, 1, n, pos[x]);
		
		x = top[x];
		heavy[x] = ask(1, 1, n, pos[x], pos[floor[x]]);
		s = x;
		x = father[x];
	}
}

int query(int x) {
	
	if (x == curRoot) {
		return ask(1, 1, n, pos[1], pos[floor[1]]);
	}
	
	bool flag = false;
	int t = curRoot;
	while(t && !flag) {
		if (pos[top[t]] <= pos[x] && pos[x] <= pos[floor[t]]) {
			flag = true;
		}
	}
	
	if (!flag) {
		return ask(1, 1, n, pos[x], pos[floor[x]]);
	} else {
		int res = INF;
		while(x) {
			res = min(res, ask(1, 1, n, pos[top[x]], pos[x]));
			x = father[top[x]];
		}
		
		return res;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &father[i], &nowVal[i]);
		sons[father[i]].push_back(i);		
	}	
	
	buildTree();
	
	for(int i = 1; i <= q; i++) {
		char type[10];
		scanf("%s", type);
		if (*type == 'V') {
			int a, b;
			scanf("%d %d", &a, &b);
			modify(a, b);
		} else if (*type == 'E') {
			int r;
			scanf("%d", &r);
			curRoot = r;
		} else if (*type == 'Q') {
			int a;
			scanf("%d", &a);
			printf("%d\n", query(a));
		}
	}
	
	return 0;
} 
