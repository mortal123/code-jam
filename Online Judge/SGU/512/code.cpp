#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int MAXN = 100005;

vector<int> ls;

struct Node {
	int x, y;
	Node(int x, int y) : x(x), y(y) {}
	Node() {}
	friend int operator <(const Node &a, const Node &b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
}p[MAXN], a[MAXN], b[MAXN];

int cmp(const int &i, const int &j) {
	return a[i].y == a[j].y ? a[i].x < a[j].x : a[i].y < a[j].y;
}

int n;
long long ans = 0;

void discrete(Node a[], int n) {
	ls.clear();
	for(int i = 1; i <= n; i++) {
		ls.push_back(a[i].x);
	}
	sort(ls.begin(), ls.end());
	ls.erase(unique(ls.begin(), ls.end()), ls.end());
	for(int i = 1; i <= n; i++) {
		a[i].x = lower_bound(ls.begin(), ls.end(), a[i].x) - ls.begin() + 1;
	}
	
	ls.clear();
	for(int i = 1; i <= n; i++) {
		ls.push_back(a[i].y);
	}
	sort(ls.begin(), ls.end());
	ls.erase(unique(ls.begin(), ls.end()), ls.end());
	for(int i = 1; i <= n; i++) {
		a[i].y = lower_bound(ls.begin(), ls.end(), a[i].y) - ls.begin() + 1;
	}
	
	sort(a + 1, a + n + 1);
}

set<int> s;
vector<pair<int, int> > pairs;
vector<int> lft;
int upRight[MAXN], downLeft[MAXN];
int h[MAXN];

inline int lowbit(const int &x) {
	return x & -x;
}

int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i -= lowbit(i)) {
		res += h[i];
	}
	return res;
}

int ins(int pos) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		h[i]++;
	}
}

void clear(int pos) {
	for(int i = pos; i <= n; i += lowbit(i)) {
		h[i] = 0;
	}
} 

void work(int l, int r) {
	if (l >= r) {
		return ;
	}
	int mid = (l + r) / 2, maxy = 0;
	for(int i = l; i <= r; i++)
		maxy = max(maxy, a[i].y);
	s.clear();
	for(int i = l; i <= mid; i++) 
		upRight[i] = maxy + 1;
	for(int i = mid; i >= l; i--) {
		set<int> :: iterator it = s.lower_bound(a[i].y);
		if (it != s.end())
			upRight[i] = *it;
		s.insert(a[i].y);
	}
	s.clear();
	for(int i = mid + 1; i <= r; i++)
		downLeft[i] = 0;
	for(int i = mid + 1; i <= r; i++) {
		set<int> :: iterator it = s.upper_bound(a[i].y);
		if (it != s.begin()) {
			--it;
			downLeft[i] = *it;
		}
		s.insert(a[i].y);
	}
	pairs.clear();
	for(int i = mid + 1; i <= r; i++)
		pairs.push_back(make_pair(downLeft[i], a[i].y));
	sort(pairs.begin(), pairs.end());
	lft.clear();
	for(int i = l; i <= mid; i++)
		lft.push_back(i);
	sort(lft.begin(), lft.end(), cmp);	
	for(int i = 0, j = 0; i < lft.size(); i++) {
		while(j < pairs.size() && pairs[j].first < a[lft[i]].y) {
			ins(pairs[j].second);
			j++;
		}
		ans += ask(upRight[lft[i]] - 1) - ask(a[lft[i]].y - 1);
	}
	for(int i = 0; i < pairs.size(); i++) {
		clear(pairs[i].second);
	}
	work(l, mid);
	work(mid + 1, r);
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);
	
	for(int i = 1; i <= n; i++)
		a[i] = p[i];
	discrete(a, n);
	work(1, n); 
	
	for(int i = 1; i <= n; i++)
		a[i] = Node(p[i].x, -p[i].y);
	discrete(a, n);
	work(1, n);
	
	map<int, int> Map;
	for(int i = 1; i <= n; i++)
		Map[p[i].x]++;
	for(map<int, int> :: iterator it = Map.begin(); it != Map.end(); it++) {
		ans -= it->second - 1;
	}
	Map.clear();
	for(int i = 1; i <= n; i++)
		Map[p[i].y]++;
	for(map<int, int> :: iterator it = Map.begin(); it != Map.end(); it++) {
		ans -= it->second - 1;
	}
	
	printf("%I64d\n", ans);
	return 0;
} 
