#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct Node;

typedef pair <Node*, Node*> Pair;

const int N = 333333 * 2;
const int BOUND = N * 25;
const double eps = 1e-10;
const int DEBUG = 0;

void myAssert(bool flag) {
	if (!flag)
		while(1);
}

struct Point {
	long long x, y;
	Point (int x, int y) : x(x), y(y) {}
	Point () {}
	friend Point operator +(const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend Point operator *(const Point &a, const long long &b) {
		return Point (a.x * b, a.y * b);
	}
	friend bool operator <(const Point &a, const Point &b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
};

map<Point, int> pmap;

long long det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

long long dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

struct Line {
	Point s, t;
	int left;
	Line(Point a, Point b, int left) : s(a), t(b), left(left) {}
	Line() {}
	void show() {
		printf("%I64d %I64d %I64d %I64d\n", s.x, s.y, t.x, t.y);
	}
};

vector<Line> lines;
vector<pair< pair<int, int>, pair<int, int> > > vertical;
vector<pair<int, int> > events;

struct Node {
	int size, key;
	Node *left, *right;
	
	Node(Node *left, Node *right) : left(left), right(right) {}
	Node() {}
	
	Node* update() {
		size = left->size + right->size + 1;
		return this;
	}
	
    Pair split(double);
};


Node* null;
Node memory[BOUND];
int used = 0;

Node *newNode(int k) {
	//myAssert(used < BOUND);
	Node *tmp = &memory[used++];
	tmp->key = k;
	tmp->left = tmp->right = null;
	tmp->size = 1;
	return tmp;
}

Node* newNode(Node *root) {
	//myAssert(used < BOUND);
	Node *tmp = &memory[used++];
	*tmp = *root;
	return tmp;
}

const int DIGIT = ((1 << 15) - 1);

bool random(int a, int b) {
	return (((rand() & DIGIT) << 15) | rand()) % (a + b) < a;
}


Node *mergy(Node *p, Node *q) {
	if (p == null) {
		return q;
	}
	if (q == null) {
		return p;
	}
	Node* tmp;
	if (random(p->size, q->size)) {
		tmp = newNode(p);
		tmp->right = mergy(tmp->right, q);
	} else {
		tmp = newNode(q);
		tmp->left = mergy(p, tmp->left);
	}
	return tmp->update();
}

double global_x;

double evaluate(int id) {
	myAssert(lines[id].s.x != lines[id].t.x);
	double k = (double)(lines[id].t.y - lines[id].s.y) / (lines[id].t.x - lines[id].s.x);
	return lines[id].s.y + (global_x - lines[id].s.x) * k;
}

Node *del(Node *root, int id, double cmpy) {
	myAssert(root != null);
	if (root->key == id) {
		return mergy(root->left, root->right);
	}
	//myAssert(used < BOUND);
	Node *tmp = newNode(root);
	
	if (evaluate(root->key) < cmpy) {
		tmp->right = del(tmp->right, id, cmpy);
	} else {
		tmp->left = del(tmp->left, id, cmpy);
	}
	
	return tmp->update();
}

Pair Node::split(double val) {
    if (this == null) {
        return make_pair(null, null);
    } 
	Node *tmp = newNode(this);
    if (evaluate(key) > val) {
        Pair ret = left->split(val);
        tmp->left = ret.second, tmp->right = right;
        return make_pair(ret.first, tmp->update());
    } else {
	    Pair ret = right->split(val);
	    tmp->left = left, tmp->right = ret.first;
	    return make_pair(tmp->update(), ret.second);
	}
}

pair<double, int> queryLower(Node *root, double y) {
	if (root == null)
		return make_pair(-1e60, -1);
	if (evaluate(root->key) < y + eps) {
		pair<double, int> ret = queryLower(root->right, y);
		if (ret.second >= 0)
			return ret;
		return make_pair(evaluate(root->key), root->key);
	} else {
		return queryLower(root->left, y);
	}
}

pair<double, int> queryUpper(Node *root, double y) {
	if (root == null)
		return make_pair(1e60, -1);
	if (evaluate(root->key) > y - eps) {
		pair<double, int> ret = queryUpper(root->left, y);
		if (ret.second >= 0)
			return ret;
		return make_pair(evaluate(root->key), root->key);
	} else {
		return queryUpper(root->right, y);
	}
}

int n;
Node *root[N];
int position[N];

bool isLeft(Point a, Point b, Point c) {
	return det(b - a, c - a) >= 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	used = 0;
	null = &memory[used++];
	null->left = null->right = null;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		vector<Point> points;
		int num = 0;
		long long area = 0;
		scanf("%d", &num);
		for(int j = 1; j <= num; j++) {
			int x, y;
			scanf("%d %d", &x, &y);
			Point tmp(x, y);
			points.push_back(tmp);
			pmap[tmp] = i;
		}
		for(int j = 0; j < num; j++) {
			area += det(points[j], points[(j + 1) % num]);
		}
		if (area < 0) {
			reverse(points.begin(), points.end());
		}
		for(int j = 0; j < num; j++) {
			Point s = points[j], t = points[(j + 1) % num];
			lines.push_back(Line(s, t, i));
			if (s.x > t.x || s.x == t.x && s.y > t.y)
				swap(s, t);
			if (s.x == t.x) {
				vertical.push_back(make_pair(make_pair(s.x, s.y), make_pair(t.y, i)));	
			} else {
				events.push_back(make_pair(s.x, (int)lines.size()));
				events.push_back(make_pair(t.x, -(int)lines.size()));	
			}
			
		}
	}	
	sort(events.begin(), events.end());
	sort(vertical.begin(), vertical.end());
	
	myAssert((int)events.size() < N);
	if (DEBUG) {
		puts("lines info");
		for(int i = 0; i < (int)lines.size(); i++) {
			printf("%I64d %I64d %I64d %I64d\n", lines[i].s.x, lines[i].s.y, lines[i].t.x, lines[i].t.y);
		}
		puts("lines end");
		puts("");
	
		puts("events info");
		for(int i = 0; i < (int)events.size(); i++) {
			printf("%d %d\n", events[i].first, events[i].second);
		}
		puts("events end");
		puts("");
	}
	
	root[0] = null;
	position[0] = -1;
	int last = 0;
	for(int i = 0, j; i < (int)events.size(); i = j) {
		int cur = last + 1;
		//myAssert(cur < N);
		root[cur] = root[last++];
		position[cur] = events[i].first;
		//printf("%d %d\n", cur, i);
		global_x = events[i].first - 0.5;
		
		//delete
		for(j = i; events[j].second < 0 && events[j].first == events[i].first; j++) {
			int id = -events[j].second - 1;
			root[cur] = del(root[cur], id, evaluate(id));
		}
		
		global_x = events[i].first + 0.5;
		
		for(; events[j].second > 0 && events[j].first == events[i].first; j++) {
			int id = events[j].second - 1;
			Pair ret = root[cur]->split(evaluate(id));
			Node *now = newNode(id);
			root[cur] = mergy(mergy(ret.first, now), ret.second);
		}
	}
	int qnum;
	scanf("%d", &qnum);
	/*
	for(int i = 1; i <= last; i++) {
		printf("size[%d] = %d\n", i, root[i]->size);
	}*/
	while(qnum--) {
		int x, y;
		scanf("%d %d", &x, &y);
		Point s = Point(x, y);
		if (pmap.find(s) != pmap.end()) {
			printf("%d\n", pmap[s]); fflush(stdout);
			continue;
		}
		// case vertical
		if (vertical.size()) {
			int l = 0, r = (int)vertical.size() - 1, mid;
			while(l < r) {
				mid = (l + r) / 2 + 1;
				if (vertical[mid].first.first < x || 
					vertical[mid].first.first == x && vertical[mid].first.second <= y)
						l = mid;
				else
					r = mid - 1;
			}
			if (vertical[l].first.first == x && vertical[l].first.second <= y && vertical[l].second.first >= y) {
				printf("%d\n", vertical[l].second.second); fflush(stdout);
				continue;
			}
		}
		
		if (x < position[1] || x > position[last]) {
			printf("-1\n"); fflush(stdout);
			continue;
		}
		
		int l = 1, r = last, mid;
		while(l < r) {
			mid = (l + r) / 2 + 1;
			if (position[mid] > x)
				r = mid - 1;
			else
				l = mid;
		}
		
		global_x = x;
		pair<double, int> lower, upper;
		lower = queryLower(root[l], y);
		//myAssert(lower.second < (int)lines.size());
		//printf("%d %d\n", root[l]->size, root[l]->right->size);
		if (lower.second != -1 && isLeft(lines[lower.second].s, lines[lower.second].t, Point(x, y))) {
			printf("%d\n", lines[lower.second].left); fflush(stdout);
			continue;
		}
		upper = queryUpper(root[l], y);
		//myAssert(upper.second < (int)lines.size());
		if (upper.second != -1 && isLeft(lines[upper.second].s, lines[upper.second].t, Point(x, y))) {
			printf("%d\n", lines[upper.second].left); fflush(stdout);
			continue;
		}
		printf("-1\n"); fflush(stdout);
	}
	return 0;
} 
