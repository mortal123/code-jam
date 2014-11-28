#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 222222;
const int INF = 1000000000;

struct Node {
	int a, b, c;
}ver[N], hor[N];
int n, m;

struct Event {
	int type, level, spe;
	Event(int type, int level, int spe) : type(type), level(level), spe(spe) {}
};

int cmp(const Event &a, const Event &b) {
	if (a.level != b.level)
		return a.level < b.level;
	return a.type < b.type;
}

vector<int> vecs;
vector<Event> events;
int h[N], limit;

int ins(int pos, int v) {
	for(int i = pos; i <= limit; i += (i & (-i))) {
		h[i] += v;
	}
}

int ask(int pos) {
	int res = 0;
	for(int i = pos; i; i -= (i & (-i)))
		res += h[i];
	return res;
}

bool solve(int length) {
	vecs.clear();
	vecs.push_back(-INF);
	events.clear();
	for(int i = 1; i <= n; i++) {
		if (ver[i].c < 2 * length)
			continue;
		vecs.push_back(ver[i].a);
		events.push_back(Event(-1, ver[i].b + length, ver[i].a));
		events.push_back(Event(1, ver[i].b + ver[i].c - length, ver[i].a));
	}
	
	for(int i = 1; i <= m; i++) {
		if (hor[i].c >= 2 * length) {
			events.push_back(Event(0, hor[i].b, i));
			vecs.push_back(hor[i].a + length - 1);
			vecs.push_back(hor[i].a + hor[i].c - length);
		}
	}
	
	sort(vecs.begin(), vecs.end());
	vecs.erase(unique(vecs.begin(), vecs.end()), vecs.end());
	limit = vecs.size() - 1;
	for(int i = 1; i < vecs.size(); i++) {
		h[i] = 0;
	}
	
	sort(events.begin(), events.end(), cmp);
	for(int i = 0; i < (int)events.size(); i++) {
		if (events[i].type == -1) {
			ins(lower_bound(vecs.begin(), vecs.end(), events[i].spe) - vecs.begin(), 1);
		} else if (events[i].type == 1) {
			ins(lower_bound(vecs.begin(), vecs.end(), events[i].spe) - vecs.begin(), -1);
		} else {
			int id = events[i].spe;
			int l = hor[id].a + length, r = hor[id].a + hor[id].c - length;
			if (ask(lower_bound(vecs.begin(), vecs.end(), r) - vecs.begin()) - 
				ask(lower_bound(vecs.begin(), vecs.end(), l - 1) - vecs.begin()) > 0)
					return true;
		}
	}
	
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d %d", &n, &m);	
	for(int i = 1; i <= n; i++) {
		scanf("%d %d %d", &ver[i].a, &ver[i].b, &ver[i].c);
	}
	
	for(int i = 1; i <= m; i++) {
		scanf("%d %d %d", &hor[i].a, &hor[i].b, &hor[i].c);
	}
	
	int l = 0, r = 100000000, mid;
	while(l < r) {
		mid = (l + r + 1) / 2;
		if (solve(mid))
			l = mid;
		else
			r = mid - 1;
	}
	
	printf("%d\n", l);
	return 0;
} 
